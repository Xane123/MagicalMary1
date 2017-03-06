# Mary's Magical Adventure

This is the ZDoom-based game engine used to power Mary's Magical Adventure _Most of Mary's Magical Adventure's modifications were programmed using ACS/DECORATE and won't be found within the source code, but some modifications like the Sonic-esque water behavior can be found here._

As with the engine it's based on, this can be compiled on Windows, Mac, and Linux using the tutorials availiable on ZDoom's wiki; Just replace any mentions of ZDoom's source code with this source code. Here's how to compile on [Windows](http://zdoom.org/wiki/Compile_ZDoom_on_Windows), [Mac](http://zdoom.org/wiki/Compile_ZDoom_on_Mac_OS_X), and  [Linux](http://zdoom.org/wiki/Compile_ZDoom_on_Linux).

ZDoom no longer supports compiling with Visual C++ 2005, so compiling for older Windows versions is no longer possible.

Mary's Magical Adventure's source code, due to it being based on ZDoom, is under the same [licenses](http://zdoom.org/wiki/License) as it.

Go [here](https://sites.google.com/view/xanem1/games/marys-magical-adventure) to visit Mary's Magical Adventure's official website. Its wiki can be found [here](https://worldofkirbycraft.miraheze.org/wiki/Main_Page).

## Request
If anyone visiting this repository knows how to do this, please make the modifications and send a pull request that does the following:
* Makes MAPINFO's "music" property be an integer.
* When loading a level, the game executes ACS script 254 with the first argument set to the "music" property's value.
