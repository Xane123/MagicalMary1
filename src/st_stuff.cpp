//-----------------------------------------------------------------------------
//
// Copyright 1993-1996 id Software
// Copyright 1994-1996 Raven Software
// Copyright 1999-2016 Randy Heit
// Copyright 2002-2016 Christoph Oelckers
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//		Cheat code. See *_sbar.cpp for status bars.
//
//-----------------------------------------------------------------------------

#include "d_protocol.h"
#include "gstrings.h"
#include "c_cvars.h"
#include "c_dispatch.h"
#include "d_event.h"
#include "gi.h"
#include "d_net.h"
#include "doomstat.h"
#include "g_level.h"
#include "g_levellocals.h"

EXTERN_CVAR (Bool, ticker);
EXTERN_CVAR (Bool, noisedebug);
EXTERN_CVAR (Int, am_cheat);

struct cheatseq_t
{
	uint8_t *Sequence;
	uint8_t *Pos;
	uint8_t DontCheck;
	uint8_t CurrentArg;
	uint8_t Args[2];
	bool (*Handler)(cheatseq_t *);
};

static bool CheatCheckList (event_t *ev, cheatseq_t *cheats, int numcheats);
static bool CheatAddKey (cheatseq_t *cheat, uint8_t key, bool *eat);
static bool Cht_Generic (cheatseq_t *);
static bool Cht_Music (cheatseq_t *);
static bool Cht_BeholdMenu (cheatseq_t *);
static bool Cht_PumpupMenu (cheatseq_t *);
static bool Cht_AutoMap (cheatseq_t *);
static bool Cht_ChangeLevel (cheatseq_t *);
static bool Cht_ChangeStartSpot (cheatseq_t *);
static bool Cht_WarpTransLevel (cheatseq_t *);
static bool Cht_MyPos (cheatseq_t *);
static bool Cht_Sound (cheatseq_t *);
static bool Cht_Ticker (cheatseq_t *);

uint8_t CheatPowerup[7][12] =
{
	{ 'x','d','o','o','m','r','o','c','k','s','v', 255 },	//X DOOM ROCKS (because these are leftovers from Doom)
	{ 'x','d','o','o','m','r','o','c','k','s','s', 255 },
	{ 'x','d','o','o','m','r','o','c','k','s','i', 255 },
	{ 'x','d','o','o','m','r','o','c','k','s','r', 255 },
	{ 'x','d','o','o','m','r','o','c','k','s','a', 255 },
	{ 'x','d','o','o','m','r','o','c','k','s','l', 255 },
	{ 'x','d','o','o','m','r','o','c','k','s','d', 255 },
};

//The list of cheats in Mary's Magical Adventure. These all start with the letter 'X' to allow easy entry.
static uint8_t CheatNoclip[] =	{ 'x','g','h','o','s','t',255 };							//XGHOST
static uint8_t CheatGod[] =		{ 'x','h','o','n','o','r',255 };							//X HONOR (Arthas)
static uint8_t CheatAmmo[] =		{ 'x','a','m','m','o','p','l','e','a','s','e',255 };	//X AMMO PLEASE
static uint8_t CheatAmmoNoKey[] =	{ 'x','g','i','m','m','e','k','e','y','s',255 };		//X GIMME KEYS
static uint8_t CheatClev[] =		{ 'x','a','r','e','a',0,0,255 };						//X AREA
static uint8_t CheatMypos[] =		{ 'x','w','h','e','r','e','a','m','i',255 };			//X WHERE AM I
static uint8_t CheatAmap[] = { 'x','a','n','e',255 };										//XANE
static uint8_t CheatKill[] = { 'x','k','i','l','l',255 };									//X KILL


static cheatseq_t GameCheats[] =
{
	{ CheatPowerup[6],		0, 1, 0, {0,0},				Cht_BeholdMenu },
	{ CheatMypos,			0, 1, 0, {0,0},				Cht_MyPos },
	{ CheatAmap,				0, 0, 0, {0,0},				Cht_AutoMap },
	{ CheatGod,				0, 0, 0, {CHT_IDDQD,0},		Cht_Generic },
	{ CheatAmmo,				0, 0, 0, {CHT_IDKFA,0},		Cht_Generic },
	{ CheatAmmoNoKey,		0, 0, 0, {CHT_IDFA,0},		Cht_Generic },
	{ CheatNoclip,			0, 0, 0, {CHT_NOCLIP,0},		Cht_Generic },
	{ CheatPowerup[0],		0, 0, 0, {CHT_BEHOLDV,0},	Cht_Generic },
	{ CheatPowerup[1],		0, 0, 0, {CHT_BEHOLDS,0},	Cht_Generic },
	{ CheatPowerup[2],		0, 0, 0, {CHT_BEHOLDI,0},	Cht_Generic },
	{ CheatPowerup[3],		0, 0, 0, {CHT_BEHOLDR,0},	Cht_Generic },
	{ CheatPowerup[4],		0, 0, 0, {CHT_BEHOLDA,0},	Cht_Generic },
	{ CheatPowerup[5],		0, 0, 0, {CHT_BEHOLDL,0},	Cht_Generic },
	{ CheatClev,				0, 1, 0, {0,0},				Cht_ChangeLevel },
	{ CheatKill,				0, 0, 0, {CHT_MDK,0},		Cht_Generic }
};

