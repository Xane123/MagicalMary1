# Changes (v1.86)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.

Most importantly, this version is the first version to have compatibility with Delta Touch! Contact Beloko Games, become a beta tester, then purchase Delta Touch. Once you do:
* Switch its GZDoom version to v3.2 (arrow button)
* Choose Freedoom: Phase 2 as the IWAD and let it download it by pushing the play button.
* Extract the game data to SD Card > OpenTouch > Delta > mods
* Return to Delta Touch and tap the keyboard button and add all three files as mods.
* Start the game by tapping the play button again. If done correctly, a picture of Mary drinking from a restaurant cup should appear then the Xane Corp. logo. From here you can start the game, but it's very laggy on weaker processors, including the Google Pixel 2!
This isn't near as user-friendly as playing on computers, but it's necessary as it isn't just a couple simple downloads and extractions. You should be familiar with Android and mobile game touch screen controls before trying this, anyways.
## Bug-fixes
* The "Return to Hell City" and "Avoid Jail" glitches, which were in Mary's Magical Adventure for many versions, are now both fixed.
* If you fail a Special Stage then return to it through a second entrance in the same level, Mary/Xane won't become stuck in it.
* Attempting to visit a Special Stage when you have all of the Chaos Bridges through forcing it using the "changemap" CCMD will instantly kick you back out to the last level you were on.
* If the player tries to force themselves into a Special Stage they aren't currently on, they will be forced instantly onto the correct Special Stage. This isn't done if recording or playing back a demo, though.
## Major
* Jane's Shop's "random upgrade" item now works as intended and gives Mary hammer and umbrella upgrades. It doesn't tell you what you get, though, and I'm unsure what to do to make the tutorials appear as if Mary picked up an upgrade item.
* 1-2 now has more complete level design, though not all of it is as polished as other areas.
* The title screen video is now twice as long. As a result, "demos" that play these videos had to be re-recorded.
* Friendly Turrets are no longer broken; They may still disappear, wasting your money you spent on them, but they no longer:
** Stare at dead enemies' bodies after killing them...
** Revert to facing towards the right on the map; They now face the direction they were placed facing.
## Minor
* The coin and time requirements in Special Stage 4 were adjusted slightly.
* Downgraded Mary's front door to not use a camera texture as you couldn't see anything special happen outside it anyways.
* Reflections were removed in areas involving slopes as this would consistently cause lag on Windows and Android (Delta Touch). I recommend using "gl_plane_reflection 0" on Android to disable reflective surfaces.
* Added credits image for Delta Touch. This doesn't appear on computers as my source edits stop the image from being shown.
* Footstep sounds can now be turned off separately for the player and enemies (snd_footstepsplayer and snd_footstepsenemy respectively). You can toggle them in the sound options menu.