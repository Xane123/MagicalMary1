# Changes (for v1.88)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Xane's Claw is now more responsive, only requiring a single use to stick to the circular objects placed on walls.
* Fixed division by zero error if returning to an area from a Special Stage if a moving skybox is in use.
* Areas now correctly set level variables when returning from a Special Stage or the Small Hut.
* When the screen fades in or out, Powerup Coins now won't tint the screen, which previously broke the near-seamless fade at the end of a level.
## Major
* Xane's claw now pulls Xane up to whatever's above the spot it attached to. This can be seen in 1-2 near the end of the area.
* Demos now use a CVAR (cl_demo) instead of using custom GameType checks. This increases compatibility with Delta Touch.
* Render culling has been added! This improves performance in Delta Touch but limits how far you can see by abusing how polyobjects stop rendering behind them. As such
## Minor
* Mary's House is now correctly referred to when spawning in it initially. Before, it was called "Small Hut".
* A small area was added behind Jane in the Small Hut, which will be used for a later game mechanic.
* A new area, **ARENA1**, was added. This is the first map in the "wave-based arena" mode, inspired by Hulk's "Challenge Mode" rooftop area.
* Screen fades were slightly changed to fade in/out quicker, mainly to make render-culling polyobject movement able to start sooner.
* Two new ambience sounds were added, ***creepy*** (5) and ***inside bowling alley*** (6).
* ZDoom's built-in purple text color was modified to be lighter and more pink to fit Mary and the game's overall girly color scheme.
* New "songs" were added to the radio in 1-3. "Oh-Ah, Oh-La" replaces "Foreign Song", which wasn't up to the other songs' standards. "My Michael Floatie" and "Monster Finger Owl" are the new ones, the latter sounding better.
