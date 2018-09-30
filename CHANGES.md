s# Changes (for v2.0)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Disabled "HandleHealthEvents" script in the Small Hut, which fixes the player randomly dropping coins upon warping there for a second time after losing health in the level.
* Fixed blue cops with rapid-fire behavior trying to run constantly. This was due to a leftover skip that caused the DECORATE code to skip the "if closer than 512 units, slowly walk" line, jumping straight to running. If playing on hard difficulty, the cop would endlessly slide into you!
* Lasers between Uroboros platforms have been re-added! This was due to removal of the laser projectiles, which were in the now-removed police DECORATE file used for the weaker police found in the scrapped first level.
* Mary no longer gets trapped in an endless loop of lowering her wand's Light Form after detransforming. This would happen even if said wand form wasn't unlocked yet.
## Major
* Upgrades are now non-linear! When a player picks up a weapon upgrade, a menu appears; Choose an upgrade from this menu then you will be given it! You can't see upgrades for weapons you don't have on-hand, and the final, fourth upgrade for each weapon can only be chosen once all other upgrades for that weapon are activated.
* Each weapon must have four upgrades due to the new upgrade menu, so Mary's Umbrella now has a new upgrade, Charged Burst! When used, Mary holds her umbrella back. When released, Mary quickly hits the enemy up to five times, depending on how long it was held back.
* Soap Boxes can be bought from Jane's Shop in packs of four! You can hold up to sixteen of them and place them anywhere to try catching enemies off-guard.
* Jane now has animated sprites using her "old design". If Jane ever gets a new design like Mary, her sprites will be replaced.
* You can now listen to the same radio "station" heard in City Street Run in Jane's Hut; Just cycle through all of the songs in the game using her radio and it will change to that! Do note that since the script that handles this is only on the level with Jane's Hut, 1-1 will instead play default music if none is chosen.
* The teleporter's controls are being moved to Xane's laptop; Push USE in front of it to start using it then choose Teleport-Hacker. Once it's migrated, the two switches will be removed.
* Thanks to ***dpJudas***' parallax shader, some textures have "depth" to them, most obvious on checker tiles.
* It was removed previously for **good reason**, but Mary now cries if hurt too much during combat, which will anger all enemies around you! If this happens, run and hide fast, as everyone will start trying to cheaply kill you.
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