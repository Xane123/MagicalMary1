# Changes (for v1.95 or v2.0)
This is a list of any changes done to Mary's Magical Adventure since the last release. They will be included in the list of changes for the release when it happens.
## Bug-fixes
* The version number on the title screen was corrected to v1.9.
* Xane's claw now uses the *Animation3* inventory item instead of *Animation2*. Before this, enemies could be provoked like if Mary cried near them if Xane tried firing his claw.
* Mary no longer gets teleported as the screen fades out at the end of Isle Hell City (1-1). This was because the script that prevented the "stuck in Hell City" glitch didn't have its right boundary extended far enough into the fake 1-2 corridor at the end of Mary's path.
* You don't randomly get the Green Key when 1-1 loads anymore.
* Burning weaker cops (1-1 only) now make the yelling sound while on fire.
* Weaker cops (1-1's variants) now respond to being burned. firing a single bullet (blue) or a burst of bullets (green).
* Warping from the Battle Arena minigame is now impossible. This fixes a glitch where you could return to the Small Hut and use the teleporter to return to Isle Hell City (1-1), which should be impossible once you enter Rooftop to Rooftop (1-2).
## Major
* Health and jump height can be upgraded by picking up upgrade items for them, which are separate from weapon upgrade items.
* Mary's Hammer Slam attack behaves differently now; Instead of activating based on height alone, which could lead to unfair deaths, it now activates if at a high enough height **and** the attack button is held down. Briefly pressing the attack button will do the normal hammer attack now, even in mid-air!
* Reverted the bubble spawner's behavior to World of Kirbycraft v1.4's true randomness. This was done as the new system was ironically **too** predictable.
## Minor
* Making it to the end of an area with more than 15 coins will automatically send them to the bank in the Small Hut, but some coins will be removed. Additionally, if transformed even less will be stored in the bank. This was done to encourage the player to warp to the Small Hut and add them to the bank manually, which could give them interest in buying things from its shop or trying out minigames. Those give the player a lot of coins if played well.
* Lovely Heart's big heart-shaped projectile isn't treated as a "powerful projectile" to enemies anymore. This was done so enemies like cops wouldn't jump over Magical Cutie Mary's attacks, which would waste the five coins it takes to perform the attack.		
* Mary's "falling scream" sprites have been re-added into the game, but in the new art style.
* The drill in the Small Hut now functions. It costs 100 coins to "dig a tunnel" to the blue building seen in the first area. The building will contain minigames which will give Mary/Xane extra coins, making it worth the price.
* Mary's Hammer Slam now maintains momentum. This feels more natural and lets Mary "launch" herself at enemies. The Hammer Slam's height it activates at was raised to 1½ stories (192 units) off the ground. This makes it harder to perform the more powerful slams but improves balance. Perform the downward Air Dash before it for a boost forward upon landing!