# cmake-21.4-rpg-turn-based-game
Task 21-4

Implement a highly simplified version of a role-playing turn-based game.

The game takes place on a 20x20 square map. Enemies and the player's character move around the cells.

After each player's turn, the map is shown again with all the enemies on it. The player is marked with the letter P, enemies with the letter E, empty spaces with a dot.

Each character in the game is represented as a structure with fields: name, lives, armor, damage.

At the beginning of the game, 5 random enemies are created in random cells of the map. Enemies are named in the format Enemy #N, where N is the number of the enemy. Enemies hit points are set randomly from 50 to 150. Armor levels vary from 0 to 50. Damage is also randomly selected from 15 to 30 units.

The player designs his own character. Sets all its parameters, including the name.

All characters spawn in random locations on the map.

The player moves with the following commands: w, a, s, d. Depending on the command, the direction of movement of the character is selected: left, right, up, down.

Enemies move in a random direction.

If a character (enemy or player) moves to the side where some character is already located, then he hits this character with his damage. Enemies at the same time never beat enemies, but simply skip a turn and remain in their place. Nobody can walk outside the map (20 by 20 cells). If someone has chosen a direction beyond what is permitted, the move is skipped.

The formula for calculating damage is the same as the one in the lesson. Lives are reduced by the remaining damage after the armor. In this case, the armor is also reduced by the reduced damage.

The game ends when either all enemies die or the player's character dies. In the first case, a message about the defeat is displayed on the screen, in the second - a victory.

If at the beginning of the turn the player enters the save or load command instead of the direction of movement, then the game either saves its state to a file or loads this state from a file, respectively.
