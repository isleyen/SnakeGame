#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;

// Geniþlik ve Yükseklik arayüzümüz için 
const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  // Yýlanýn Kuyruk Koordinatlarýdýr. 
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {

	gameOver = false;
	dir = STOP;     // karakter baslangicta hareketsizdir.
	x = width / 2;    // x ve y nin yükseklik ve genisligin yarýsýna ayarlamak demek
	y = height / 2;       // Karakterimizin tam ortadan baslayacagi anlamýna gelmektedir

	fruitX = rand() % width;   // rand rastgele bir sayý üretir ve onun modunu aldýgýmýz zaman
	fruitY = rand() % height;   // ekranýn içinde rastgele bir yerde meyvenin baþlamasýný saglar.
	                         

	score = 0; // score da en baþta sýfýr olarak baþlatýlýr

}
// Bu fonksiyon içerisinde oyunumuzun temel ekranýný yapacaðýz yani çerçevemizi.
void Draw() {

	system("cls"); // Bu komutumuz ekraný temizler, her oyun baþlamadan önce ekran temizlenir.
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#"; // Dýþ kýsmý yani çerçeveyi temsil ederken
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
					cout << " "; // içerideki boþluklarý temsil ediyor
			}


			if (j == width - 1) 
				cout << "#";
		}
		cout << endl; ; // endl yapmamýzýn amacý ise her döngü sonunda alt satýra geçmemizdir ve bu þekilde çerçeve oluþacaktýr.

	}


	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}
// bu fonksiyonumuzda da tuþlarý yön için atama yaptýk.
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

void Logic() { // Oluþturduðumuz girdilerin mantýðýný burada oluþturacaðýz yani nasýl hareket edeceðini vs daha detaylý kodlayacaðýz.
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
	if (x > width || x <0 || y > height || y < 0) //sýnýrlarý aþarsa gameOver.
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y) // bu kod parçasýnda yýlanýn kuyruðu herhangi bir yere çarparsa oyun sona erer.
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