// Respond to keyboard input events, intercept cheats.
// [RH] Cheats eat the last keypress used to trigger them
bool ST_Responder (event_t *ev)
{
	bool eat = false;

		static cheatseq_t *cheatlists[] = { GameCheats };
		static int counts[] = { countof(GameCheats) };

		for (size_t i=0; i<countof(cheatlists); i++)
		{
			if (CheatCheckList(ev, cheatlists[i], counts[i])) return true;
		}
	return false;
}

static bool CheatCheckList (event_t *ev, cheatseq_t *cheats, int numcheats)
{
	bool eat = false;

	if (ev->type == EV_KeyDown)
	{
		int i;

		for (i = 0; i < numcheats; i++, cheats++)
		{
			if (CheatAddKey (cheats, (uint8_t)ev->data2, &eat))
			{
				if (cheats->DontCheck || !CheckCheatmode ())
				{
					eat |= cheats->Handler (cheats);
				}
			}
			else if (cheats->Pos - cheats->Sequence > 1)
			{ // If more than two characters into the sequence,
			  // eat the keypress, just so that the Hexen cheats
			  // with T in them will work without unbinding T.
				eat = true;
			}
		}
	}
	return eat;
}

//--------------------------------------------------------------------------
//
// FUNC CheatAddkey
//
// Returns true if the added key completed the cheat, false otherwise.
//
//--------------------------------------------------------------------------

static bool CheatAddKey (cheatseq_t *cheat, uint8_t key, bool *eat)
{
	if (cheat->Pos == NULL)
	{
		cheat->Pos = cheat->Sequence;
		cheat->CurrentArg = 0;
	}
	if (*cheat->Pos == 0)
	{
		*eat = true;
		cheat->Args[cheat->CurrentArg++] = key;
		cheat->Pos++;
	}
	else if (key == *cheat->Pos)
	{
		cheat->Pos++;
	}
	else
	{
		cheat->Pos = cheat->Sequence;
		cheat->CurrentArg = 0;
	}
	if (*cheat->Pos == 0xff)
	{
		cheat->Pos = cheat->Sequence;
		cheat->CurrentArg = 0;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
//
// CHEAT FUNCTIONS
//
//--------------------------------------------------------------------------

static bool Cht_Generic (cheatseq_t *cheat)
{
	Net_WriteByte (DEM_GENERICCHEAT);
	Net_WriteByte (cheat->Args[0]);
	return true;
}

static bool Cht_Music (cheatseq_t *cheat)
{
	char buf[12] = "puke 254 xx";

	if (cheat->Args[0] == 0)
	{
		buf[9] = cheat->Args[1];
		buf[10] = '\0';
	}
	else
	{
		buf[9] = cheat->Args[0];
		buf[10] = cheat->Args[1];
	}

	C_DoCommand(buf);
	return true;
}

static bool Cht_BeholdMenu (cheatseq_t *cheat)
{
	Printf ("%s\n", GStrings("STSTR_BEHOLD"));
	return false;
}

static bool Cht_PumpupMenu (cheatseq_t *cheat)
{
	// How many people knew about the PUMPUPT cheat, since
	// it isn't printed in the list?
	Printf ("Bzrk, Inviso, Mask, Health, Pack, Stats\n");
	return false;
}

static bool Cht_AutoMap (cheatseq_t *cheat)
{
	if (automapactive)
	{
		am_cheat = (am_cheat + 1) % 3;
		return true;
	}
	else
	{
		return false;
	}
}

static bool Cht_ChangeLevel (cheatseq_t *cheat)
{
	char cmd[10] = "idclev xx";

	cmd[7] = cheat->Args[0];
	cmd[8] = cheat->Args[1];
	C_DoCommand (cmd);
	return true;
}

static bool Cht_ChangeStartSpot (cheatseq_t *cheat)
{
	char cmd[64];

	mysnprintf (cmd, countof(cmd), "changemap %s %c", primaryLevel->MapName.GetChars(), cheat->Args[0]);
	C_DoCommand (cmd);
	return true;
}

static bool Cht_WarpTransLevel (cheatseq_t *cheat)
{
	char cmd[11] = "hxvisit xx";
	cmd[8] = cheat->Args[0];
	cmd[9] = cheat->Args[1];
	C_DoCommand (cmd);
	return true;
}

static bool Cht_MyPos (cheatseq_t *cheat)
{
	C_DoCommand ("toggle idmypos");
	return true;
}

static bool Cht_Ticker (cheatseq_t *cheat)
{
	ticker = !ticker;
	Printf ("%s\n", GStrings(ticker ? "TXT_CHEATTICKERON" : "TXT_CHEATTICKEROFF"));
	return true;
}

static bool Cht_Sound (cheatseq_t *cheat)
{
	noisedebug = !noisedebug;
	Printf ("%s\n", GStrings(noisedebug ? "TXT_CHEATSOUNDON" : "TXT_CHEATSOUNDOFF"));
	return true;
}
