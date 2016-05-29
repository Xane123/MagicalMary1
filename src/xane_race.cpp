// HEADER FILES ------------------------------------------------------------

#ifdef _WIN32
#include <direct.h>
#define mkdir(a,b) _mkdir (a)
#else
#include <sys/stat.h>
#endif

#ifdef HAVE_FPU_CONTROL
#include <fpu_control.h>
#endif
#include <float.h>

#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif

#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "doomdef.h"
#include "doomstat.h"
#include "gstrings.h"
	#include "m_misc.h"
#include "c_console.h"

CUSTOM_CVAR(Int, xane_popindistance, 1024, CVAR_ARCHIVE | CVAR_DEMOSAVE | CVAR_MOD | CVAR_NOINITCALL)
{
	if (xane_popindistance < 64)
	{
		xane_popindistance = 64;
		Printf("THAT POP-IN DISTANCE COULD AFFECT GAMEPLAY;\nYOUR POP-IN DISTANCE HAS BEEN SET TO 64.\n");
	}
}

CVAR(Int,xane_racecourse1,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG)	//[XANE]Race track #1
CVAR(Int,xane_racecourse2,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG)	//[XANE]Race track #2
CVAR(Int,xane_racecourse3,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG)	//[XANE]Race track #3
CVAR(Int,xane_racecourse4,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG)	//[XANE]Race track #4

EXTERN_CVAR(Bool, wokpos)
EXTERN_CVAR(Bool, noisedebug)

CUSTOM_CVAR(Int, xane_racecup, 0, CVAR_ARCHIVE|CVAR_NOINITCALL) //[XANE]Similar to compatflags; Sets custom variables to preset values.
{
		//94 - Andy's Room, 101 - Hell Circuit, and 102 - Uninished Snow Track.
	switch (self)
	{
	default:
		break;
	case 1: //Test Cup #1
		xane_racecourse1 = 94;
		xane_racecourse2 = 101;
		xane_racecourse3 = 94;
		xane_racecourse4 = 101;
		break;
	case 2:	//Test Cup #2
		xane_racecourse1 = 94;
		xane_racecourse2 = 94;
		xane_racecourse3 = 101;
		xane_racecourse4 = 102;
		break;

	}
}