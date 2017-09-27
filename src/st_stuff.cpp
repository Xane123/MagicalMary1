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

static uint8_t CheatNoclip2[] =	{ 'x','c','l','i','p','e','m',255 };	//XCLIPEM (X CLIP 'EM)
static uint8_t CheatMus[] =		{ 'p','l','a','y',0,0,255 };
static uint8_t CheatGod[] =		{ 'h','o','n','o','r',255 };	//"For honor."
static uint8_t CheatAmmo[] =		{ 'm','m','a','m','a','g','i','c',255 };	//MMAMAGIC (MMA MAGIC)
static uint8_t CheatMypos[] =		{ 'm','m','a','p','o','s',255 };	//MMAPOS
static uint8_t CheatAmap[] =		{ 'x','a','n','e',255 };

static cheatseq_t MMACheats[] =
{
	{ CheatMus,				0, 1, 0, {0,0},				Cht_Music },
	{ CheatMypos,			0, 1, 0, {0,0},				Cht_MyPos },
	{ CheatAmap,			0, 0, 0, {0,0},				Cht_AutoMap },
	{ CheatGod,				0, 0, 0, {CHT_IDDQD,0},		Cht_Generic },
	{ CheatAmmo,			0, 0, 0, {CHT_IDKFA,0},		Cht_Generic },
	{ CheatNoclip2,			0, 0, 0, {CHT_NOCLIP2,0},	Cht_Generic },
};

// Respond to keyboard input events, intercept cheats.
// [RH] Cheats eat the last keypress used to trigger them
bool ST_Responder (event_t *ev)
{
	bool eat = false;
	return CheatCheckList(ev, MMACheats, countof(MMACheats));
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
	char buf[20] = "runoldscript 254 x ";

	if (cheat->Args[0] == '0')
	{
		buf[17] = cheat->Args[1];
	}
	else
	{
		buf[17] = cheat->Args[0];
		buf[18] = cheat->Args[1];
	}
	C_DoCommand (buf);
	return true;
}

static bool Cht_BeholdMenu (cheatseq_t *cheat)
{
	Printf ("%s\n", GStrings("STSTR_BEHOLD"));
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

	mysnprintf (cmd, countof(cmd), "changemap %s %c", level.MapName.GetChars(), cheat->Args[0]);
	C_DoCommand (cmd);
	return true;
}


static bool Cht_MyPos (cheatseq_t *cheat)
{
	C_DoCommand ("toggle mmapos");
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
