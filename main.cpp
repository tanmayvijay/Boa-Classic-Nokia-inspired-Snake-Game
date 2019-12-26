// basic imports
#include<stdio.h> // for printf
#include<conio.h> // for listening to keys pressed
#include<time.h> // for random numbers
#include<windows.h> // for layout

// basic directional constants
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4


// function to move the cursor to specific locations before printing
void set_cursor_position(int x, int y)
{
 COORD position;
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 position.X = x;
 position.Y = y;
 SetConsoleCursorPosition(handle, position);
}


// setting color of objects appearing on screen before printing them
void set_console_color(int fg_color){ // fg_color = foreground color
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(handle, fg_color);
}


// function to make boundary, layout, Instructions, Score chart, etc
void make_frame(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cursor;
	
	// hiding the cursor from console screen
	cursor.dwSize=1;
	cursor.bVisible=false;
	SetConsoleCursorInfo(handle, &cursor);
	
	system("mode con:cols=120 lines=40"); //setting frame size
	system("title Boa - Classic Nokia Style Snake Game"); // setting title
	
	//printing top edge
	set_console_color(4);
	printf("\n   %c", 218);
	for(int x=0;x<112;x++)
		printf("%c",196);
	printf("%c  ", 191);
	
	//printing left and right edges
	for(int x=0;x<33;x++){
		set_cursor_position(3,x+2);
		printf("%c",179);
		set_cursor_position(116,x+2);
		printf("%c ",179);
	}
	
	// printing right edge
	printf("\n   %c", 192);
	for(int x=0;x<112;x++)
		printf("%c",196);
	printf("%c  ", 217);
	
	// displaying score
	set_cursor_position(5,37);
	printf("Score: ");
	set_cursor_position(5,38);
	printf("Highscore: ");
	
	// displaying instructions
	set_cursor_position(72,37);
	printf("Toggle Play/Pause - Spacebar");
	set_cursor_position(72,38);
	printf("Quit - Q");
}



//function to display current score
void show_score(int score){
	set_cursor_position(11,37);
	printf("%4d",score*10);
}



// function to display 'best' highscore
void show_highscore(int highscore){
	set_cursor_position(15,38);
	printf("%4d",highscore*10);
}



