# Boa-Classic-Nokia-inspired-Snake-Game
This repository contains my project on a classic Nokia phone style snake game made on C++.

The snake game is quite popular among people, especially 90's kids.

#### This game takes a console input/output based approach on displaying objects and controlling the game.
  
### How to play:
1. Clone the repository and open the directory
2. Run main.exe
  
#### Game Controls:
* **Right Arrow Key** - to turn the snake right.
* **Left Arrow Key** - to turn the snake left.
* **Up Arrow Keyn** - to turn the snake up.
* **Down Arrow Key** - to turn the snake down.
<b>

### Files Description:
* *main.cpp* - contains the source code (thoroughly explained through comments)
* *main.o* - object code
* *main.exe* - executable file for game
* *makefile.win* - make file used to build the game and track version changes
<b>

### Libraries Used:
* *stdio.h* - for outputting to screen (printf() ).
* *conio.h* - for listening for keys pressed.
* *time.h* - for generating random numbers.
* *windows.h* - for laying out game windows.
<b>
  
### Code Description:
#### Functions: - Details of code are thoruoughly described in comments with the code itself.
* *void set_cursor_position(int x, int y)* - to change position of cursor for outputting text.
* *void set_console_color(int fg_color)* - to change text color at various points
* *void make_frame()* - to create the initial frame, set no of columns, rows and show instructions.
* *void show_score(int score)* - to update score on screen.
* *void show_highscore(int highscore)* - to update highscore on screnn.
* *int main()* - main activity handler - to run the game loops.
<b>

## *Thanks for viewing my project.*
#### This project taught me many general window handling skills (eg - Geometry of windows). The biggest challenge with the project was to make the snake move (head + body + tail). This part of code required lot of efforts figuring out the geometry of window had how to change positions on interval basis.
##### Hope you like the efforts.

Here's a snapshot of the game:
![alt text](https://github.com/tanmayvijay/Boa-Classic-Nokia-inspired-Snake-Game/blob/master/Boa%20-%20image.png)
<b><b>
  
Thank You. :)
