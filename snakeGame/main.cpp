#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;

// Geni�lik ve Y�kseklik aray�z�m�z i�in 
const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  // Y�lan�n Kuyruk Koordinatlar�d�r. 
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {

	gameOver = false;
	dir = STOP;     // karakter baslangicta hareketsizdir.
	x = width / 2;    // x ve y nin y�kseklik ve genisligin yar�s�na ayarlamak demek
	y = height / 2;       // Karakterimizin tam ortadan baslayacagi anlam�na gelmektedir

	fruitX = rand() % width;   // rand rastgele bir say� �retir ve onun modunu ald�g�m�z zaman
	fruitY = rand() % height;   // ekran�n i�inde rastgele bir yerde meyvenin ba�lamas�n� saglar.
	                         

	score = 0; // score da en ba�ta s�f�r olarak ba�lat�l�r

}
// Bu fonksiyon i�erisinde oyunumuzun temel ekran�n� yapaca��z yani �er�evemizi.
void Draw() {

	system("cls"); // Bu komutumuz ekran� temizler, her oyun ba�lamadan �nce ekran temizlenir.
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#"; // D�� k�sm� yani �er�eveyi temsil ederken
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "X";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " "; // i�erideki bo�luklar� temsil ediyor
			}


			if (j == width - 1) 
				cout << "#";
		}
		cout << endl; ; // endl yapmam�z�n amac� ise her d�ng� sonunda alt sat�ra ge�memizdir ve bu �ekilde �er�eve olu�acakt�r.

	}


	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}
// bu fonksiyonumuzda da tu�lar� y�n i�in atama yapt�k.
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic() { // Olu�turdu�umuz girdilerin mant���n� burada olu�turaca��z yani nas�l hareket edece�ini vs daha detayl� kodlayaca��z.
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {

		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x <0 || y > height || y < 0) //s�n�rlar� a�arsa gameOver.
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y) // bu kod par�as�nda y�lan�n kuyru�u herhangi bir yere �arparsa oyun sona erer.
			gameOver = true;


	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10);
	}

	return 0;
}