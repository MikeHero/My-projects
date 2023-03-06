#include <iostream>
#include <string.h>
#include <signal.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream f("xboardtoeng.txt");
ofstream g("engtoxboard.txt");

void initNewGame(int board[9][9], int *turn, int *forceMode, int *engineColor, vector<int> *history) {
	int i,j; 
	for (i = 1; i <= 8; i++) 
		for (j = 1; j <= 8; j++) 
			board[i][j] = 0;
	/*	construiesc board 
		valoare camp=0 : nicio piesa pe el
		valoare camp:
			1=pion 
			2=nebun
			3=cal
			4=tura
			5=regina
			6=rege
			negativ=negru
			pozitiv=alb

		exemplu valoarea unui camp din matrice= +3 
		=> in acel camp se afla un cal care apratine jucatorului alb
	 */

	/* pioni albi si negri */
	for(i=1;i<=8;i++){
		board[2][i]=1;				// pionii albi
		board[7][i]=-1;				// pionii negri 
	}

	/* nebuni albi si negri */
	board[1][3]=board[1][6]=2;		// nebunii albi
	board[8][3]=board[8][6]=-2;		// nebunii negri

	/* cai albi si negri */
	board[1][2]=board[1][7]=3;		// caii albi
	board[8][2]=board[8][7]=-3;		// caii negri

	/* ture albe si negre */
	board[1][1]=board[1][8]=4;		// ture albe
	board[8][1]=board[8][8]=-4;		// ture negre

	/* regina alb si negru */
	board[1][4]=5;
	board[8][4]=-5;

	/* rege alb si negru */
	board[1][5]=6;
	board[8][5]=-6;

	//Default settings
	history->clear();
	*turn = 1; //Set white on move.
	*forceMode = 0; //Leave force mode.
	*engineColor = -1; //Set engine to play with black.
}

bool userMoves(char s[]) {


	if(strlen(s) < 4) return false;
	bool isMove = true;

	if( 'a'>s[0] || s[0]>'h' )	
		isMove=false;

	if( '1'>s[1] || s[1]>'8')
		isMove=false;
	
	if( 'a'>s[2] || s[2]>'h' )
		isMove=false;
	
	if( '1'>s[3] || s[3]>'8')
		isMove=false;
	return isMove;
}

void initCoordinates(char s[4], int *i1, int *j1, int *i2, int *j2) {	
	// (i1,j1) = coordonate initiale ; 
	// (i2,j2)=coordonate finale

	char c=s[0];
	// switch(c)
	// {	case 'a':	{*j1=1;	break;}
	// 	case 'b':	{*j1=2; break;}
	// 	case 'c':	{*j1=3;	break;}
	// 	case 'd':	{*j1=4;	break;}
	// 	case 'e':	{*j1=5;	break;}
	// 	case 'f':	{*j1=6;	break;}
	// 	case 'g':	{*j1=7;	break;}
	// 	default:{*j1=8; }
	// }
	*j1 = c - 'a' + 1;

	c=s[1];
	*i1=c-'0';
	c=s[2];
	// switch(c)
	// {	case 'a':	{*j2=1;	break;}
	// 	case 'b':	{*j2=2; break;}
	// 	case 'c':	{*j2=3;	break;}
	// 	case 'd':	{*j2=4;	break;}
	// 	case 'e':	{*j2=5;	break;}
	// 	case 'f':	{*j2=6;	break;}
	// 	case 'g':	{*j2=7;	break;}
	// 	default:{*j2=8; }
	// }
	*j2 = c - 'a' + 1;

	c=s[3];
	*i2=c-'0';
}

char PromNrToChar( int x)
{
	if(x%4==0) return 'b';
	if(x%4==1) return 'n';
	if(x%4==2) return 'r';
	return 'q';
}

int PromCharToNr(char c)
{
	if( c=='b' ) return 2;
	if( c=='n' ) return 3;
	if( c=='r') return 4;
	return 5;
}

void generateHalfStringMove (int i, int j, char move[2]) {
	// switch(j)
	// {	case 1:		{move[0]='a';break;}
	// 	case 2:		{move[0]='b';break;}
	// 	case 3:		{move[0]='c';break;}
	// 	case 4:		{move[0]='d';break;}
	// 	case 5:		{move[0]='e';break;}
	// 	case 6:		{move[0]='f';break;}
	// 	case 7:		{move[0]='g';break;}
	// 	default:	{move[0]='h';		 }	
	// }

	move[0] = 'a' + j - 1;
	move[1] = i + '0';
	move[2] = '\0';
}

void generateCompleteStringMove(char s1[2], char s2[2], char move[4]) {
	move[0]=s1[0];
	move[1]=s1[1];
	move[2]=s2[0];
	move[3]=s2[1];
	move[4]='\0';
}

bool withinBoard(int xCoordinate, int yCoordinate) {
	if (1 <= xCoordinate && xCoordinate <= 8
	&& 1 <= yCoordinate && yCoordinate <= 8)
		return true;
	return false;
}

