# Mary's Magical Adventure ![build status image](https://travis-ci.org/Xane123/MaryMagicalAdventure.svg?branch=master "Mac OS X Build Status (Travis CI)")
Mary's Magical Adventure (abbreviated MMA) is a first-person platforming game which uses a modified version of GZDoom. This is the source code, released as per the GPL 3.
## License
Mary's Magical Adventure's code is licensed under the GNU General Public License version 3, which has limited compatibility with CC-BY-SA, which MMA's music and other resources are licensed under. Additional licenses for other components that make up the engine can be found in /docs/licenses.
## Download & Setup
Builds are compiled with each git commit automatically by continuous integration services. Where their builds can be found varies.
### Windows (AppVeyor)
The latest Windows 64-bit builds can be found in the releases section as tag "appveyor-deploy". Download the ZIP file "mma_compiled.zip" then download the latest game data from [Xane's website](https://sites.google.com/view/xanem1/games/marys-magical-adventure) or a previous release (which may be outdated) the extract both to the same directory.

Run play.exe and the game should start if everything was done correctly. If it crashes with an error message at startup, run it again until it doesn't crash on startup.
### Mac OS X/Ubuntu (Travis CI)
The latest releases for non-Windows operating systems can be found in the __gh-pages__ branch. Download that branch as a ZIP file then extract it to your system. The executables and other files can be found in the main directory of the ZIP file.

To make this easier, Travis CI may be set up to use GitHub Releases like AppVeyor. Xane isn't familiar with UNIX-based operating systems so you may need to look up how to properly install the game.
## Credits (incomplete)
* id Software for Doom and its source code
* Randy Heit for ZDoom
* COleckers for GZDoom
* Nash for GZDoom-GPL
