_This project has been created as part of the 42 curriculum by elangari, rselva-2._

# Cub3D

## Description
The goal of this project is to create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting.

Only the use of the minilibx, the math library and a few other functions was allowed.

## Instructions
### Installation and Compilation
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

```
git clone https://github.com/Carbonard/42-cub3d.git cub3D
```

```
cd cub3D && make && cub3D [map_file.cub]
```

### Usage
#### Menu
- Press `P` go to the menu. 

- To start the game select `PLAY`.

- Select `SETTINGS` to choose the map or adjust the character's speed, camera speed, and FPS.

- To quit the game select `EXIT` or press `ESC`.

#### Moving through the map
- Use the the keys `A`, `W`, `S` and `D` to walk.

- To move the camera use the directional keys or the mouse. Press `M` to disable the mouse.

#### Using the sonic
To open/close doors and kill enemies, aim for the center of the screen and press `SPACE`.

#### Add your own maps and textures!
To execute the game, a map file must be added as an argument. The file must follow this requirements:

- The file name must end with `.cub`.

- Every element on the map must be given a texture. Said texture can be either an RGB code or a `.xpm` file, following this format:
	```
	NO ./img/backroom_wall.xpm
	SO ./img/backroom_wall.xpm
	EA ./img/backroom_wall.xpm
	WE ./img/backroom_wall.xpm
	F 187,135,57
	C 130,130,100
	```

- The textures must be placed before the map on the file, but the order they are in is not relevant.

- Every texture can have an animation if you give it multiple `.xpm` files or RGB colors (max 32), separated by spaces.

	> **Texture key:**
	>- C -> ceiling.
	>- F -> floor.
	>- NO -> North wall.
	>- SO -> South wall.
	>- EA -> East wall.
	>- WE -> West wall.
	>- D -> door (only needed if on the map).
	>- e -> exit (only needed if on the map).
	>- f -> enemy (only needed if on the map).
	>- ex -> explosion/dying enemy (optional).

- The map must be closed (completely surronded by walls) and just one player must be placed on it.

	> **Map Key:**
	>- 1 -> Wall.
	>- 0 -> Floor, empty space in the map.
	>- D -> Closed door (optional).
	>- d -> Open door (optional).
	>- e -> Exit (you win getting to this square)(optional.)
	>- f -> Enemy (foe) (you die if you touch them, they die if shooted)(optional).
	>- Player characters, only one can be placed on the map:
	>	- E -> spawn looking East.
	>	- W -> spawn looking West.
	>	- N -> spawn looking North.
	>	- S -> spawn looking South.

## Resources
[Raycasting guide](https://lodev.org/cgtutor/raycasting.html)

### AI usage
Chat GPT was used to better understand how to optimize the code and to generate the Doctor's hand and Sonic.
