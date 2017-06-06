// Emacs style mode select	 -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// $Log:$
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

EXTERN_CVAR (Bool, ticker);
EXTERN_CVAR (Bool, noisedebug);
EXTERN_CVAR (Int, am_cheat);

struct cheatseq_t
{
	BYTE *Sequence;
	BYTE *Pos;
	BYTE DontCheck;
	BYTE CurrentArg;
	BYTE Args[2];
	bool (*Handler)(cheatseq_t *);
};

static bool CheatCheckList (event_t *ev, cheatseq_t *cheats, int numcheats);
static bool CheatAddKey (cheatseq_t *cheat, BYTE key, bool *eat);
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

// Smashing Pumpkins Into Small Piles Of Putrid Debris. 
static BYTE CheatXKill[] =		{ 'x','k','i','l','l',255 };	//XKILL
static BYTE CheatNoclip2[] =	{ 'x','g','h','o','s','t',255 };	//XGHOST
static BYTE CheatMus[] =		{ 'x','p','l','a','y',0,0,255 };	//XPLAY##
static BYTE CheatGod[] =		{ 'h','o','n','o','r',255 };	//HONOR
static BYTE CheatAmmo[] =		{ 'm','m','a','l','o','c','k','s',255 };	//MMALOCKS
static BYTE CheatAmmoNoKey[] =  { 'm','m','a','w','e','a','p','s',255 };	//MMAWEAPS
static BYTE CheatClev[] =		{ 'x','c','h','g','l','v','l',0,0,255 };	//XCHGLVL##
static BYTE CheatMypos[] =		{ 'm','m','a','p','o','s',255 };	//MMAPOS
static BYTE CheatAmap[] =		{ 'x','a','n','e',255 };	//XANE

static cheatseq_t MMACheats[] =
{
	{ CheatMus,				0, 1, 0, {0,0},				Cht_Music },
	{ CheatMypos,			0, 1, 0, {0,0},				Cht_MyPos },
	{ CheatAmap,			0, 0, 0, {0,0},				Cht_AutoMap },
	{ CheatGod,				0, 0, 0, {CHT_IDDQD,0},		Cht_Generic },
	{ CheatAmmo,			0, 0, 0, {CHT_IDKFA,0},		Cht_Generic },
	{ CheatAmmoNoKey,		0, 0, 0, {CHT_IDFA,0},		Cht_Generic },
	{ CheatXKill,			0, 0, 0, {CHT_MDK,0},	Cht_Generic },
	{ CheatNoclip2,			0, 0, 0, {CHT_NOCLIP,0},	Cht_Generic },
	{ CheatClev,			0, 1, 0, {0,0},				Cht_ChangeLevel }
};

// Respond to keyboard input events, intercept cheats.
// [RH] Cheats eat the last keypress used to trigger them
bool ST_Responder (event_t *ev)
{
	bool eat = false;

	if (1)
	{
		cheatseq_t *cheats;
		int numcheats;

		switch (gameinfo.gametype)
		{
		case GAME_Doom:
			cheats = MMACheats;
			numcheats = countof(MMACheats);
			break;

		default:
			return false;
		}
		return CheatCheckList(ev, cheats, numcheats);
	}
	else
	{
		static cheatseq_t *cheatlists[] = { MMACheats };
		static int counts[] = { countof(MMACheats) };

		for (size_t i=0; i<countof(cheatlists); i++)
		{
			if (CheatCheckList(ev, cheatlists[i], counts[i])) return true;
		}
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
			if (CheatAddKey (cheats, (BYTE)ev->data2, &eat))
			{
				if (cheats->DontCheck || !CheckCheatmode ())
				{
					eat |= cheats->Handler (cheats);
				}
			}
			else if (cheats->Pos - cheats->Sequence > 2)
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

static bool CheatAddKey (cheatseq_t *cheat, BYTE key, bool *eat)
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

static bool Cht_Music(cheatseq_t *cheat)	//Ported from https://github.com/Xane123/MaryMagicalAdventure/commit/eb1bc900210d2f0ef2bf928d06f2f7f4f355c705
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
