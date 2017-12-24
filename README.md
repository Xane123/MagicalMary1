# Mary's Magical Adventure ![AppVeyor build badge](https://ci.appveyor.com/api/projects/status/github/Xane123/MaryMagicalAdventure?svg=true) ![Travis build status image](https://travis-ci.org/Xane123/MaryMagicalAdventure.svg?branch=master "MacOS/Ubuntu Build Status (Travis CI)")
Mary's Magical Adventure (abbreviated MMA) is a first-person platforming game which uses a modified version of GZDoom. This is the source code, released as per the GPLv3.
## License
Mary's Magical Adventure's code is licensed under the GNU General Public License version 3, which has limited compatibility with CC-BY-SA, which MMA's music and other resources are licensed under. Additional licenses for other components that make up the engine can be found in /docs/licenses.
## Download & Setup
### Google Drive downloads
Due to the problems mentioned above, you can download the latest builds from Xane's Google Drive.
* [![Windows 64-bit download badge](https://img.shields.io/badge/Windows%20(64%20bit)-Download-green.svg)](https://drive.google.com/file/d/0Bx2t_-Mbdk3yQ2FsYVNKTUdPQlU/view?usp=sharing)
* [![MacOS download badge](https://img.shields.io/badge/MacOS-Download-blue.svg)](https://drive.google.com/file/d/0Bx2t_-Mbdk3ycl9mVktHQjVtZHM/view?usp=sharing)
* [![Ubuntu download badge](https://img.shields.io/badge/Ubuntu-Download-red.svg)](https://drive.google.com/file/d/0Bx2t_-Mbdk3ycWxfb2tkRGpvT3M/view?usp=sharing)
### Problems
There's a reason why those are not on GitHub. AppVeyor (Windows) and Travis (MacOS and Ubuntu) automatically build any changes made to the source code. However, both have problems; AppVeyor's builds (found under releases as __appveyor-deploy__) don't have OpenAL/sound and Travis only deploys a single OS' build at a time, overwriting whatever's in the __gh-pages__ branch. This means only MacOS or Ubuntu's build will be found there.
## Credits (incomplete)
* id Software for Doom and its source code
* Randy Heit for ZDoom
* COleckers for GZDoom
* Nash for GZDoom-GPL
