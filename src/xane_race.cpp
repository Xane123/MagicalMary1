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

CVAR(Bool, xane_controller, false, CVAR_ARCHIVE|CVAR_USERINFO)

CVAR(Int,xane_racecourse1,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG|CVAR_SERVERINFO)	//[XANE]Race track #1
CVAR(Int,xane_racecourse2,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG|CVAR_SERVERINFO)	//[XANE]Race track #2
CVAR(Int,xane_racecourse3,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG|CVAR_SERVERINFO)	//[XANE]Race track #3
CVAR(Int,xane_racecourse4,0,CVAR_ARCHIVE|CVAR_MOD|CVAR_GLOBALCONFIG|CVAR_SERVERINFO)	//[XANE]Race track #4

CUSTOM_CVAR(Int, xane_racecup, 0, CVAR_ARCHIVE|CVAR_NOINITCALL) //[XANE]Similar to compatflags; Sets custom variables to preset values.
{

	switch (self)
	{
	default:
		break;
	case 1: //Test Cup #1
		xane_racecourse1 = 94;
		xane_racecourse2 = 2;
		xane_racecourse3 = 3;
		xane_racecourse4 = 4;
		break;
	case 2:	//Test Cup #2
		xane_racecourse1 = 2;
		xane_racecourse2 = 4;
		xane_racecourse3 = 6;
		xane_racecourse4 = 8;
		break;

	}
}