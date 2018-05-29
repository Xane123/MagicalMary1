# Changes (for v1.95 or v2.0)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* The version number on the title screen was corrected to v1.9.
* Xane's claw now uses the *Animation3* inventory item instead of *Animation2*. Before this, enemies could be provoked like if Mary cried near them if Xane tried firing his claw.
* Mary no longer gets teleported as the screen fades out at the end of Isle Hell City (1-1). This was because the script that prevented the "stuck in Hell City" glitch didn't have its right boundary extended far enough into the fake 1-2 corridor at the end of Mary's path.
* You don't randomly get the Green Key when 1-1 loads anymore.
* Burning weaker cops (1-1 only) now make the yelling sound while on fire.
* Weaker cops (1-1's variants) now respond to being burned. firing a single bullet (blue) or a burst of bullets (green).
* Warping from the Battle Arena minigame is now impossible. This fixes a glitch where you could return to the Small Hut and use the teleporter to return to Isle Hell City (1-1), which should be impossible once you enter Rooftop to Rooftop (1-2).
* Added sanity check for checkpoints; Now if the player or monsters are set to spawn at an object that doesn't exist, the checkpoint ID will revert to the level default, 616. This should fix the Black Room Glitch when dying in 1-1 after returning from a Battle Arena fight.
* Fixed "special plane areas" being double the size they were set to.
* Special Stages don't drain your time on the ground, now updated to the new special plane system.
* Fixed the hammer's silly behavior in the air if the player didn't have enough hammer upgrades to perform the Hammer Slam.
* Respawning from checkpoints that are placed on 3D floors now places the player on the 3D floor and not on the ground/bottomless pit below it.
* Fixed Xane spawning at the beginning of the current area when returning from a Special Stage.
* Fixed Special Stages incorrectly draining time just by standing on the main floor. This was caused by an outdated water level function from before the better area system was added.
## Major
* Health and jump height can be upgraded by picking up upgrade items for them, which are separate from weapon upgrade items.
* Mary's Hammer Slam attack behaves differently now; Instead of activating based on height alone, which could lead to unfair deaths, it now activates if at a high enough height **and** the attack button is held down. Briefly pressing the attack button will do the normal hammer attack now, even in mid-air!
* Reverted the bubble spawner's behavior to World of Kirbycraft v1.4's true randomness. This was done as the new system was ironically **too** predictable.
* Render-culling polyobjects are now non-solid due to a small source code modification. This replaces the "hurt on touch" polyobject behavior but the othe two polyobject types are still solid as before.
* Projectile reflection has been altered thanks to Ryuhi (developer of *Heretical Doom*); Projectiles only are reflected in front of Mary/Xane and you aren't invulnerable during the reflection. Lasers cannot be reflected, so they will phase through your protection. 
* City Street Run (1-3) can be completed now! Jump in the Uroboros (the "airship") at the end and it will "lift off" and Mary/Xane will go to "The Command Master", an incomplete area. Once this boss area is complete, the game will become v2.0 and the **ZDoom Forums Demo** will be made from this version, allowing playing of the four levels plus the arena!
* The Windows executable is now 32-bit! This allows more people to play the game.
* Added a new mod, the Materials Mod (*mma_materials.pk3*). This enables the new GLDEFS materials, viewable in the OpenGL ("true 3D") renderer. It makes metal and wooden surfaces reflect any lights around them.
* Added a second mod, the hi-res sprites/textures mod (*mma_hires.pk3*). This mod increases the resolution of textures and weapon sprites, not included with the game by default to keep the filesize down.
* The challenges from Mary's Magical Adventure v1.6 are being brought back! In the Small Hut, push use on the hanging yellow part of the counter above the orange/yellow rug. This will toggle challenges on/off. Jane will tell you what your goal is when you use the switches to change levels. However, she won't do this if you haven't completed the level with a percentage of at least 50%.
* Score cannot be earned during challenges or in Monster Arenas. This is to prevent easily getitng extra lives outside of main gameplay while keeping the score in sync with the 10,000-point increments, so the player always knows how far they are from an extra life without an additional counter.
* MacOS and Ubuntu builds are now up-to-date, though due to limitations, the MacOS build doesn't have sound. It's unknown if the Ubuntu build can get OpenAL sound at the moment as it will not start up in the virtual machine Xane is using.
* Title cards now appear before level transitions rather than after them. This makes the loading screens more interesting by reminding the player where they are going and looks vaguely like Sonic 3 & Knuckles' level titles during black-screen load times.
* *Ocean Floor* by Kulor has been replaced with an original composition, *To the Core*, which now plays after Mary/Xane enters HCPD HQ in City Street Run.
* Song info doesn't appear anymore if your music volume is below ¼.
## Minor
* Making it to the end of an area with more than 15 coins will automatically send them to the bank in the Small Hut, but some coins will be removed. Additionally, if transformed even less will be stored in the bank. This was done to encourage the player to warp to the Small Hut and add them to the bank manually, which could give them interest in buying things from its shop or trying out minigames. Those give the player a lot of coins if played well.
* Lovely Heart's big heart-shaped projectile isn't treated as a "powerful projectile" to enemies anymore. This was done so enemies like cops wouldn't jump over Magical Cutie Mary's attacks, which would waste the five coins it takes to perform the attack. Altering how Magical Cutie Mary behaves is planned in the future but for now, yes, using certain attacks costs coins.	
* Mary's "falling scream" sprites have been re-added into the game, but in the new art style.
* The drill in the Small Hut now functions. It costs 100 coins to "dig a tunnel" to the blue building seen in the first area. The building will contain minigames which will give Mary/Xane extra coins, making it worth the price.
* Mary's Hammer Slam now maintains momentum. This feels more natural and lets Mary "launch" herself at enemies. The Hammer Slam's height it activates at was raised to 1½ stories (192 units) off the ground. This makes it harder to perform the more powerful slams but improves balance. Perform the downward Air Dash before it for a boost forward upon landing!
* Some invisible walls now have a texture on them! This makes it clear what the boundaries of each area are. It isn't much better than the immersion-breaking invisible walls, but it decreases the chances of players trying to go somewhere only to find out that area's off-limits and unfairly losing a life.
* Powerup Coins are always 3D voxel models regardless of their distance from the player. The images they would turn into when distant are used if voxel model rendering is disabled, however.
* Mary's falling scream height has been increased, so Isle Hell City (1-1)'s buildings won't cause screaming every time Mary barely jumps off one but higher areas like Rooftop to Rooftop (1-2) will still cause screaming.
* Isle Hell City (1-1)'s ceiling height outdoors has been levelled out, meaning Mary/Xane won't hit invisible walls in the sky anymore!
* The combo meter drains slightly quicker now to balance the planned amounts of enemies. However, coins now increase more of the combo meter, allowing continuing combos without Combo Coins easier.
* Extra dialogue was added to Rooftop to Rooftop and City Street Run for Mary and Xane.
* Turrets can now automatically shoot lasers to a fast or slow rhythm instead of the default player detection. Hitting a turret in these modes will temporarily change it to its default behavior until it loses sight of you and reverts.
* Linedefs that triggered script errors about a non-existant "TimeSafeBoundary" script have had the script attached to them removed.
* Above-normal process priority option was added (Windows only); GZDoom changes the game's process priority automatically, but this prevents the user manually setting it to anything but "normal", so this was added.
* If crying is started during dialogue, it will happen after Mary stops talking.
* Turrets can be provoked by crying like the HCPD officers. If this is done, they will shoot at double-speed any time that particular turret detects you.
* Mary's Magical Adventure's logo is now slightly less purple and more pink.
* Some textures, such as fabric, metal walls, and ones taken from Legend of Zelda: Wind Waker have been replaced with better textures thanks to Substance Designer. (Additionally, the new "materials mod" takes advantage of this and gives those textures PBR texture maps, adding realistic reflections in areas that use lights.
* As dynamic lights don't cause lag just by being visible, the objects responsible for turning them on when a player is near them have been removed from City Street Run (1-3).