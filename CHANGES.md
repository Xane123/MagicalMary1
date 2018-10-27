# Changes (for v2.0)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Disabled "HandleHealthEvents" script in the Small Hut, which fixes the player randomly dropping coins upon warping there for a second time after losing health in the level.
* Fixed blue cops with rapid-fire behavior trying to run constantly. This was due to a leftover skip that caused the DECORATE code to skip the "if closer than 512 units, slowly walk" line, jumping straight to running. If playing on hard difficulty, the cop would endlessly slide into you!
* Lasers between Uroboros platforms have been re-added! This was due to removal of the laser projectiles, which were in the now-removed police DECORATE file used for the weaker police found in the scrapped first level.
* Mary no longer gets trapped in an endless loop of lowering her wand's Light Form after detransforming. This would happen even if said wand form wasn't unlocked yet.
* Returning from minigames in Jane's Hut now works as expected, spawning the player on the platform as it returns to its normal height. Glitches involving ***ss_position*** (now named ***spawn_position**** have been mostly fixed and it now serves a non-Special Stage purpose, hence the name change.
* Rain ambience now correctly starts when the storm begins in 1-3. Before, outdoor areas would then lose all ambient sounds.
## Major
* You can actually fail in Battle Arenas again! Somehow, I broke the arenas using their own "death behavior", which made them use #0, which is the default, taking a life from the player. This means the only way the player could lose was by running out of time, not dying!
* Upgrades are now non-linear! When a player picks up a weapon upgrade, a menu appears; Choose an upgrade from this menu then you will be given it! You can't see upgrades for weapons you don't have on-hand, and the final, fourth upgrade for each weapon can only be chosen once all other upgrades for that weapon are activated.
* Each weapon must have four upgrades due to the new upgrade menu, so Mary's Umbrella now has a new upgrade, Charged Burst! When used, Mary holds her umbrella back. When released, Mary quickly hits the enemy up to five times, depending on how long it was held back.
* Soap Boxes can be bought from Jane's Shop in packs of four! You can hold up to sixteen of them and place them anywhere to try catching enemies off-guard.
* Jane now has animated sprites using her "old design". If Jane ever gets a new design like Mary, her sprites will be replaced.
* You can now listen to the same radio "station" heard in City Street Run in Jane's Hut; Just cycle through all of the songs in the game using her radio and it will change to that! Do note that since the script that handles this is only on the level with Jane's Hut, 1-1 will instead play default music if none is chosen.
* The teleporter's controls are being moved to Xane's laptop; Push USE in front of it to start using it then choose Teleport-Hacker.
* Thanks to ***dpJudas***' parallax shader, some textures have "depth" to them, most obvious on checker tiles and city roads.
* It was removed previously for **good reason**, but Mary now cries if hurt too much during combat, which will anger all enemies around you! If this happens, run and hide fast, as everyone will start trying to cheaply kill you.
* The **Double Jump** and **Triple Jump** have been re-added from World of Kirbycraft v1.4! Push the jump button very shortly after you land from a jump while moving and you'll jump higher, though this disables your Air Dash (Mary)/Kirby Puffs (Xane).
* If playing on easy difficulty, you cannot get a Game Over anymore, being stuck at nine lives. In the future, Game Overs will change their behavior to just restart the current level, being renamed to "tries" which depend on the player's magic.
## Minor
* Xane's thrown hammer now is affected by gravity. It has less gravity for a few split-seconds but falls quicker after that.
* Jane's Shop is now complete; The last two slots were filled by **Soap Box ×4** and **Ability Upgrade**!
* Friendly Turrets are now placed slightly closer to the player.
* Buffed Soap Boxes slightly; Soap that lands on the ground deals more damage over time and flies farther from the Soap Box. Additionally, Soap Boxes have less health, so a single hammer attack makes them explode now.
* Magical Cutie Mary isn't affected by cops' stunning bullets and other special pain reactions.
* Disabled draw distance in Jane's Hut as the area is too small to need it. All other levels can still have it enabled.
* Checkpoints no longer store the player's angle. This is to clear a **SetCheckpoint** script argument slot for a "forced ambience" argument, which will fix cases where the wrong ambience is heard upon returning to a checkpoint.
* New songs were added to replace some of the radio songs. They're no more safe to use than the old ones, but the goal is to have the radio sounding higher-quality by the final version.
* Doors now have new sounds that sound less silly.
* After Mary is hurt, a third, purple "pain" meter appears until she has recovered from the pain. If this meter fills up, the crying behavior mentioned in the major changes will occur. If the player forces Mary to cry, the meter will disappear, as if she did it herself.
* Replaced some openInput variable checks to use verisons that aren't affected by players' frozen statuses. This removes the need for the psuedo-freeze that happens when viewing the minigame menu.
* Due to changed priorities relating to minigames, the only minigame that is guaranteed to end up in the final game is Battle Arena. Therefore, the platform in the middle of the room in Jane's Hut now serves as the entrance to the minigame, moving down after a destination is chosen.
* Added ***-1*** as a valid number for the ***xane_lowend*** CVAR. When this is chosen, the roads in City Street Run become reflective, which will not happen on normal (0) and performance (1) settings. This is due to even my gaming laptop lagging when the reflective roads are in sight and I would look to the opposite side of the open city area.
* More lights and reflective surfaces have been overall added to City Street Run. Additionally, a new room was added to the building with the walkway.
* The "absolute value" (abs) function has been moved out of COMMON1.acs to mma_extra.acs, so it can now be used in any script file.
* If the moving skybox is disabled in Uroboros (1-4), a fake, slow-moving tunnel is used for the background.