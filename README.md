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

([video](https://youtu.be/aD20O2oQ1DQ))

A map should look like this:
```
20
a 0 0
##start
b 0 4
c 2 2
d 4 0
e 3 4
f 6 2
g 6 4
h 5 7
i 9 0
j 9 4
k 9 6
l 7 8
##end
m 12 4
n 12 8
a-b
b-e
e-g
g-j
j-m
#comment
a-d
d-i
i-j
b-c
c-f
f-g
e-h
h-l
l-n
n-m
g-k
k-m

```

It is composed of three parts:
* The number of ants
* The rooms
* The links

Comments can be anywhere but you have to specify the start and end rooms by putting the commands ##start and ##end before declaring the room.

## Authors

* **[Sarah Brochard](https://github.com/everchild)**
* **[Youva Gaudé](https://github.com/Eviber)**
