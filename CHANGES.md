s# Changes (for v2.0)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* Disabled "HandleHealthEvents" script in the Small Hut, which fixes the player randomly dropping coins upon warping there for a second time after losing health in the level.
## Major
* Upgrades are now non-linear! When a player picks up a weapon upgrade, a menu appears; Choose an upgrade from this menu then you will be given it! You can't see upgrades for weapons you don't have on-hand, and the final, fourth upgrade for each weapon can only be chosen once all other upgrades for that weapon are activated.
* Each weapon must have four upgrades due to the new upgrade menu, so Mary's Umbrella now has a new upgrade, Charged Burst! When used, Mary holds her umbrella back. When released, Mary quickly hits the enemy up to five times, depending on how long it was held back.
* Soap Boxes can be bought from Jane's Shop in packs of four! You can hold up to sixteen of them and place them anywhere to try catching enemies off-guard.
* Jane now has animated sprites using her "old design". If Jane ever gets a new design like Mary, her sprites will be replaced.
* Wall Jumps can now only be performed on certain walls. This may limit its usage and make it inconsistent what you can wall jump off of, but this prevents glitches where Mary could (frustratingly) stick to thin air nearly every time she performed the Air Dash. This also prevents "sticking to" enemies (then getting hurt). Think of it like Xane's claw nerfing that happened previously.
## Minor
* Xane's thrown hammer now is affected by gravity. It has less gravity for a few split-seconds but falls quicker after that.
* Jane's Shop is now complete; The last two slots were filled by **Soap Box ×4** and **Ability Upgrade**!
* Friendly Turrets are now placed slightly closer to the player.
* Buffed Soap Boxes slightly; Soap that lands on the ground deals more damage over time and flies farther from the Soap Box. Additionally, Soap Boxes have less health, so a single hammer attack makes them explode now.
* Magical Cutie Mary isn't affected by cops' stunning bullets and other special pain reactions.
* Disabled draw distance in Jane's Hut as the area is too small to need it. All other levels can still have it enabled.
* Checkpoints no longer store the player's angle. This is to clear a **SetCheckpoint** script argument slot for a "forced ambience" argument, which will fix cases where the wrong ambience is heard upon returning to a checkpoint.