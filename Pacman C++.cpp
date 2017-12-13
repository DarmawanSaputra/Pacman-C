#include <iostream>
#include <conio.h>
using namespace std;

//Function definition
void control(char key);
void move();
void renderMap();
void actionTrigger();
void win();
void lose();
void respawn();
void AIMonster(char type);

//Global variable
bool isOver = false;
char inputControl;
int health = 3;
int coin = 10;
int x = 1;
int y = 1;
int v_x = 0;
int v_y = 0;

//Respawn point variable
int r_x = 1;
int r_y = 1;
char map[26][80]=
	{
	"[=====^==============^=====^===============^=======^======^======^============]",
	"|P    |              |  C  |               |       |      |      |            |",
	"|     |              |     |               |       |      | M    |            |",
	"|     |              |     |               |       |      |      |            |",
	"|     (==============)     (===============)       |      |      (============>",
	"|                                                M |      |                C  |",
	"|     [==============]     [===============]       |      |      [============>",
	"|     |              |  M  |               |       |      |   M  |            |",
	"|     (==============)     (===============)       (======)      (============>",
	"|C      M                                                                     |",
	"<====================]C    [=====#    #====]       [======]     [========]    |",
	"|                    |     |               |  C    |      |     |        |    |",
	"|                    |     |               |       |      |     |        |    |",
	"<====================)     (===============)       (======)     (========)    |",
	"|                                                                             |",
	"|     [======================]    [=================]     [==========]    [===>",
	"|     |                      |    |                 |     |          |    |   |",
	"|  C  |                      | C  |                 |     |          |    |   |",
	"|     (======================)    (=================)     (==========)    (===>",
	"|                                                                          C  |",
	"<===============]     [===============]     [=================]    [==========>",
	"|               |     |               |   C |                 |    |          |",
	"<===============)     (===============)     (=================)    (==========>",
	"|                                                             M             C |",
	"|                                   M                                         |",
	"(=============================================================================)",
	};
	

main() {
	bool firstTime;
	while(!isOver) {
		if(!firstTime) {
			renderMap();
			firstTime = true;
		}
		
		//Get player control key pressed
		if(kbhit()) {
			inputControl = getch();
			control(inputControl);
			
			//Render the arena
			system("cls");
			renderMap();
		}
	}
}

void control(char key) {
	//Reset
	v_x = 0;
	v_y = 0;
	
	//Move to top
	if(key == 'W' || key == 'w')
		v_y = -1;
	//Move to left
	else if(key == 'A' || key == 'a')
		v_x = -1;
	//Move to bottom
	else if(key == 'S' || key == 's')
		v_y = 1;
	//Move to right
	else if(key == 'D' || key == 'd')
		v_x = 1;	
	
	move();
}

//The implement of move() function
void move() {
	if(v_x != 0 || v_y != 0) {
		//Obstacle check
		if(y + v_y < 0 || x + v_x < 0)
			return;
			
		char t = map[y + v_y][x + v_x];
		if(t == '=' || t == '|' || t == '^' || t == '%' || t == '<' || t == '>' || t == '[' || t == ']' || t == '(' || t == ')') {
			return;
		}
		
		//Call what event will be trigger
		actionTrigger();
	}
}

//The implement of renderMap() function
void renderMap() {
	cout<<"==== CREDIT BY: Darmawan Saputra & Mayvan Gandhy ===="<<endl<<endl;
	cout<<"Sisa Nyawa: "<<health<<endl;
	cout<<"Sisa Koin: "<<coin<<endl<<endl;
	
	for(int i=0; i<26; i++){
		for(int j=0; j<80; j++){
			char t = map[i][j];
			
			if(t == '=')
				cout<<char(205);
			else if(t == '|')
				cout<<char(186);
			else if(t == '#')
				cout<<char(206);
			else if(t == '^')
				cout<<char(203);
			else if(t == '<')
				cout<<char(204);
			else if(t == '>')
				cout<<char(185);
			else if(t == '%')
				cout<<char(202);
			else if(t == '[')
				cout<<char(201);
			else if(t == ']')
				cout<<char(187);
			else if(t == '(')
				cout<<char(200);
			else if(t == ')')
				cout<<char(188);
			else
				cout<<t;
		}
		cout<< endl;
	}
}

//The implement of actionTrigger() function
void actionTrigger() {
	char nextChar = map[y + v_y][x + v_x];
	
	//Event if pacman met monster
	if(nextChar == 'M') {
		health--; //Decrease the value of health
		
		//Check if health < 1
		if(health < 1)
			lose();
		else
			respawn();
	}
	
	//Event if pacman met coin
	else if(nextChar == 'C') {
		coin--; //Decrease the value of coin
		
		map[y][x] = ' '; //Clear
		
		x = x + v_x;
		y = y + v_y;
		
		map[y][x] = 'P'; //Move
		
		//Check if health < 1
		if(coin < 1)
			win();
	}
	
	//Event if nothing happen, just move
	else {
		map[y][x] = ' '; //Clear
		
		x = x + v_x;
		y = y + v_y;
		
		map[y][x] = 'P'; //Move
	}
}

//The implement of respawn() function
void respawn() {
	map[y][x] = ' '; //Clear
	
	x = r_x;
	y = r_y;
	
	map[y][x] = 'P'; //Move
}

//The implement of win() function
void win() {
	isOver = true;
	cout<<"\n\nYOU'RE WIN!!!\n\n";
	system("pause");
}

//The implement of lose() function
void lose() {
	isOver = true;
	cout<<"\n\nYOU'RE LOSE!!!\n\n";
	system("pause");
}

//The implement of AIMonster(char type) function
void AIMonster(char type) {
	
}
