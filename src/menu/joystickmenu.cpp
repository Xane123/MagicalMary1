/*
** joystickmenu.cpp
** The joystick configuration menus
**
**---------------------------------------------------------------------------
** Copyright 2010 Christoph Oelckers
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

#include <float.h>

#include "menu/menu.h"
#include "c_dispatch.h"
#include "w_wad.h"
#include "sc_man.h"
#include "v_font.h"
#include "g_level.h"
#include "d_player.h"
#include "v_video.h"
#include "gi.h"
#include "i_system.h"
#include "c_bind.h"
#include "v_palette.h"
#include "d_event.h"
#include "d_gui.h"
#include "i_music.h"
#include "m_joy.h"

#define NO_IMP
#include "optionmenuitems.h"


static TArray<IJoystickConfig *> Joysticks;
IJoystickConfig *SELECTED_JOYSTICK;

FOptionMenuDescriptor *UpdateJoystickConfigMenu(IJoystickConfig *joy);

//=============================================================================
//
//
//
//=============================================================================

class FOptionMenuSliderJoySensitivity : public FOptionMenuSliderBase
{
public:
	FOptionMenuSliderJoySensitivity(const char *label, double min, double max, double step, int showval)
		: FOptionMenuSliderBase(label, min, max, step, showval)
	{
	}

	double GetSliderValue()
	{
		return SELECTED_JOYSTICK->GetSensitivity();
	}

	void SetSliderValue(double val)
	{
		SELECTED_JOYSTICK->SetSensitivity(float(val));
	}
};

//=============================================================================
//
//
//
//=============================================================================

class FOptionMenuSliderJoyScale : public FOptionMenuSliderBase
{
	int mAxis;
	int mNeg;
	
public:
	FOptionMenuSliderJoyScale(const char *label, int axis, double min, double max, double step, int showval)
		: FOptionMenuSliderBase(label, min, max, step, showval)
	{
		mAxis = axis;
		mNeg = 1;
	}

	double GetSliderValue()
	{
		double d = SELECTED_JOYSTICK->GetAxisScale(mAxis);
		mNeg = d < 0? -1:1;
		return d;
	}

	void SetSliderValue(double val)
	{
		SELECTED_JOYSTICK->SetAxisScale(mAxis, float(val * mNeg));
	}
};

//=============================================================================
//
//
//
//=============================================================================

class FOptionMenuSliderJoyDeadZone : public FOptionMenuSliderBase
{
	int mAxis;
	int mNeg;
	
public:
	FOptionMenuSliderJoyDeadZone(const char *label, int axis, double min, double max, double step, int showval)
		: FOptionMenuSliderBase(label, min, max, step, showval)
	{
		mAxis = axis;
		mNeg = 1;
	}

	double GetSliderValue()
	{
		double d = SELECTED_JOYSTICK->GetAxisDeadZone(mAxis);
		mNeg = d < 0? -1:1;
		return d;
	}

	void SetSliderValue(double val)
	{
		SELECTED_JOYSTICK->SetAxisDeadZone(mAxis, float(val * mNeg));
	}
};

//=============================================================================
//
// 
//
//=============================================================================

class FOptionMenuItemJoyMap : public FOptionMenuItemOptionBase
{
	int mAxis;
public:

	FOptionMenuItemJoyMap(const char *label, int axis, const char *values, int center)
		: FOptionMenuItemOptionBase(label, "none", values, NULL, center)
	{
		mAxis = axis;
	}

	int GetSelection()
	{
		double f = SELECTED_JOYSTICK->GetAxisMap(mAxis);
		FOptionValues **opt = OptionValues.CheckKey(mValues);
		if (opt != NULL && *opt != NULL)
		{
			// Map from joystick axis to menu selection.
			for(unsigned i = 0; i < (*opt)->mValues.Size(); i++)
			{
				if (fabs(f - (*opt)->mValues[i].Value) < FLT_EPSILON)
				{
					return i;
				}
			}
		}
		return -1;
	}

	void SetSelection(int selection)
	{
		FOptionValues **opt = OptionValues.CheckKey(mValues);
		// Map from menu selection to joystick axis.
		if (opt == NULL || *opt == NULL || (unsigned)selection >= (*opt)->mValues.Size())
		{
			selection = JOYAXIS_None;
		}
		else
		{
			selection = (int)(*opt)->mValues[selection].Value;
		}
		SELECTED_JOYSTICK->SetAxisMap(mAxis, (EJoyAxis)selection);
	}
};

//=============================================================================
//
// 
//
//=============================================================================

class FOptionMenuItemInverter : public FOptionMenuItemOptionBase
{
	int mAxis;
public:

	FOptionMenuItemInverter(const char *label, int axis, int center)
		: FOptionMenuItemOptionBase(label, "none", "YesNo", NULL, center)
	{
		mAxis = axis;
	}

	int GetSelection()
	{
		float f = SELECTED_JOYSTICK->GetAxisScale(mAxis);
		return f > 0? 0:1;
	}

	void SetSelection(int Selection)
	{
		float f = fabsf(SELECTED_JOYSTICK->GetAxisScale(mAxis));
		if (Selection) f*=-1;
		SELECTED_JOYSTICK->SetAxisScale(mAxis, f);
	}
};

class DJoystickConfigMenu : public DOptionMenu
{
	DECLARE_CLASS(DJoystickConfigMenu, DOptionMenu)
};

IMPLEMENT_CLASS(DJoystickConfigMenu)

//=============================================================================
//
// Executes a CCMD, action is a CCMD name
//
//=============================================================================

class FOptionMenuItemJoyConfigMenu : public FOptionMenuItemSubmenu
{
	IJoystickConfig *mJoy;
public:
	FOptionMenuItemJoyConfigMenu(const char *label, IJoystickConfig *joy)
		: FOptionMenuItemSubmenu(label, "JoystickConfigMenu")
	{
		mJoy = joy;
	}

	bool Activate()
	{
		UpdateJoystickConfigMenu(mJoy);
		return FOptionMenuItemSubmenu::Activate();
	}
};


/*=======================================
 *
 * Joystick Menu
 *
 *=======================================*/

