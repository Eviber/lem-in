# Lem-in

This program will find the best way to move "ants" from a specific room to another in a graph.

## Getting Started

### Usage

Lem-in reads on STDIN so you can just launch it and write your map:
```
./lem-in
```
or you can redirect an existing map:
```
./lem-in < map
```

### Prerequisites

You will need SDL2, SDL2\_GFX and SDL2\_TTF

Debian
```
sudo apt-get install sdl2 sdl2_gfx sdl2_ttf
```
OSX
```
brew install sdl2 sdl2_gfx sdl2_ttf
```

### Compiling

```
make all
```

## Example

A map should look like this:
```
42
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
```

It is composed of three parts:
* The number of ants
* The rooms
* The links

Comments can be anywhere but you have to specify the start and end rooms by putting the commands ##start ans ##end before declaring the room.

## Authors

* **[Sarah Brochard](https://github.com/everchild)**
* **[Youva Gaudé](https://github.com/Eviber)**
