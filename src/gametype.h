#ifndef EGAMETYPE
#define EGAMETYPE
enum EGameType
{
	GAME_Any	 = 0,
	GAME_MMA	 = 1,
	GAME_Heretic = 2,
	GAME_Hexen	 = 4,
	GAME_Strife	 = 8,
	GAME_Chex	 = 16, //Chex is basically Doom, but we need to have a different set of actors.

	GAME_Raven			= GAME_Heretic|GAME_Hexen,
	GAME_DoomChex		= GAME_MMA|GAME_Chex,
	GAME_DoomStrifeChex	= GAME_MMA|GAME_Strife|GAME_Chex
};
#endif