// driver function
int main(){
	make_frame(); // to display boundries, instructions and scores
	
	//initializations
	int direction, snake_length=8, i, x_food, y_food, speed=850, restart=1, temp, x_snake[100], y_snake[100], score=0, highscore=0;
	
	srand(time(NULL));
	while(true){
		if(restart){ // at every restart of game
			
			// clearing the frame on every restart
			for(int j=4;j<116;j++)
				for(int k=2;k<35;k++){
					set_cursor_position(j,k);
					printf(" ");
				}
				
			// displaying the scores
			show_score(score);
			show_highscore(highscore);
			
			direction=RIGHT; // initializing snake direction
			
			// initializing snake
			x_snake[0]=40;
			for(i=0;i<snake_length;i++){
				x_snake[i]=x_snake[0]-i*2; //alternating blocks
				y_snake[i]=15;
			}
			
			// printing the snake
			set_console_color(12);
			for(i=0;i<snake_length;i++){
				set_cursor_position(x_snake[i],y_snake[i]);
				printf("%c", 254);
			}
			
			// getting food location
			for(temp=1;true;){
					int x_temp = rand()%112;
					int y_temp = rand()%33+2;					
					x_food=x_temp + x_temp%2 + 4;				
					y_food=y_temp;
					
				// if snake eats food, we get new location until snake doesnt eat it
				for(i=0;i<snake_length;i++)
					if(x_food==x_snake[i] && y_food==y_snake[i]){
						temp=0; break;
					} // here we don't increase length of snake, if initial position of snake and food is same
				
				// if snake doesnt eat, location is okay
				if(temp)
					break;
			}
			
			// printing the food object at location
			set_cursor_position(x_food,y_food);
			set_console_color(6);
			printf("%c", 220);
			set_console_color(12);
			
			restart=0; // resetting restart variable to mark that game is
						// continuously running
		
		} // end restart-code
		
		// if no key is hit, snake movies in 'direction'
		while(!kbhit() && !restart)	{ // if game continues and no key is hit
		
			if(x_snake[0]==x_food && y_snake[0]==y_food){ // if snake eats, get new location for food
				
				for(temp=1;true;){
					int x_temp = rand()%112;
					int y_temp = rand()%33+2;					
					x_food=x_temp + x_temp%2 + 4;				
					y_food=y_temp;
					
					for(i=0;i<snake_length;i++)
						if(x_food==x_snake[i] && y_food==y_snake[i]){
							temp=0; break;
						}
					if(temp)
						break;
				}
				
				// print the food
				set_cursor_position(x_food,y_food);
				set_console_color(6);
				printf("%c", 220);
				set_console_color(12);
				
				// snake eats --> gets bigger
				snake_length+=2;
				score += (snake_length-8); // score increases
				speed+=3; // game gets tough
				
				// updating score
				show_score(score); 
				
			} // end if (snake eats)
			
			
			set_cursor_position(x_snake[snake_length-1],y_snake[snake_length-1]); // go to snake tail
														// before updating it
			
			// move snake body forward
			for(i=snake_length-1;i>0;i--){				
				x_snake[i]=x_snake[i-1];
				y_snake[i]=y_snake[i-1];
			}
			
			// move snake head forward
			switch(direction){
				case RIGHT :x_snake[i]+=2; break;
				case LEFT :	x_snake[i]-=2; break;
				case UP :	y_snake[i]-=1; break;
				case DOWN :	y_snake[i]+=1; break;
				default : break;
			}
			
			temp=1; // if snake is alive
			
			// check if snake hits itself
			for(i=1;i<snake_length;i++)
				if(x_snake[i]==x_snake[0] && y_snake[i]==y_snake[0]){
					temp=0; // snake dies
					break;
				}
				
				
			// check if snake hits the boundary
			if(x_snake[0]>115 || x_snake[0]<4 || y_snake[0]<2 ||y_snake[0]>34)
				temp=0; // snake dies
			
			
			
			// if snake is alive
			if(temp){
				printf(" "); // remove tail
				
				//print new head
				set_cursor_position(x_snake[0],y_snake[0]);
				printf("%c", 178);
				
				// change old head position to body (other body parts remain same 
				// (except head, part nexrt to head and tail) )
				set_cursor_position(x_snake[1],y_snake[1]);
				printf("%c", 254);	
			}
			// if snake is dead
			else{
				set_console_color(7); // make it white
				printf("%c", 254); // tail
				set_cursor_position(x_snake[1],y_snake[1]); // head (showing it at its prev position only,
				printf("%c", 178); // ie position before hitting)
				
				// make rest of the snake white
				for(i=2;i<snake_length;i++){
					set_cursor_position(x_snake[i],y_snake[i]);
					printf("%c", 254);
				}
				
//				update highscore
				if (score> highscore)
					highscore = score;
				score=0; // reset score
				restart=1; // game starts from start, but with snake length 
							// acquired in last game
							
				snake_length = 8;

			}
			
			// more the speed, less the program sleeps, faster the snake moves
			if (speed>=1000) speed = 950 + (speed%1000);
			Sleep(1000-speed);
		} // end while - no key hit and not new game
		
		// input key
		char ch=getch();
		switch(tolower(ch)){
			case 'q' : 	system("cls"); // if key=q, exit
						exit(0);
			case ' ' :	while(true){ // if key=' ' --> pause
							char z=getch();
							if(z=='q')
								return 0;
							if(z==' ')
								break;
						}
						break;
			case -32: { // arrow keys
				char chh=getch();
				if(chh==72 && direction!=DOWN)
					direction=UP;
				else if(chh==80 && direction!=UP)
					direction=DOWN;
				else if(chh==75 && direction!=RIGHT)
					direction=LEFT;
				else if(chh==77 && direction!=LEFT)
					direction=RIGHT;
				break;
			}
		}
	}
}