void generatePawnMove(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	//mutare pion negru
	if (engine == -1 && xCoordinate != 1) {
		// vedem daca pionul poate merge inainte
		if( (board[i-1][j]==0) && (1<=i-1) && (i-1<=6) && (1<=j) && (j<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// vedem daca pionul poate avansa pe diagonala dreapta
		else if( (board[i-1][j+1]>0) && (1<=i-1) && (i-1<=6) && (1<=(j+1) ) && ( (j+1)<=8) ) {	
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j+1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// diagonala stanga
		else if( (board[i-1][j-1]>0) && (1<=(i-1) ) && ( (i-1)<=6) && (1<=(j-1)) && ((j-1)<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j-1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
	}
	//mutare pion alb
	else if (engine == 1 && xCoordinate != 8) {
		// sus
		if( (board[i+1][j]==0) && (3<=(i+1)) && ((i+1)<=8) && (1<=j) && (j<=8) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// avansez pion alb fata stanga(daca privesti dinspre alb spre negru )
		else if( (board[i+1][j-1]<0) && (3<=(i+1)) && ( (i+1)<=8) && (1<=(j-1)) && ((j-1)<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j-1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		else if( (board[i+1][j+1]<0) && (3<=(i+1)) && ((i+1)<=8) && (1<=(j+1)) && ((j+1)<=8)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j+1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
	}
}

void generatePawnMoveWithEnPassant(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	//mutare pion negru
	if (engine == -1 && xCoordinate != 1) {
		// vedem daca pionul poate merge inainte
		if ( (board[i-1][j]==0) && (1<=i-1) && (i-1<=6) && (1<=j) && (j<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// vedem daca pionul poate avansa pe diagonala dreapta
		else if ( (board[i-1][j+1]>0) && (1<=i-1) && (i-1<=6) && (1<=(j+1) ) && ( (j+1)<=8) ) {	
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j+1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// diagonala stanga
		else if ( (board[i-1][j-1]>0) && (1<=(i-1) ) && ( (i-1)<=6) && (1<=(j-1)) && ((j-1)<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-1, j-1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
	}
	//mutare pion alb
	else if (engine == 1 && xCoordinate != 8) {
		// sus
		if( (board[i+1][j]==0) && (3<=(i+1)) && ((i+1)<=8) && (1<=j) && (j<=8) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		// avansez pion alb fata stanga(daca privesti dinspre alb spre negru )
		else if( (board[i+1][j-1]<0) && (3<=(i+1)) && ( (i+1)<=8) && (1<=(j-1)) && ((j-1)<=8) ) { 
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j-1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
		else if( (board[i+1][j+1]<0) && (3<=(i+1)) && ((i+1)<=8) && (1<=(j+1)) && ((j+1)<=8)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+1, j+1, s2);
			generateCompleteStringMove(s1, s2, move);
		}
	}
}

void generateBishopMove(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	// NU poate sari peste piese
	
	//STANGA Jos [i][j] -> [i-1][j-1]
	if (i-1 >= 1 && i-1 <= 8 && j-1 >= 1 && j-1 <= 8 && (board[i-1][j-1] * engine <= 0) ) {		
		generateHalfStringMove(i, j, s1);
		generateHalfStringMove(i-1, j-1, s2);
		generateCompleteStringMove(s1, s2, move);
	}
	//DREAPTA Jos [i][j] -> [i-1][j+1]
	else if (i-1 >= 1 && i-1 <= 8 && j+1 >= 1 && j+1 <= 8 && ( board[i-1][j+1] * engine <= 0 ) ) {			
		generateHalfStringMove(i, j, s1);
		generateHalfStringMove(i-1, j+1, s2);
		generateCompleteStringMove(s1, s2, move);	
	}
	//STANGA Sus [i][j] -> [i+1][j-1] 
	else if (i+1 >= 1 && i+1 <= 8 && j-1 >= 1 && j-1 <= 8 &&  ( board[i+1][j-1] * engine <= 0 ) ) {	
		generateHalfStringMove(i, j, s1);
		generateHalfStringMove(i+1, j-1, s2);
		generateCompleteStringMove(s1, s2, move);
			
	}
	// DREAPTA  Sus [i][j] -> [i+1][j+1]
	else if (i+1 >= 1 && i+1 <= 8 && j+1 >= 1 && j+1 <= 8 && ( board[i+1][j+1] * engine <= 0 ) ) { 
		generateHalfStringMove(i, j, s1);
		generateHalfStringMove(i+1, j+1, s2);
		generateCompleteStringMove(s1, s2, move);
	}		
}

void generateKnightMove(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	generateHalfStringMove(i, j, s1);
	// sus dreapta: i,j -> i+2, j+1
	if (1 <= i+2 && i+2 <= 8 && 1 <= j+1 && j+1 <= 8 && (board[i+2][j+1] * engine <= 0)) {
		generateHalfStringMove(i+2, j+1, s2);
	}
	// centru dreapta sus: i,j -> i+1, j+2
	else if (1 <= i+1 && i+1 <= 8 && 1 <= j+2 && j+2 <= 8 && (board[i+1][j+2] * engine <= 0)) {
		generateHalfStringMove(i+1, j+2, s2);
	}
	// centru dreapta jos: i,j -> i-1, j+2
	else if (1 <= i-1 && i-1 <= 8 && 1 <= j+2 && j+2 <= 8 && (board[i-1][j+2] * engine <= 0)) {
		generateHalfStringMove(i-1, j+2, s2);
	}
	// jos dreapta: i,j -> i-2, j+1
	else if (1 <= i-2 && i-2 <= 8 && 1 <= j+1 && j+1 <= 8 && (board[i-2][j+1] * engine <= 0 )) {
		generateHalfStringMove(i-2, j+1, s2);
	}
	// jos stanga: i,j -> i-2, j-1
	else if (1 <= i-2 && i-2 <= 8 && 1 <= j-1 && j-1 <= 8 && (board[i-2][j-1] * engine <= 0 )) {
		generateHalfStringMove(i-2, j-1, s2);
	}
	//centru stanga jos: i,j -> i-1, j-2
	else if (1 <= i-1 && i-1 <= 8 && 1 <= j-2 && j-2 <= 8 && (board[i-1][j-2] * engine <= 0 )) {
		generateHalfStringMove(i-1, j-2, s2);
	}
	// centru stanga sus: i,j -> i+1, j-2
	else if (1 <= i+1 && i+1 <= 8 && 1 <= j-2 && j <= 8 && (board[i+1][j-2] * engine <= 0 )) {
		generateHalfStringMove(i+1, j-2, s2);
	}
	// sus stanga: i,j -> i+2, j-1
	else if (1 <= i+2 && i+2 <= 8 && 1 <= j-1 && j-1 <= 8 && (board[i+2][j-1] * engine <= 0 )) {
		generateHalfStringMove(i+2, j-1, s2);
	}

	generateCompleteStringMove(s1, s2, move);
}

void generateRookMove(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	// vom efectua cea mai lunga mutare posibila

	int distance;

	// Sus: i,j -> i+distance, j
	for (distance = 1; distance <= 7; distance++) {
		// mergem in sus pe spatiile libere, modificam constant string-ul mutarii
		if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata coloana a fost libera, ne oprim pe randul de sus
			if (i + distance == 8) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai jos
		// daca piesa aliata este fix deasupra turei, nu este o mutare valida
		else if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] * engine > 0)) {
			if (distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i + distance - 1, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Jos: i,j -> i-distance, j
	for (distance = 1; distance <= 7; distance++) {
		// mergem in sus pe spatiile libere, modificam constant string-ul mutarii
		if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata coloana a fost libera, ne oprim pe randul de jos
			if(i - distance == 1) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai sus
		// daca piesa aliata este fix deasupra turei, nu este o mutare valida
		else if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] * engine > 0)) {
			if (distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i - distance + 1, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Stanga: i,j -> i, j-distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem la stanga pe spatiile libere
		if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			//daca toata linia a fost libera, ne oprim pe coloana din stanga
			if (j - distance == 1) {
				return;
			}
		}
		//daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine < 0) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		//daca intalnim o piesa aliata, ne oprim cu o pozitie mai la dreapta
		//daca piesa este fix la stanga turei, mutarea nu este valida
		else if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance + 1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Dreapta: i,j -> i, j+distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem la stanga pe spatiile libere
		if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			//daca toata linia a fost libera, ne oprim pe coloana din dreapta
			if (j + distance == 8) {
				return;
			}
		}
		//daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine < 0) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		//daca intalnim o piesa aliata, ne oprim cu o pozitie mai la stanga
		//daca piesa este fix la stanga turei, mutarea nu este valida
		else if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance-1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}
}

void generateQueenMove(int engine, int xCoordinate, int yCoordinate, int board[9][9], char move[4]) {
	int i = xCoordinate, j = yCoordinate;
	char s1[2], s2[2];
	strcpy(move, "0000");

	// datorita lui return, se va scrie prima mutare posibila, dupa care functia se opreste
	// vom efectua cea mai lunga mutare posibila
	// copy paste de la tura si nebun
	int distance;

	// Sus: i,j -> i+distance, j
	for (distance = 1; distance <= 7; distance++) {
		// mergem in sus pe spatiile libere, modificam constant string-ul mutarii
		if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata coloana a fost libera, ne oprim pe randul de sus
			if (i + distance == 8) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai jos
		// daca piesa aliata este fix deasupra turei, nu este o mutare valida
		else if (1 <= i+distance && i+distance <= 8 && (board[i+distance][j] * engine > 0)) {
			if (distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i + distance - 1, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Jos: i,j -> i-distance, j
	for (distance = 1; distance <= 7; distance++) {
		// mergem in sus pe spatiile libere, modificam constant string-ul mutarii
		if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata coloana a fost libera, ne oprim pe randul de jos
			if(i - distance == 1) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai sus
		// daca piesa aliata este fix deasupra turei, nu este o mutare valida
		else if (1 <= i-distance && i-distance <= 8 && (board[i-distance][j] * engine > 0)) {
			if (distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i - distance + 1, j, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Stanga: i,j -> i, j-distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem la stanga pe spatiile libere
		if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			//daca toata linia a fost libera, ne oprim pe coloana din stanga
			if (j - distance == 1) {
				return;
			}
		}
		//daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine < 0) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		//daca intalnim o piesa aliata, ne oprim cu o pozitie mai la dreapta
		//daca piesa este fix la stanga turei, mutarea nu este valida
		else if (1 <= j-distance && j-distance <= 8 && (board[i][j-distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j-distance + 1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// Dreapta: i,j -> i, j+distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem la dreapta pe spatiile libere
		if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata linia a fost libera, ne oprim pe coloana din dreapta
			if (j + distance == 8) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine < 0) ) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai la stanga
		// daca piesa este fix la stanga turei, mutarea nu este valida
		else if (1 <= j+distance && j+distance <= 8 && (board[i][j+distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i, j+distance-1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// stanga jos: i,j -> i-distance, j-distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem diagonala stanga jos pe spatiile libere
		// modificam pe parcurs string-ul mutarii
		if (1 <= i-distance && i-distance <= 8
		 && 1 <= j-distance && j-distance <= 8 
		 && (board[i-distance][j-distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata diagonala a fost libera, ne oprim in capatul diagonalei
			// capatul diagonalei se afla la linia 1 SI/SAU coloana 1
			if(i-distance == 1 || j-distance == 1) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i-distance && i-distance <= 8 
		&& 1 <= j-distance && j-distance <= 8 
		&& (board[i-distance][j-distance] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai dreapta-sus
		// daca piesa este fix langa regina, mutarea nu este valida
		else if (1 <= i-distance && i-distance <= 8
		&& 1 <= j-distance && j-distance <= 8
		&& (board[i-distance][j-distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance+1, j-distance+1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// dreapta jos: i,j -> i-distance, j+distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem diagonala stanga jos pe spatiile libere
		// modificam pe parcurs string-ul mutarii
		if (1 <= i-distance && i-distance <= 8
		 && 1 <= j+distance && j+distance <= 8 
		 && (board[i-distance][j+distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata diagonala a fost libera, ne oprim in capatul diagonalei
			// capatul diagonalei se afla la linia 1 SI/SAU coloana 8
			if(i-distance == 1 || j+distance == 8) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i-distance && i-distance <= 8 
		&& 1 <= j+distance && j+distance <= 8 
		&& (board[i-distance][j+distance] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai stanga-sus
		// daca piesa este fix langa regina, mutarea nu este valida
		else if (1 <= i-distance && i-distance <= 8
		&& 1 <= j+distance && j+distance <= 8
		&& (board[i-distance][j+distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i-distance+1, j+distance-1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// stanga sus: i,j -> i+distance, j-distance 
	for (distance = 1; distance <= 7; distance++) {
		// mergem diagonala stanga jos pe spatiile libere
		// modificam pe parcurs string-ul mutarii
		if (1 <= i+distance && i+distance <= 8
		 && 1 <= j-distance && j-distance <= 8 
		 && (board[i+distance][j-distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata diagonala a fost libera, ne oprim in capatul diagonalei
			// capatul diagonalei se afla la linia 8 SI/SAU coloana 1
			if(i+distance == 8 || j-distance == 1) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i+distance && i+distance <= 8 
		&& 1 <= j-distance && j-distance <= 8 
		&& (board[i+distance][j-distance] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j-distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai dreapta-jos
		// daca piesa este fix langa regina, mutarea nu este valida
		else if (1 <= i+distance && i+distance <= 8
		&& 1 <= j-distance && j-distance <= 8
		&& (board[i+distance][j-distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance-1, j-distance+1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}

	// dreapta sus: i,j -> i+distance, j+distance
	for (distance = 1; distance <= 7; distance++) {
		// mergem diagonala stanga jos pe spatiile libere
		// modificam pe parcurs string-ul mutarii
		if (1 <= i+distance && i+distance <= 8
		 && 1 <= j+distance && j+distance <= 8 
		 && (board[i+distance][j+distance] * engine == 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			// daca toata diagonala a fost libera, ne oprim in capatul diagonalei
			// capatul diagonalei se afla la linia 8 SI/SAU coloana 8
			if(i+distance == 8 || j+distance == 8) {
				return;
			}
		}
		// daca intalnim o piesa, o mancam si ne oprim
		else if (1 <= i+distance && i+distance <= 8 
		&& 1 <= j+distance && j+distance <= 8 
		&& (board[i+distance][j+distance] * engine < 0)) {
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance, j+distance, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
		// daca intalnim o piesa aliata, ne oprim cu o pozitie mai stanga-jos
		// daca piesa este fix langa regina, mutarea nu este valida
		else if (1 <= i+distance && i+distance <= 8
		&& 1 <= j+distance && j+distance <= 8
		&& (board[i+distance][j+distance] * engine > 0)) {
			if(distance == 1) {
				break;
			}
			generateHalfStringMove(i, j, s1);
			generateHalfStringMove(i+distance-1, j+distance-1, s2);
			generateCompleteStringMove(s1, s2, move);
			return;
		}
	}	

}

int makeMove(char *move, int board[9][9], vector<int> *history) {
	int i1, j1, i2, j2; // Old and new coordinates of a piece moved by user/engine. 
	initCoordinates(move, &i1, &j1, &i2, &j2);

	// hardcodare retinere miscari tura (ca sa nu mai poata face rocada)
	// trebuie sa diferentiem turele
	// daca am miscat o tura trebuie sa putem face rocada cu cealalta

	// tura alb stanga jos se muta (si cealalta nu)
	int movedRook = 0;
	if (i1 == 1 && j1 == 1) {
		if (find(history->begin(), history->end(), 400) == history->end())
			history->push_back(400);
		movedRook = 1;
	}
	// tura alb dreapta jos
	else if (i1 == 1 && j1 == 8){
		if (find(history->begin(), history->end(), 40) == history->end())
			history->push_back(40);
		movedRook = 1;
	}
	// tura negru dreapta sus
	else if (i1 == 8 && j1 == 8) {
		if (find(history->begin(), history->end(), -40) == history->end())
			history->push_back(-40);
		movedRook = 1;
	}
	// tura negru stanga sus
	else if (i1 == 8 && j1 == 1) {
		if (find(history->begin(), history->end(), -400) == history->end())
			history->push_back(-400);
		movedRook = 1;
	}


	//Update the board.
	board[i2][j2] = board[i1][j1];
	board[i1][j1] = 0;
	g<<"A move has been made: "<<move<<"."<<endl;

	if (movedRook == 1) {
		return 1;
		// skips ordinary move
	}
	
	if (find(history->begin(), history->end(), board[i2][j2]) == history->end())
			history->push_back(board[i2][j2]);

	return 1;
}

void makeDangerZone(int engine, int board[9][9], int danger[9][9]) {
	// piese care dau sah in acelasi fel
	// toate, in afara de pioni
	int i, j;
	int distance;

	// 
	for (i = 8; i >= 1; i--) {
		for (j = 8; j >= 1; j--) {
			// nebun gasit
			if (board[i][j] * engine == 2) {
				// pana unde poate da sah pe diagonala stanga jos
				for (distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i-distance, j-distance)
					&& (board[i-distance][j-distance] == 0)) {
						danger[i-distance][j-distance] = 1;
						// daca toata diagonala a fost libera, ne oprim
						if (i-distance == 1 || j-distance == 1) {
							break;
							// sau un goto dreapta_jos
						}
					}
					// daca intalneste o piesa aliata/inamica pe drum, vom include si pozitia ei si apoi ne oprim
					// asta ajuta la doua cazuri: cand regele alb vrea sa manance piesa noastra sau cand regele alb se afla acolo
					else if (withinBoard(i-distance, j-distance)
					&& (board[i-distance][j-distance] != 0)) {
						danger[i-distance][j-distance] = 1;
						break;
						//sau goto dreapta_jos
					}
				}
				// pana unde poate da sah pe diagonala dreapta jos
				for(distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i-distance,j+distance)
					&& (board[i-distance][j+distance] == 0)) {
						danger[i-distance][j+distance] = 1;
						//daca toata diagonala a fost libera, ne oprim
						if (i-distance == 1 || j+distance == 8) {
							break;
							// sau goto stanga_sus
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i-distance, j+distance)
					&& board[i-distance][j+distance] != 0) {
						danger[i-distance][j+distance] = 1;
						break;
						// sau goto stanga_sus
					}
				}
				// stanga sus
				for (distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i+distance, j-distance) 
					&& board[i+distance][j-distance] == 0) {
						danger[i+distance][j-distance] = 1;
						if (i+distance == 8 || j-distance == 1) {
							break;
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i+distance, j-distance) 
					&& board[i+distance][j-distance] != 0) {
						danger[i+distance][j-distance] = 1;
						break;
					}
				}
				// dreapta sus
				for(distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i+distance, j+distance) 
					&& board[i+distance][j+distance] == 0) {
						danger[i+distance][j+distance] = 1;
						if (i+distance == 8 || j+distance == 8) {
							break;
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i+distance, j+distance) 
					&& board[i+distance][j+distance] != 0) {
						danger[i+distance][j+distance] = 1;
						break;
					}
				}
			}
			// tura
			else if (board[i][j] * engine == 4) {
				// sus: i,j -> i+distance, j
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i+distance, j) 
					&& board[i+distance][j] == 0) {
						danger[i+distance][j] = 1;
						if(i+distance == 8) {
							break;
						}
					}
					// piesa aliata/inamica
					else if (withinBoard(i+distance, j)
					&& board[i+distance][j] != 0) {
						danger[i+distance][j] = 1;
						break;
					} 
				}
				// jos
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if(withinBoard(i-distance, j)
					&& board[i-distance][j] == 0) {
						danger[i-distance][j] = 1;
						if(i-distance == 1) {
							break;
						}
					}
					// piesa aliata/inamica
					else if (withinBoard(i-distance, j)
					&& board[i-distance][j] != 0) {
						danger[i-distance][j] = 1;
						break;
					}
				}
				// stanga
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i, j-distance)
					&& board[i][j-distance] == 0) {
						danger[i][j-distance] = 0;
						if (i-distance == 1) {
							break;
						}
					}
					// piesa aliata/inamica
					if (withinBoard(i, j-distance)
					&& board[i][j-distance] != 0) {
						danger[i][j-distance] = 1;
						break;
					}
				}
				// dreapta
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i, j+distance)
					&& board[i][j+distance] == 0) {
						danger[i][j+distance] = 1;
						if (j+distance == 8) {
							break;
						}
					}
				}
			}
			// regina
			// copy paste de la nebun + tura
			else if (board[i][j] * engine == 5) {
				// pana unde poate da sah pe diagonala stanga jos
				for (distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i-distance, j-distance)
					&& (board[i-distance][j-distance] == 0)) {
						danger[i-distance][j-distance] = 1;
						// daca toata diagonala a fost libera, ne oprim
						if (i-distance == 1 || j-distance == 1) {
							break;
							// sau un goto dreapta_jos
						}
					}
					// daca intalneste o piesa aliata/inamica pe drum, vom include si pozitia ei si apoi ne oprim
					// asta ajuta la doua cazuri: cand regele alb vrea sa manance piesa noastra sau cand regele alb se afla acolo
					else if (withinBoard(i-distance, j-distance)
					&& (board[i-distance][j-distance] != 0)) {
						danger[i-distance][j-distance] = 1;
						break;
						//sau goto dreapta_jos
					}
				}
				// pana unde poate da sah pe diagonala dreapta jos
				for(distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i-distance,j+distance)
					&& (board[i-distance][j+distance] == 0)) {
						danger[i-distance][j+distance] = 1;
						//daca toata diagonala a fost libera, ne oprim
						if (i-distance == 1 || j+distance == 8) {
							break;
							// sau goto stanga_sus
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i-distance, j+distance)
					&& board[i-distance][j+distance] != 0) {
						danger[i-distance][j+distance] = 1;
						break;
						// sau goto stanga_sus
					}
				}
				// stanga sus
				for (distance = 1; distance <= 7; distance++) {
					//spatiu gol
					if (withinBoard(i+distance, j-distance) 
					&& board[i+distance][j-distance] == 0) {
						danger[i+distance][j-distance] = 1;
						if (i+distance == 8 || j-distance == 1) {
							break;
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i+distance, j-distance) 
					&& board[i+distance][j-distance] != 0) {
						danger[i+distance][j-distance] = 1;
						break;
					}
				}
				// dreapta sus
				for(distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i+distance, j+distance) 
					&& board[i+distance][j+distance] == 0) {
						danger[i+distance][j+distance] = 1;
						if (i+distance == 8 || j+distance == 8) {
							break;
						}
					}
					// piesa inamica/aliata
					else if (withinBoard(i+distance, j+distance) 
					&& board[i+distance][j+distance] != 0) {
						danger[i+distance][j+distance] = 1;
						break;
					}
				}
				// sus: i,j -> i+distance, j
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i+distance, j) 
					&& board[i+distance][j] == 0) {
						danger[i+distance][j] = 1;
						if(i+distance == 8) {
							break;
						}
					}
					// piesa aliata/inamica
					else if (withinBoard(i+distance, j)
					&& board[i+distance][j] != 0) {
						danger[i+distance][j] = 1;
						break;
					} 
				}
				// jos
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if(withinBoard(i-distance, j)
					&& board[i-distance][j] == 0) {
						danger[i-distance][j] = 1;
						if(i-distance == 1) {
							break;
						}
					}
					// piesa aliata/inamica
					else if (withinBoard(i-distance, j)
					&& board[i-distance][j] != 0) {
						danger[i-distance][j] = 1;
						break;
					}
				}
				// stanga
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i, j-distance)
					&& board[i][j-distance] == 0) {
						danger[i][j-distance] = 0;
						if (i-distance == 1) {
							break;
						}
					}
					// piesa aliata/inamica
					if (withinBoard(i, j-distance)
					&& board[i][j-distance] != 0) {
						danger[i][j-distance] = 1;
						break;
					}
				}
				// dreapta
				for (distance = 1; distance <= 7; distance++) {
					// spatiu gol
					if (withinBoard(i, j+distance)
					&& board[i][j+distance] == 0) {
						danger[i][j+distance] = 1;
						if (j+distance == 8) {
							break;
						}
					}
				}
			}
			// cal
			else if (board[i][j] * engine == 3) {
				//sus dreapta: i,j -> i+2, j+1
				if (withinBoard(i+2, j+1))
					danger[i+2][j+1] = 1;
				// centru dreapta sus: i,j -> i+1, j+2
				if (withinBoard(i+1, j+2))
					danger[i+1][j+2] = 1;
				// centru dreapta jos: i,j -> i-1, j+2
				if (withinBoard(i-1, j+2))
					danger[i-1][j+2] = 1;
				// jos dreapta: i,j -> i-2, j+1
				if (withinBoard(i-2, j+1))
					danger[i-2][j+1] = 1;
				// jos stanga: i,j -> i-2, j-1
				if (withinBoard(i-2, j-1))
					danger[i-1][j-1] = 1;
				//centru stanga jos: i,j -> i-1, j-2
				if (withinBoard(i-1, j-2))
					danger[i-1][j-2] = 1;
				// centru stanga sus: i,j -> i+1, j-2
				if (withinBoard(i+1, j-2))
					danger[i+1][j-2] = 1;
				// sus stanga: i,j -> i+2, j-1
				if (withinBoard(i+2, j-1))
					danger[i+2][j-1] = 1;
			}
			// rege (cei doi regi nu se pot apropia unul de altul)
			else if ( board[i][j] *engine == 6) {
				// sus
				if (withinBoard(i+1, j))
					danger[i+1][j] = 1;
				// dreapta sus
				if (withinBoard(i+1, j+1))
					danger[i+1][j+1] = 1;
				// dreapta
				if (withinBoard(i, j+1))
					danger[i][j+1] = 1;
				// dreapta jos
				if (withinBoard(i-1, j+1))
					danger[i-1][j+1] = 1;
				//jos
				if (withinBoard(i-1, j))
					danger[i-1][j] = 1;
				// stanga jos
				if (withinBoard(i-1,j-1))
					danger[i-1][j-1] = 1;
				// stanga
				if (withinBoard(i,j-1))
					danger[i][j-1] = 1;
				// stanga sus
				if (withinBoard(i+1, j-1))
					danger[i+1][j-1] = 1;
			}		
		}
	}
}

void makeDangerZoneForWhiteKing(int board[9][9], int whiteDanger[9][9]) {
	int i, j;
	int distance;

	// se reseteaza matricea la 0
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
			whiteDanger[i][j] = 0;

	// pentru fiecare piesa neagra, vom marca zona ei de atac cu 1
	for (i = 8; i >= 1; i--) {
		for (j = 8; j >= 1; j--) {
			// pion negru gasit
			if (board[i][j] == -1) {
				// vedem daca poate da sah pe diagonala dreapta (daca nu iese din matrice)
				if (1 <= i-1 && j+1 <= 8) {
					whiteDanger[i-1][j+1] = 1;
				}
				//vedem daca poate da sah pe diagonala stanga (daca nu iese din matrice)
				if (1 <= i-1 && 1 <= j-1) {
					whiteDanger[i-1][j-1] = 1;
				}
			}
		}
	}

	// restul pieselor se comporta la fel, vom folosi functia si pt negru
	makeDangerZone(-1, board, whiteDanger);
}

void makeDangerZoneForBlackKing(int board[9][9], int blackDanger[9][9]) {
	int i, j;

	// se reseteaza matricea la 0
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
			blackDanger[i][j] = 0;

	// difera de makeDangerZoneforWhiteKing doar prin sensul de atac al pionilor,
	// restul pieselor se comporta identic

	//pentru fiecare pion, se va marca zona lui de atac
	for (i = 1; i >= 1; i--) {
		for (j = 8; j >= 1; j--) {
			// pion alb gasit
			if (board[i][j] == 1) {
				// vedem daca poate da sah pe diagonala dreapta
				if (i+1 <= 8 && j+1 >= 8) {
					blackDanger[i+1][j+1] = 1;
				}
				// vedem daca poate da sah pe diagonala stanga
				if (i+1 <= 8 && 1 <= j-1) {
					blackDanger[i+1][j-1] = 1;
				}
			}
		}
	}

	makeDangerZone(1, board, blackDanger);
}

int doSmallRocada (int engineColor, int board[9][9], vector<int> *history, 
	int whiteDanger[9][9], int blackDanger[9][9]) {
	if (engineColor == -1 && board[8][8] == -4 && board[8][5] == -6) {
		//verifica daca intre tura din stanga si rege nu se afla nicio piesa
		if (board[8][6] == 0 && board[8][7] == 0) {
			// TO DO: REGELE NU SE AFLA IN SAH
			if (blackDanger[8][5] == 0) {
				g << "nu se afla in sah"<<endl;
				// POZITIILE DINTRE TURA SI REGE NU SUNT CONTROLATE DE ALTE PIESE ADVERSE
				if (blackDanger[8][6] == 0 && blackDanger[8][7] == 0) {
					g << "nu exista sah intermediar"<< endl;
					// REGELE NU A FOST MUTAT NICIODATA PANA ACUM
					// si nici tura
					if ((find(history->begin(), history->end(), -6) == history->end())
					&& (find(history->begin(), history->end(), -40) == history->end())) {

						char move[5] = "h8f8";
						makeMove(move, board, history);

						strcpy(move, "e8g8");
						makeMove(move, board, history);

						cout << "move " << move << endl;
						g << "move " << move << endl;
						return 1;
					}
				}
			}
		}		
	}

	else if (engineColor == 1 && board[1][8] == 4 && board[1][5] == 6) {
		if (board[1][6] == 0 && board[1][7] == 0) {
			if (whiteDanger[1][5] == 0) {
				if (whiteDanger[1][6] == 0 && whiteDanger[1][7] == 0) {
					if (find(history->begin(), history->end(), 6) == history->end()
					&& (find(history->begin(), history->end(), 40) == history->end())) {
						char move[5] = "h1f1";
						makeMove(move, board, history);

						strcpy(move, "e1g1");
						makeMove(move, board, history);

						cout << "move " << move << endl;
						g << "move " << move << endl;
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int doBigRocada (int engineColor, int board[9][9], vector<int> *history, 
	int whiteDanger[9][9], int blackDanger[9][9]) {
	if (engineColor == -1 && board[8][1] == -4 && board[8][5] == -6) {
		g << "pozitii ok pt rocada"<<endl;
		g << "tura engine "<< engineColor<<" "<<board[8][1];
		//verifica daca intre tura din stanga si rege nu se afla nicio piesa
		if (board[8][2] == 0 && board[8][3] == 0 && board[8][4] == 0) {
			g << "spatii libere intre tura si rege"<<endl;
			// TO DO: REGELE NU SE AFLA IN SAH
			if (blackDanger[8][5] == 0) {
				g << "rege nu se afla in sah"<<endl;
				// POZITIILE DINTRE TURA SI REGE NU SUNT CONTROLATE DE ALTE PIESE ADVERSE
				if (blackDanger[8][4] == 0 && blackDanger[8][3] == 0 && blackDanger[8][2] == 0) {
					g<< "nu e sah intermediar"<<endl;
					// REGELE NU A FOST MUTAT NICIODATA PANA ACUM
					if ((find(history->begin(), history->end(), -6) == history->end())
					&& (find(history->begin(), history->end(), -400) == history->end())) {

						g << "regele n a fost mutat pana acum"<<endl;
						char move[5] = "a8d8";
						makeMove(move, board, history);

						strcpy(move, "e8c8");
						makeMove(move, board, history);
						
						cout << "move " << move << endl;
						g << "move " << move << endl;
						return 1;
					}
				}
			}
		}		
	}

	else if (engineColor == 1 && board[1][1] == 4 && board[1][5] == 6) {
		if (board[1][2] == 0 && board[1][3] == 0 && board[1][4] == 0) {
			if (whiteDanger[1][5] == 0) {
				if (whiteDanger[1][4] == 0 && whiteDanger[1][3] == 0 && whiteDanger[1][2] == 0) {
					if ((find(history->begin(), history->end(), 6) == history->end())
					&& (find(history->begin(), history->end(), 400) == history->end())) {


						char move[5] = "a1d1";
						makeMove(move, board, history);

						strcpy(move, "e1c1");
						makeMove(move, board, history);

						cout << "move " << move << endl;
						g << "move " << move << endl;
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int makeEngineMove(int engineColor, int board[9][9], int whiteDanger[9][9], 
	int blackDanger[9][9], vector<int> *history, char *last_move, int *nrPromotie) {
	
	char move[4];
	// Cauta pe tabla o piesa care poate fi mutata, salveaza-i coordonatele
	// si genereaza mutarea cu generatePawnMove(coordonatele gasite) ;
	int found = 0;
	int xCoordinate, yCoordinate;
	
	// pentru en passant
	int i1, j1, i2, j2;
	int x=-10, y=-10;
	char s1[2], s2[2];
	initCoordinates(last_move, &i1, &j1, &i2, &j2);
	// for
	// 	for
	// 	if rege si rege primeste sah
	// 		muta rege sau mananca piesa sau blocheaza sah
	// 		- muta rege : make king move (daca poate)
	// 		- mananca piesa: chiar daca o mananca tot trebuie sa nu primeasca sah
	// 		- blocheaza sah: tot trebuie sa nu primeasca sah din alte parti

	if (doBigRocada(engineColor, board, history, whiteDanger, blackDanger) == 1 || doSmallRocada(engineColor, board, history, whiteDanger, blackDanger) == 1) {
		g << "a facut rocada"<<endl;
		return 1;
	}
	else g << "n a facut rocada" << endl;

	// verificam daca putem face en passant
	if(  ( (i1-i2==2) || (i2-i1==2 )) && (board[i2][j2]*engineColor == -1) )		// last move s a mutat pion inamic 2 patratele
	{	
		if(board[i2][j2-1]== engineColor )	// pion inamic, pe aceeasi linie cu pionul care a sarit 2 patratele, in dreapta
		{	
			x=i2;
			y=j2-1;
		}
		else if(board[i2][j2+1]== engineColor )	// pion inamic, pe aceeasi linie cu pionul care a sarit 2 patratele, in stanga acestuia
		{
			x=i2;
			y=j2+1;
		}
		if( (x==-10) && (y==-10) ) // nu se poate face en passat ul deoarece nu exista niciun pion inamic vecin cu pionul care a sarit 2
			;
		else	// botul poate executa en passat cu pionul de pe coord (x,y)
		{
			
			if(engineColor == 1 )
			{
			generateHalfStringMove( x, y, s1  );
			generateHalfStringMove( x+1, j2, s2);
			generateCompleteStringMove(s1, s2 , move);
			}
			
			else if(engineColor == -1)
			{
			generateHalfStringMove( x, y, s1  );
			generateHalfStringMove( x-1, j2, s2);
			generateCompleteStringMove(s1, s2 , move);
			}
		board[i2][j2]=0;	// mananci pionul inamic la en passat
		cout<<"move "<<move<<endl;
		g<<"move "<<move<<endl;
		makeMove(move, board, history);
		
			return 1;
		}
		
	}



	// restul pieselor
	for (xCoordinate = 8; xCoordinate >= 1 && found == 0; xCoordinate--) {
		for (yCoordinate = 8; yCoordinate >=1 && found == 0; yCoordinate--) {
			// pion gasit
			if (board[xCoordinate][yCoordinate] == 1*engineColor) { 
				generatePawnMove(engineColor, xCoordinate, yCoordinate, board, move);
				if (strcmp(move, "0000"))
					found = 1;
			}
			// nebun gasit
			
			else if (board[xCoordinate][yCoordinate] == 2*engineColor) {
				generateBishopMove(engineColor, xCoordinate, yCoordinate, board, move);
				if (strcmp(move, "0000"))
					found = 1;
			}
			// cal gasit
			else if (board[xCoordinate][yCoordinate] == 3*engineColor) {
				generateKnightMove(engineColor, xCoordinate, yCoordinate, board, move);
				if(strcmp(move, "0000"))
					found = 1;
			}
			//tura
			else if (board[xCoordinate][yCoordinate] == 4*engineColor) {
				generateRookMove(engineColor, xCoordinate, yCoordinate, board, move);
				if(strcmp(move, "0000"))
					found = 1;
			}
			//regina
			else if (board[xCoordinate][yCoordinate] == 5*engineColor) {
				generateQueenMove(engineColor, xCoordinate, yCoordinate, board, move);
				if(strcmp(move, "0000"))
					found = 1;
			}
		}

	}

	// Daca nu mai exista nicio mutare posibila, resign
	
	if (found == 0) {
		cout<<"resign"<<endl;
		g<<"resign: no move available found"<<endl;
		return 0;
	} 
	else 
	{
		
		int x1,x2,y1,y2;
		initCoordinates(move, &x1, &y1, &x2, &y2 );
		int promotiePion=0;
		char tipPromotie; 
		if(board[x1][y1]==1 && x2==8 )	//pion alb care trebuie promovat
		{
			promotiePion=1;

		}	
		else 
			if(board[x1][y1]==-1 && x2==1 ) 		// pion negru care trb promov	
			{
				promotiePion=1;
			}
		
		if(promotiePion==1)
		{
			
			tipPromotie=PromNrToChar(*nrPromotie);
			cout<<"move "<<move<<tipPromotie<<endl;
			board[x1][y1]=0;
			board[x2][y2]=engineColor*PromCharToNr(tipPromotie);
			g<<"move "<<move<<tipPromotie<<endl;

			/* history */
			(*nrPromotie)++;
		}

		else	/* Pion nepromovat */	
		{
		cout<<"move "<<move<<endl;
		g<<"move "<<move<<endl;
		makeMove(move, board, history);
		}
	}
	return 1;
}


int main() {
	signal (SIGINT, SIG_IGN);

	vector<int> history;

	int board[9][9] = {{0}};
	// where white and black kings get check
	int whiteDanger[9][9] = {{0}};
	int blackDanger[9][9] = {{0}};
	char command[20];
	char last_move[20];
	
	makeDangerZoneForWhiteKing(board, whiteDanger);
	makeDangerZoneForBlackKing(board, blackDanger);

	int nrPromotie=0;


	//Game settings:
	// 0 -> white ; 1 -> black
	int engineColor = -1; //Engine plays with black by default.
	int forceMode = 0;   //Force mode is disabled by default.
	int turn = 1;        //White moves first.

	while (1) {
		cin>>command; //take instruction from xboard's stdout
		f<<command<<endl; //put command in "xboardtoeng.txt" - debbuging file

		if (!strcmp(command, "new")) {
			//Set new game.
			initNewGame(board, &turn, &forceMode, &engineColor, &history); 
		}

		if (!strcmp(command, "force")) {
			forceMode = 1;
			//  When in force mode, engine expects to receive moves from xboard,
			//  and just updates its board's representation, without making other
			//  moves by "itself".
		}

		if (!strcmp(command, "go")) {
			// Disables force mode
			forceMode = 0;
		}

		if (!strcmp(command, "quit")) {
			// Leave the game
			break;
		}

		if (!strcmp(command, "black")) {
			// Set engine to play with black 
			engineColor = -1;
			turn = -1;
		}

		if (!strcmp(command, "white")) {
			// Set engine to play with white
			engineColor = 1;
			turn = 1;
		}


		// MOVES

		// User made a move, xboard sent a move format string to stdout,
		// and the engine needs to interpretate it 
		// and update its intern board representation.
		if(userMoves(command)) {
			strcpy(last_move, command);
			makeMove(command, board, &history);
			makeDangerZoneForWhiteKing(board, whiteDanger);
			makeDangerZoneForBlackKing(board, blackDanger);

			turn *= -1;   // Update turn.
			g<<"User moved.It's engine's turn! "<<turn<<endl;
			for(int i = 0; i < (int)history.size(); i++) {
				g << history[i] << ' ';
			}
			g << endl;
		}

		// Engine moves
		if (forceMode == 0 && engineColor == turn) {
			makeEngineMove(engineColor, board, whiteDanger, blackDanger, &history, last_move, &nrPromotie);	
			makeDangerZoneForWhiteKing(board, whiteDanger);
			makeDangerZoneForBlackKing(board, blackDanger);		
			turn *= -1;
			g<<"Engine moved.It's user's turn! "<<turn<<endl;
			for(int i = 0; i < (int)history.size(); i++) {
				g << history[i] << ' ';
			}
			g << endl;			
		}
	}


	f.close();
	g.close();

	return 0;
}