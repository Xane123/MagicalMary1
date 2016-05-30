# World of Kirbycraft

This is the ZDoom-based game engine used to power World of Kirbycraft. _Most of World of Kirbycraft's modifications were programmed using ACS/DECORATE and won't be found within the source code, but some modifications like the Sonic-esque water behavior can be found here._

As with the engine it's based on, this can be compiled on Windows, Mac, and Linux using the tutorials availiable on ZDoom's wiki.

For example, compiling on [Windows](http://zdoom.org/wiki/Compile_ZDoom_on_Windows) and [Linux](http://zdoom.org/wiki/Compile_ZDoom_on_Linux) 

ZDoom no longer supports compiling with Visual C++ 2005, so compiling for older Windows versions is no longer possible.

World of Kirbycraft's source code, due to it being based on ZDoom, is under the same [licenses](http://zdoom.org/wiki/License) as it.

## Request
If anyone visiting this repository knows how to do this, please make the modifications and send a pull request that does the following:
* Makes MAPINFO's "music" property be an integer.
* When loading a level, the game executes ACS script 254 with the first argument set to the "music" property's value.
