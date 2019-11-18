# Changes (for v2.1)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* It's unknown if this fixed anything, but now springs lock the player twice across two tics. This is in an attempt to fix a bug where the lock would immediately get removed due to the player being on-ground right as it's set.
* Xane Corp.'s glitched line portals are now fixed by ungrouping sectors.
* Added requirement for raindrops to be in the air for three tics before being able to play "splash" sounds. This fixes hearing rain sounds through the right wall around the first corner of the PWPD HQ hallway.
* Springs now allow movement if Mary starts gliding with her umbrella. Yep, before now, since the spring lock was added, Mary's umbrella was useless if springs were involved.
* Fixed oddity where Boost Panels would accelerate players to insane speeds if they left the ground! This was caused by the "pushvels" array having only two indices instead of **three.** Arrays counting from zero can be confusing...
* When the Drop Dash was removed, a script was deleted that allowed Xane's Claw to function. As of now, the claw works again.
## Major
* Checkpoints no longer store much information, now just storing the current music and the respawn point thing ID. Additionally, that thing ID is only used if the player can't be warped to their "last safe position", which was previously only used when warping back from the Small Hut or Special Stage.
* Level start points are no longer scripted warps; Before this version, your character would spawn in a small black room before being warped to where they start the level. This could fail, leading to the infamous "Black Room Glitch". Now, if nothing happens, the player will always appear at the beginning of the level, as intended. This also allows levels to have multiple starting points naturally, like when transitioning to and from the planned hub area, which will connect directly to the first level. Xane's special level starting point (TID 1995) will still use the old method, but it's so rarely used in the game's levels.
* Changed how rain sounds are generated. Now, every raindrop plays about a second of rain sound, chosen randomly from 18 sounds. This creates a more 3D sound and makes the rain more believable. Also, it improves how rain sounds when indoors near a door that leads out. It does cause sound glitches due to using a lot of "slots".
* Removed "auto wind" since I can't think of any real good use of it. As a result, wind only now moves in directions scripted during levels and is used more for currents more than wind.
* Also removed arbitrary disabling of movememnt when gliding using Mary's umbrella in higher wind speeds. The wind alone makes it hard to move against while gliding, so this artificial limitation isn't necessary.
* Xane's multiple flaps now have an "automatic" mode. Hold the jump button anytime in the air and Xane will automatically flap at an optimal rate until it's released. This will save your fingers from possibly hurting if you play this game a lot.
* A new status bar is (being) added, replacing the old one. The new status bar uses bigger meters that have the game's visual style.
* Armor was added! The power meter previously used armor internally, but now it uses its own inventory item.
* Trees are now very different than before. Previously, they were single images that didn't blend in, but currently use a combination of 2D images (for leaves) and a voxel model under it all. The leaves are randomly placed within areas, giving each tree its own appearance and also allowing you to damage the tree and its leaves.
* Added hiragana and katakana to the main font in case there's ever a Japanese text localization.
## Minor
* In 1-3, the beach area was removed, and the bridge that comes from 1-2 is now visible from the windows of the original intro building.
* Added a "detection" mechanic to PWPD HQ. Upon entering, H-Computer alerts everyone to your presence, then warns about detectors scanning your character. Little black areas with red lasers firing from them are in some hallways, and if you don't jump over the laser, you'll be "scanned". This causes the lights to go out, alarms begin sounding, and bars lower to prevent exiting the building (though it's still possible to exit). Enemies will always be aware of your presence once this happens.
* Rain ambience no longer uses a separate low frequency and high frequency version of the sounds. Instead, the low frequency plays around the player as before while *normal* frequency sounds play sround the player, as stated abvoe.
* Ambience script was updated to use the ambient sound object (TID 1080 + player number) that the low-frequency rain and thunder sounds use.
* The ambience script uses a much easier to edit system than before, now not a linear list of sounds.
* Corrected internal order of coins in the "AddCPowerupTics" ACS script.
* Dropped coins play more realistic sounds upon hitting the ground, with longer "ching" sounds if hitting it quickly. Also, dropped coins have height variation now, so coins will look more unique and less like clones now.
* A new song was added (#15), which plays in Special Stages, replacing #14, "The Peaceful Dimension".
* Special Stages now require collecting large magic stars instead of ordinary coins.
* The "endless Special Stage" event flag (array index [3]) was added, which will be used before the final boss eventually. When finished, this will lock the player into the Special Stage chain until all seven are completed.
* Large magic stars collectable in Special Stages can now be picked up and can be used to complete the Special Stage without problems.
* Lights were added to City Street Run's bowling alley vent to be consistent with Peacewater Prison's vents.
* Leaves drop from trees when it's raining or wind is blowing.
* Support for different foliage colors per level has been implemented. Currently, tree leaf clusters distant "imposter" tree renders change color accordingly, but leaves are still all green.
* Menu sounds were changed (again). I just can't decide how things should sound in this game!
* Juice inside of half-drank juice cylinders now can go stale if not drank within 90 (orange) or 120 (apple) seconds. If it goes stale, the remaining juice in he container is forcibly removed from your inventory.
* Proximity mines now are tinted slightly orange around the mini-thrusters at each corner, a bit of fake lighting.
* Added light pink fade in (12) and out (13). Use SetFadeOut script to see them, though they will be used for the World Map.