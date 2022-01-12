# Magical Mary: Redthorn's Family Ransom
Magical Mary (also called Magical Mary 1, abbreviated MM1) is a first-person platforming game which uses a modified version of GZDoom. This is the source code, released as per the GPLv3.
## Download & Setup
* [![Windows 64-bit download badge](https://img.shields.io/badge/Windows_64bit-Download-green.svg)](https://storage.googleapis.com/mary-game-1/downloads/public/windows.zip)
* [![Ubuntu download badge](https://img.shields.io/badge/Ubuntu-Download-orange.svg)](https://storage.googleapis.com/mary-game-1/downloads/public/ubuntu.zip)
* The downloads above come with the game data, ensuring they are always compatible. Old builds/versions of this game (found in Releases) include the game data as a separate download.
## Notes about MacOS (problems, compiling, etc.)
* Due to not owning any MacOS devices, said OS's builds aren't provided in the same easy-to-use state as Windows and Ubuntu. Go to the [Actions tab](https://github.com/Xane123/MagicalMary1/actions), click on the latest commit, then download the MacOS artifacts at the bottom of that page.
* Extract that ZIP to one folder then move the files using Finder to another folder. This is needed to remove the restrictions on what files the application can access in modern MacOS versions.
* The game won't start unless you provide the game data and pre-compiled ZMusic library. For that, download the Windows or Ubuntu build above then extract its IPK3, PK3, and WAD files to the folder you moved the engine files to previously.
* For ZMusic, [clone the ZMusic repository](https://github.com/coelckers/ZMusic) then build it. You may need to install the prerequisites written on [ZDoom's wiki page about compiling for MacOS](https://zdoom.org/wiki/Compile_GZDoom_on_Mac_OS_X_11.2.2) before it will work. If it compiles, move the resulting library files to the same folder as the application.
* If the application cannot start, find a way to extract its files into the folder, then run the executable file directly. (I haven't used MacOS since I used a virtual machine so things may work differently than they did at that time, and UNIX libraries may not behave exactly as they do in Linux.
## License
Magical Mary's engine code is licensed under the GNU General Public License version 3, as with GZDoom.
## Credits (incomplete)
* id Software for Doom and its source code
* Randy Heit for ZDoom
* Christoph Oelckers (Graf Zahl) and all other contributors for GZDoom
