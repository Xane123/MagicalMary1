/*
** gl_glow.cpp
** Glowing flats like Doomsday
**
**---------------------------------------------------------------------------
** Copyright 2005 Christoph Oelckers
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
** 4. When not used as part of GZDoom or a GZDoom derivative, this code will be
**    covered by the terms of the GNU Lesser General Public License as published
**    by the Free Software Foundation; either version 2.1 of the License, or (at
**    your option) any later version.
** 5. Full disclosure of the entire project's source code, except for third
**    party libraries is mandatory. (NOTE: This clause is non-negotiable!)
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**---------------------------------------------------------------------------
**
*/

//Extra things in this file were added from https://github.com/coelckers/gzdoom/commit/02c3b3613fef339a70e26452156292297454e7c2 and will probably break. That floating point update sucked!

#include "w_wad.h"
#include "sc_man.h"
#include "v_video.h"
#include "r_defs.h"
#include "textures/textures.h"

#include "gl/dynlights/gl_glow.h"

//===========================================================================
// 
//	Reads glow definitions from GLDEFS
//
//===========================================================================
void gl_InitGlow(FScanner &sc)
{
	sc.MustGetStringName("{");
	while (!sc.CheckString("}"))
	{
		sc.MustGetString();
		if (sc.Compare("FLATS"))
		{
			sc.MustGetStringName("{");
			while (!sc.CheckString("}"))
			{
				sc.MustGetString();
				FTextureID flump=TexMan.CheckForTexture(sc.String, FTexture::TEX_Flat,FTextureManager::TEXMAN_TryAny);
				FTexture *tex = TexMan[flump];
				if (tex) tex->gl_info.bAutoGlowing = tex->gl_info.bGlowing = tex->gl_info.bFullbright = true;
			}
		}
		else if (sc.Compare("WALLS"))
		{
			sc.MustGetStringName("{");
			while (!sc.CheckString("}"))
			{
				sc.MustGetString();
				FTextureID flump=TexMan.CheckForTexture(sc.String, FTexture::TEX_Wall,FTextureManager::TEXMAN_TryAny);
				FTexture *tex = TexMan[flump];
				if (tex) tex->gl_info.bAutoGlowing = tex->gl_info.bGlowing = tex->gl_info.bFullbright = true;
			}
		}
		else if (sc.Compare("TEXTURE"))
		{
			sc.SetCMode(true);
			sc.MustGetString();
			FTextureID flump=TexMan.CheckForTexture(sc.String, FTexture::TEX_Flat,FTextureManager::TEXMAN_TryAny);
			FTexture *tex = TexMan[flump];
			sc.MustGetStringName(",");
			sc.MustGetString();
			PalEntry color = V_GetColor(NULL, sc.String);
			//sc.MustGetStringName(",");
			//sc.MustGetNumber();
			if (sc.CheckString(","))
			{
				if (sc.CheckNumber())
				{
					if (tex) tex->gl_info.GlowHeight = sc.Number;
					if (!sc.CheckString(",")) goto skip_fb;
				}

				sc.MustGetStringName("fullbright");
				if (tex) tex->gl_info.bFullbright = true;
			}
		skip_fb:
			sc.SetCMode(false);

			if (tex && color != 0)
			{
				tex->gl_info.bAutoGlowing = false;
				tex->gl_info.bGlowing = true;
				tex->gl_info.GlowColor = color;
			}
		}
	}
}


//==========================================================================
//
// Checks whether a sprite should be affected by a glow
//
//==========================================================================
int gl_CheckSpriteGlow(sector_t *sector, int lightlevel, int x, int y, int z)
{
	float bottomglowcolor[4];
	bottomglowcolor[3] = 0;
	auto c = sector->planes[sector_t::floor].GlowColor;
	if (c == 0)	//"doubles" are "fixed_t" here.
	{
		FTexture *tex = TexMan[sector->GetTexture(sector_t::floor)];
		if (tex != NULL && tex->isGlowing())
		{
			if (!tex->gl_info.bAutoGlowing) tex = TexMan(sector->GetTexture(sector_t::floor));
			if (tex->isGlowing())	// recheck the current animation frame.
				{
				tex->GetGlowColor(bottomglowcolor);
				bottomglowcolor[3] = (float)tex->gl_info.GlowHeight;
				}
			}
		
		}
	else if (c != -1)
		{
		bottomglowcolor[0] = c.r / 255.f;
		bottomglowcolor[1] = c.g / 255.f;
		bottomglowcolor[2] = c.b / 255.f;
		bottomglowcolor[3] = sector->planes[sector_t::floor].GlowHeight;
		}
	
		if (bottomglowcolor[3]> 0)
		 {
		fixed_t floordiff = z - sector->floorplane.ZatPoint(x, y);
		if (floordiff < bottomglowcolor[3])
		{
			int maxlight = (255+lightlevel)>>1;
			fixed_t lightfrac = floordiff / bottomglowcolor[3];
			if (lightfrac<0) lightfrac=0;
			lightlevel= (lightfrac*lightlevel + maxlight*(FRACUNIT-lightfrac))>>FRACBITS;
		}
	}
	return lightlevel;
}

//==========================================================================
//
// Checks whether a wall should glow
//
//==========================================================================
bool gl_GetWallGlow(sector_t *sector, float *topglowcolor, float *bottomglowcolor)
 {
	bool ret = false;
	bottomglowcolor[3] = topglowcolor[3] = 0;
	auto c = sector->planes[sector_t::ceiling].GlowColor;
	if (c == 0)
		{
		FTexture *tex = TexMan[sector->GetTexture(sector_t::ceiling)];
		if (tex != NULL && tex->isGlowing())
			{
			if (!tex->gl_info.bAutoGlowing) tex = TexMan(sector->GetTexture(sector_t::ceiling));
			if (tex->isGlowing())	// recheck the current animation frame.
				{
				ret = true;
				tex->GetGlowColor(topglowcolor);
				topglowcolor[3] = (float)tex->gl_info.GlowHeight;
				}
			}
		}
	else if (c != -1)
		{
		topglowcolor[0] = c.r / 255.f;
		topglowcolor[1] = c.g / 255.f;
		topglowcolor[2] = c.b / 255.f;
		topglowcolor[3] = sector->planes[sector_t::ceiling].GlowHeight;
		ret = topglowcolor[3] > 0;
		}
	
		c = sector->planes[sector_t::floor].GlowColor;
		if (c == 0)
		{
		FTexture *tex = TexMan[sector->GetTexture(sector_t::floor)];
		if (tex != NULL && tex->isGlowing())
			{
			if (!tex->gl_info.bAutoGlowing) tex = TexMan(sector->GetTexture(sector_t::floor));
			if (tex->isGlowing())	// recheck the current animation frame.
				{
				ret = true;
				tex->GetGlowColor(bottomglowcolor);
				bottomglowcolor[3] = (float)tex->gl_info.GlowHeight;
				}
			}
		}
	else if (c != -1)
		{
		bottomglowcolor[0] = c.r / 255.f;
		bottomglowcolor[1] = c.g / 255.f;
		bottomglowcolor[2] = c.b / 255.f;
		bottomglowcolor[3] = sector->planes[sector_t::floor].GlowHeight;
		ret = bottomglowcolor[3] > 0;
		}
	return ret;
	}

#include "c_dispatch.h"
#include "d_player.h"

CCMD(setglow)
{
	auto s = players[0].mo->Sector;
	s->planes[sector_t::floor].GlowHeight = 128;
	s->planes[sector_t::floor].GlowColor = 0xff0000;
}