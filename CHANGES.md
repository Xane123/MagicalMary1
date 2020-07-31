# Changes (for v2.2?)
This is a list of any changes done to Magical Mary 1 since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Fixed a glitch where gliding with Mary's parasol when sticking to walls would prevent checking for walls behind her, allowing her to do things like turn around and jump toward the wall she's on, or worse, sliding up to the invisible ceiling of **any** area, then gliding to anywhere she wants!
* Added extra code to Mary's downward Air Dash to cancel it if she's ever detected gliding (with her Pretty Parasol), sliding on a wall, or bouncing off a spring. (The latter should stop the boost mid-way through, which will lessen how much the player could tweak where springs bounce them to.
## Major
* None
## Minor
* For you mod programmers, if there's any of you here, GetSpeed has been updated with new parameters to control what axises are factored in. It's not the same as GetActorVel# though, as this returns integers that usually are large at even slower speeds.
* Addititonally, the ***RoundTo5*** function is no longer in COMMON1.acs, instead in the common script file "mma_extra.acs". It's also more freeform now, taking two arguments, one for the multiple to round to and a second one to pass your variable to.
* Running (moving fast in any way near the ground) no longer slowly regenerates your power. In fact, it does the opposite! Be careful with how much you run, as...moving your legs takes energy! Also, power can only be recovered if you're on the ground. Yeah, this sounds like a big downgrade but it both makes speed more "strategic" and discourages moving through the air to recover. Remember, Power Coins can still forcibly max out and freeze your power meter, and that if there's ever an item added that recovers power, it will work even in the air.