FOptionMenuDescriptor *UpdateJoystickConfigMenu(IJoystickConfig *joy)
{
	FMenuDescriptor **desc = MenuDescriptors.CheckKey(NAME_JoystickConfigMenu);
	if (desc != NULL && (*desc)->mType == MDESC_OptionsMenu)
	{
		FOptionMenuDescriptor *opt = (FOptionMenuDescriptor *)*desc;
		FOptionMenuItem *it;
		for(unsigned i=0;i<opt->mItems.Size();i++)
		{
			delete opt->mItems[i];
			opt->mItems.Clear();
		}
		if (joy == NULL)
		{
			opt->mTitle = GStrings("MENU_CONTROLLER_TITLE");
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_ERROR"), false);
			opt->mItems.Push(it);
		}
		else
		{
			opt->mTitle.Format("Configure %s", joy->GetName().GetChars());

			SELECTED_JOYSTICK = joy;

			it = new FOptionMenuSliderJoySensitivity(GStrings("MENU_CONTROLLER_SENSITIVITY1"), 0, 2, 0.1, 3);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(" ", false);
			opt->mItems.Push(it);

			if (joy->GetNumAxes() > 0)
			{
				it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_AXIS"), true);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);

				for (int i = 0; i < joy->GetNumAxes(); ++i)
				{
					it = new FOptionMenuItemStaticText("", false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemJoyMap(joy->GetAxisName(i), i, "JoyAxisMapNames", false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText("", false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText("", false);
					opt->mItems.Push(it);
					it = new FOptionMenuSliderJoyScale(GStrings("MENU_CONTROLLER_SENSITIVITY1"), i, 0, 4, 0.1, 3);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText(" ", false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemInverter(GStrings("MENU_CONTROLLER_INVERT"), i, false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText(" ", false);
					opt->mItems.Push(it);
					it = new FOptionMenuSliderJoyDeadZone(GStrings("MENU_CONTROLLER_DEADZONE"), i, 0, 0.9, 0.05, 3);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText(" ", false);
					opt->mItems.Push(it);
					it = new FOptionMenuItemStaticText(" ", false);
					opt->mItems.Push(it);

				}
			}
			else
			{
				it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_AXISERROR"), false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText(" ", false);
				opt->mItems.Push(it);
			}
		}
		opt->mScrollPos = 0;
		opt->mSelectedItem = -1;
		opt->mIndent = 0;
		opt->mPosition = -25;
		opt->CalcIndent();
		return opt;
	}
	return NULL;
}



void UpdateJoystickMenu(IJoystickConfig *selected)
{
	FMenuDescriptor **desc = MenuDescriptors.CheckKey(NAME_JoystickOptions);
	if (desc != NULL && (*desc)->mType == MDESC_OptionsMenu)
	{
		FOptionMenuDescriptor *opt = (FOptionMenuDescriptor *)*desc;
		FOptionMenuItem *it;
		for(unsigned i=0;i<opt->mItems.Size();i++)
		{
			delete opt->mItems[i];
		}
		opt->mItems.Clear();

		int i;
		int itemnum = -1;

		I_GetJoysticks(Joysticks);
		if ((unsigned)itemnum >= Joysticks.Size())
		{
			itemnum = Joysticks.Size() - 1;
		}
		if (selected != NULL)
		{
			for (i = 0; (unsigned)i < Joysticks.Size(); ++i)
			{
				if (Joysticks[i] == selected)
				{
					itemnum = i;
					break;
				}
			}
		}

		// Todo: Block joystick for changing this one.
		it = new FOptionMenuItemOption(GStrings("MENU_ECONTROLLERS"), "use_joystick", "YesNo", NULL, false);
		opt->mItems.Push(it);
		#ifdef _WIN32
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemOption(GStrings("MENU_DIRECTINPUT"), "joy_dinput", "YesNo", NULL, false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemOption(GStrings("MENU_XINPUT"), "joy_xinput", "YesNo", NULL, false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemOption(GStrings("MENU_PLAYSTATION2"), "joy_ps2raw", "YesNo", NULL, false);
			opt->mItems.Push(it);
		#endif

		it = new FOptionMenuItemStaticText("", false);
		opt->mItems.Push(it);
		it = new FOptionMenuItemStaticText("", false);
		opt->mItems.Push(it);

		if (Joysticks.Size() == 0)
		{
			it = new FOptionMenuItemStaticText(GStrings("MENU_NOCONTROLLERS_HEADER"), false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(GStrings("MENU_NOCONTROLLERS_INFO1"), false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(GStrings("MENU_NOCONTROLLERS_INFO2"), false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(GStrings("MENU_NOCONTROLLERS_INFO3"), false);
			opt->mItems.Push(it);
			if (!use_joystick)
			{
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_OFF1"), false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_OFF2"), false);
				opt->mItems.Push(it);
			}
		}
		else
		{
			it = new FOptionMenuItemStaticText("", false);
			opt->mItems.Push(it);
			it = new FOptionMenuItemStaticText(GStrings("MENU_CONTROLLER_ON"), false);
			opt->mItems.Push(it);

			for (int i = 0; i < (int)Joysticks.Size(); ++i)
			{
				it = new FOptionMenuItemStaticText("", false);
				opt->mItems.Push(it);
				it = new FOptionMenuItemJoyConfigMenu(Joysticks[i]->GetName(), Joysticks[i]);
				opt->mItems.Push(it);
				if (i == itemnum) opt->mSelectedItem = opt->mItems.Size();
			}
		}
		if (opt->mSelectedItem >= (int)opt->mItems.Size())
		{
			opt->mSelectedItem = opt->mItems.Size() - 1;
		}

		opt->CalcIndent();

		// If the joystick config menu is open, close it if the device it's
		// open for is gone.
		for (i = 0; (unsigned)i < Joysticks.Size(); ++i)
		{
			if (Joysticks[i] == SELECTED_JOYSTICK)
			{
				break;
			}
		}
		if (i == (int)Joysticks.Size())
		{
			SELECTED_JOYSTICK = NULL;
			if (DMenu::CurrentMenu != NULL && DMenu::CurrentMenu->IsKindOf(RUNTIME_CLASS(DJoystickConfigMenu)))
			{
				DMenu::CurrentMenu->Close();
			}
		}
	}
}

