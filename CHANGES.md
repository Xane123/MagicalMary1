# Changes (for v1.88)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Xane's Claw is now more responsive, only requiring a single use to stick to the circular objects placed on walls.
* Fixed division by zero error if returning to an area from a Special Stage if a moving skybox is in use.
* Areas now correctly set level variables when returning from a Special Stage or the Small Hut.
* When the screen fades in or out, Powerup Coins now won't tint the screen, which previously broke the near-seamless fade at the end of a level.
* The Black Room Glitch could occur when returning from a Special Stage due to previous commenting out of a check that prevented updating the player's last ground position while they're on top of pure black floor, resulting in the game warping them into the room rather than out of it.
* If Mary Air Dashes onto the water, she'll stop displaying the Air Dash animation and will run properly on the water.
* A minor sound oddity where a footstep sound would be heard every time Mary performed an Air Dash was fixed by adding a height check to the footstep sound ACS script. It's unknown what caused the random sound, though.
* Added and additional height/button press check to the variable jump height script to prevent it activating after bouncing off of certain springs.
## Major
* Xane's claw now pulls Xane up to whatever's above the spot it attached to. This can be seen in 1-2 near the end of the area.
* Demos now use a CVAR (cl_demo) instead of using custom GameType checks. This increases compatibility with Delta Touch.
* Render culling has been added! This improves performance in Delta Touch but limits how far you can see by abusing how polyobjects stop rendering behind them. Due to this, mobile devices now use the same data as computers.
* Skyboxes no longer render on mobile or on computers if ***mma_mobile.pk3*** is loaded. This was done because even slopes can cause lag on mobile just by looking in their direction if a skyox using them is visible, such as the distant volcano in Hell City (1-1).
## Minor
* Mary's House is now correctly referred to when spawning in it initially. Before, it was called "Small Hut".
* A small area was added behind Jane in the Small Hut, which will be used for a later game mechanic.
* A new area, **ARENA1**, was added. This is the first map in the "wave-based arena" mode, inspired by Hulk's "Challenge Mode" rooftop area.
* Screen fades were slightly changed to fade in/out quicker, mainly to make render-culling polyobject movement able to start sooner.
* Two new ambience sounds were added, ***creepy*** (5) and ***inside bowling alley*** (6).
* ZDoom's built-in purple text color was modified to be lighter and more pink to fit Mary and the game's overall girly color scheme.
* New "songs" were added to the radio in 1-3. "Oh-Ah, Oh-La" replaces "Foreign Song", which wasn't up to the other songs' standards. "My Michael Floatie" and "Monster Finger Owl" are the new ones, the latter sounding better.
* On mobile (when ***mma_mobile.pk3*** is loaded) all jumps are the maximum height. This is done to counter lag and make timing Air Dashes easier on touch screens. If you're not using touch screen controls, don't load this file.