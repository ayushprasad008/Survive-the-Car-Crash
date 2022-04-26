#include<iostream>
#include<conio.h>
#include<dos.h> 
#include<windows.h>
#include<time.h>
#include<fstream>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<15; j++){
			gotoxy(0+j,i); 
			cout<<"±";
			gotoxy(WIN_WIDTH-j,i); 
			cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void gameover(){
	system("cls");
	
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t     Last Game Score:"<<score<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	
	highscore();
	cout<<"\t\tPress 9 and then any key to go back to menu."<<endl;
	
		do{
	
		char op = getche();
		
		if( op=='9')break; 
	
		
	}while(1);
    getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH - 6, 6);
	cout<<" Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\n NOTE: If you are LUCKY you can even play after hitting the other car(s)";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH - 6, 1);cout<<"----------";
	gotoxy(WIN_WIDTH - 6, 2);cout<<"  Car Game";
	gotoxy(WIN_WIDTH - 6, 3);cout<<"----------";
	gotoxy(WIN_WIDTH - 6, 4);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 5);cout<<"----------";
	gotoxy(WIN_WIDTH - 6, 7);cout<<"----------";
	gotoxy(WIN_WIDTH - 6, 8);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 9);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 10);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 11);cout<<"----------";
	gotoxy(WIN_WIDTH - 6, 12);cout<<" Control ";
	gotoxy(WIN_WIDTH - 6, 13);cout<<"---------- ";
	gotoxy(WIN_WIDTH - 6, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH - 6, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH - 6, 16);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 17);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 18);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 19);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 20);cout<<"           "; 
  gotoxy(WIN_WIDTH - 6, 21);cout<<"           ";
  gotoxy(WIN_WIDTH - 6, 22);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 23);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 24);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 25);cout<<"           ";
	gotoxy(WIN_WIDTH - 6, 26);cout<<"           "; 
    

	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 3;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 3;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameover();
			return;
		}
		if(score>=0 && score<25)
		Sleep(50); 
		else if(score>=25 && score<50)
		Sleep(40);
		else if(score>=50 && score<100)
		Sleep(30);
		else if(score>=100 && score<150)
		Sleep(20);
		else if(score>=150 && score<200)
		Sleep(10);
		else
		Sleep(5);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        Car Game        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";
		gotoxy(10,11); cout<<"3. Players List";	 
		gotoxy(10,12); cout<<"4. Quit";
		gotoxy(10,14); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') PlayersList();
		else if( op=='4') exit(0);
		
	}while(1);
	
	return 0;
}
