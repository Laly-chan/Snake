#include<windows.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27
#define enter 13

using namespace std;

void gotoxy(int,int);
void bordes();
void poscuerpo();
void moscuerpo();
void borrarcuerpo();
void teclas();
void movimiento();
void crearcomida();
bool chocar();
void menu();
void puntaje();
void guardar();
void altopunt();
void game_over();
void velocidad();

int x, y, t, n;
int cuerpo[259][2];
char tecla;
int dir, opc = 0;
int xc, yc, cc = 0;
int scr, spd, num, lim = 5;
char hiscr[5] = {'1' , '0'};

int main(){
	while (opc != 1){
		scr = 0; x = 40; y = 11; t = 4; n = 1; spd = 150; dir = 4;
		bordes();
		puntaje();
		menu();
		gotoxy(xc,yc); printf("*");
		if (opc == 0){
			while (tecla != esc){
				borrarcuerpo();
				poscuerpo();
				moscuerpo();
				
				if (cc == 0){
					crearcomida();
				}
				
				gotoxy(xc,yc); printf("*");
				
				if (xc == x && yc == y){
					t++;
					cc--;
					scr++;
				}
				
				if (scr > lim && spd > 40){
					velocidad();
				}
				
				gotoxy(9,0); printf(" "); cout<<scr;
				
				teclas();
				teclas();
				
				movimiento();
				
				if (chocar()){
					game_over();
					break;
				}
				
				Sleep(spd);
			}
		}
		system ("cls");
	}
	return 0;
}

void gotoxy(int x1, int y1){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x1;
	dwPos.Y = y1;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void bordes(){
	for (int i = 2; i < 78; i++){
		gotoxy(i,1); printf("%c",205);
		gotoxy(i,23); printf("%c",205);
	}
	
	gotoxy(1,1); printf("%c",201);
	gotoxy(78,1); printf("%c",187);
	gotoxy(1,23); printf("%c",200);
	
	for (int i = 2; i < 23; i++){
		gotoxy(1,i); printf("%c",186);
		gotoxy(78,i); printf("%c",186);
	}
	
	gotoxy(78,23); printf("%c",188);
}

void poscuerpo(){
	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;
	if (n == t){
		n = 1;
	}
}

void moscuerpo(){
	for (int i = 1; i < t; i++){
		gotoxy(cuerpo[i][0],cuerpo[i][1]);
		printf("%c",254);
	}
}

void borrarcuerpo(){	
	gotoxy(cuerpo[n][0],cuerpo[n][1]);
	printf(" ");
}

void teclas(){
	if (kbhit()){
		tecla = getch();
		switch (tecla){
			case up:
				if (dir != 2){
					dir = 1;
				} break;
			case down:
				if (dir != 1){
					dir = 2;
				} break;
			case left:
				if (dir != 4){
					dir = 3;
				} break;
			case right:
				if (dir != 3){
					dir = 4;
				} break;
		}
	}
}

void movimiento(){
	if (dir == 4) x++;
	if (dir == 3) x--;
	if (dir == 2) y++;
	if (dir == 1) y--;
}

void crearcomida(){
	xc = 2 + (rand()%76);
	yc = 2 + (rand()%21);
	
	gotoxy(xc,yc); printf("*");
	
	cc++;
}

bool chocar(){
	if (x == 1 || x == 78 || y == 1 || y == 23) return true;
	
	for (int i = 0; i < t; i++){
		if (x == cuerpo[i][0] && y == cuerpo[i][1]) return true;
	}
	
	return false;
}

void menu(){
	gotoxy(35,10); printf("Start");
	gotoxy(35,13); printf("Exit Game");
	gotoxy(33,10); printf("%c",62);
	gotoxy(0,0); printf(" ");
	tecla = right;
	
	while (tecla != enter){
		if (kbhit()){
			tecla = getch();
			if (tecla == up){
				gotoxy(33,13); printf(" ");
				gotoxy(33,10); printf("%c",62);
				gotoxy(0,0); printf(" ");
				opc = 0;
			} else if (tecla == down){
				gotoxy(33,10); printf(" ");
				gotoxy(33,13); printf("%c",62);
				gotoxy(0,0); printf(" ");
				opc = 1;
			}
		}
	}
	gotoxy(33,10); printf("       ");
	gotoxy(33,13); printf("           ");
}

void puntaje(){
	gotoxy(3,0); printf("Score: "); //9
	gotoxy(15,0); printf("Hi Score: ");
	altopunt();
	gotoxy(24,0); printf(" "); cout<<hiscr;
}

void guardar(){
	ofstream archivo;
	
	archivo.open("Save.sav",ios::out);
	
	archivo<<scr;
	
	archivo.close();
}

void altopunt(){
	ifstream archivo;
	
	archivo.open("Save.sav",ios::in);
	
	if (archivo.fail()){
		return;
	}
	
	while (!archivo.eof()){
		archivo.getline(hiscr,5);
	}
	
	archivo.close();
}

void game_over(){
	system("cls"); bordes();
	gotoxy(35,10); printf("Game Over");
	if (scr >= 10){
		gotoxy(32,12); printf("Final score: ");
		gotoxy(44,12); printf(" "); cout<<scr;
	} else {
		gotoxy(33,12); printf("Final score: ");
		gotoxy(45,12); printf(" "); cout<<scr;
	}
	num = atoi(hiscr);
	if (scr > num){
		guardar();
		gotoxy(32,14); printf("New High Score!");
		gotoxy(28,16); printf("Press Enter To Continue");
	} else {
		gotoxy(29,14); printf("Press Enter To Continue");
	}
	
	gotoxy(0,0); printf(" ");
	while (tecla != enter){
		if (kbhit()){
			tecla = getch();
		}
	}
}

void velocidad(){
	spd -=13;
	lim +=5;
}
