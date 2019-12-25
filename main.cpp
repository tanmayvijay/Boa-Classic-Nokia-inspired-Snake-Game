#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4



void go_to_xy(int x, int y)
{
 COORD position;
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 position.X = x;
 position.Y = y;
 SetConsoleCursorPosition(handle, position);
}


void objects_color(int fg_color){
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(handle, fg_color);
}



void make_frame(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cursor;
	
	cursor.dwSize=1;
	cursor.bVisible=false;
	SetConsoleCursorInfo(handle, &cursor);
	
	system("mode con:cols=120 lines=40");
	system("title Boa - Classic Nokia Style Snake Game");
	
	objects_color(3);
	printf("\n   %c", 218);
	for(int x=0;x<112;x++)
		printf("%c",196);
	printf("%c  ", 191);
	
	for(int x=0;x<33;x++){
		go_to_xy(3,x+2);
		printf("%c",179);
		go_to_xy(116,x+2);
		printf("%c ",179);
	}
	
	printf("\n   %c", 192);
	for(int x=0;x<112;x++)
		printf("%c",196);
	printf("%c  ", 217);
	
	
	go_to_xy(5,37);
	printf("Score: ");
	go_to_xy(5,38);
	printf("Highscore: ");
	
	go_to_xy(72,37);
	printf("Toggle Play/Pause - Spacebar");
	go_to_xy(72,38);
	printf("Quit - Q");
	
	objects_color(12);
}


void show_score(int score){
	go_to_xy(11,37);
	printf("%4d",score*10);
}


void show_highscore(int highscore){
	go_to_xy(15,38);
	printf("%4d",highscore*10);
}


int main(){
	make_frame();
	
	register int flow, size=8, i, x_food, y_food;
	int speed=850, restart=1, tmp, x_snake[100], y_snake[100], score=0, highscore=0;
	
	srand(time(NULL));
	while(true){
		if(restart){
			
			for(int j=4;j<116;j++)
				for(int k=2;k<35;k++){
					go_to_xy(j,k);
					printf(" ");
				}
				
			show_score(score);
			show_highscore(highscore);
			flow=RIGHT;
			x_snake[0]=40;
			
			for(i=0;i<size;i++){
				x_snake[i]=x_snake[0]-i*2;
				y_snake[i]=15;
			}
			
			objects_color(12);
			for(i=0;i<size;i++){
				go_to_xy(x_snake[i],y_snake[i]);
				printf("%c", 254);
			}
			
			for(tmp=1;true;){
					int x_temp = rand()%112;
					int y_temp = rand()%33+3;					
					x_food=x_temp + x_temp%2 + 4;				
					y_food=y_temp;
					
				for(i=0;i<size;i++)
					if(x_food==x_snake[i] && y_food==y_snake[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			go_to_xy(x_food,y_food);
			objects_color(6);
			printf("O");
			objects_color(12);
			restart=0;
		}
		
		while(!kbhit() && !restart)	{
			if(x_snake[0]==x_food && y_snake[0]==y_food){
				for(tmp=1;true;){
					int x_temp = rand()%112;
					int y_temp = rand()%33+2;					
					x_food=x_temp + x_temp%2 + 4;				
					y_food=y_temp;
					
					for(i=0;i<size;i++)
						if(x_food==x_snake[i] && y_food==y_snake[i]){
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				
				go_to_xy(x_food,y_food);
				objects_color(6);
				printf("O");
				objects_color(12);
				size++;
				score++;
				speed+=3;
				show_score(score);
			}
			go_to_xy(x_snake[size-1],y_snake[size-1]);
			for(i=size-1;i>0;i--){				
				x_snake[i]=x_snake[i-1];
				y_snake[i]=y_snake[i-1];
			}
			
			switch(flow){
				case RIGHT :x_snake[i]+=2; break;
				case LEFT :	x_snake[i]-=2; break;
				case UP :	y_snake[i]-=1; break;
				case DOWN :	y_snake[i]+=1; 
			}
			
			tmp=1;
			
			for(i=1;i<size;i++)
				if(x_snake[i]==x_snake[0] && y_snake[i]==y_snake[0]){
					tmp=0;
					break;
				}
				
			if(x_snake[0]>115 || x_snake[0]<4 || y_snake[0]<2 ||y_snake[0]>34)
				tmp=0;
				
			if(tmp){
				printf(" ");
				go_to_xy(x_snake[0],y_snake[0]);
				printf("%c", 178);	
				go_to_xy(x_snake[1],y_snake[1]);
				printf("%c", 254);	
			}
			else{
				objects_color(7);
				printf("%c", 254);
				go_to_xy(x_snake[1],y_snake[1]);
				printf("%c", 178);
				for(i=2;i<size;i++){
					go_to_xy(x_snake[i],y_snake[i]);
					printf("%c", 254);
				}
				if (score> highscore)
					highscore = score;
				score=0;
				restart=1;
				getch();
			}
			//delay(speed);
			Sleep(1000-speed);
		}
		char ch=getch();
		switch(tolower(ch)){
			case 'Q' : 	system("cls");
						return 0;
			case ' ' :	while(true){
							char z=getch();
							if(z=='Q')
								return 0;
							if(z==' ')
								break;
						}
						break;
			case -32: {
				char chh=getch();
				if(chh==72 && flow!=DOWN)
					flow=UP;
				else if(chh==80 && flow!=UP)
					flow=DOWN;
				else if(chh==75 && flow!=RIGHT)
					flow=LEFT;
				else if(chh==77 && flow!=LEFT)
					flow=RIGHT;
				break;
			}
		}
	}
}
