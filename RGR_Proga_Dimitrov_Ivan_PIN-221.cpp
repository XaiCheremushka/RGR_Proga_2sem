#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <locale.h>

using namespace std;

#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
#define KPG 17 // предельная точка глобальная
#define CENTREX 476 // Координаты центра консоли
#define СENTREY 238 


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Текстовый курсор в точку x,y
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

// Видимость курсора
void ConsoleCursorVisible()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void setcur(int x, int y)//установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

double proverkaFunc(double y, double x) {
	if (y <= 10.0 && y >= -10.0) {
		return y;
	}
	else {
		
		return 404.0;
	}
}





//Анимация меню
void menuAnim(string Menu[7]) {
	setlocale(0, "RUS");

	
	int kPoz = KPG; // предельная точка
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	
	//for (int i = size(Menu) - 1; i >= 0; i--) {
	for (int i = 6; i >= 0; i--) {
		for (int j = 0; j <= kPoz; j++) {
			Sleep(10);
			ConsoleCursorVisible();
			GoToXY(45, j-1);
			cout << "                                  " << endl;
			GoToXY(45, j);
			cout << Menu[i] << endl;
			if (kPoz < KPG) 
				for (int l = KPG; l >= kPoz+1; l--) {
					GoToXY(45, l);
					//cout << Menu[size(Menu)-(KPG-l)-1] << endl;
					cout << Menu[7-(KPG-l)-1] << endl;
				}
		}
		kPoz--;
	}

}

// Анимация
void animation() {
	// Координаты для первой части анимации
	int coordsX[] = {1, 960, 1, 960};
	int coordsY[] = { 1, 1, 476, 476 };
	
	

	system("cls");
	HDC screen = GetDC(GetConsoleWindow());
	HPEN arevWhite = CreatePen(PS_SOLID, 6, RGB(255, 255, 255));
	HPEN arevBlack = CreatePen(PS_SOLID, 6, RGB(12, 12, 12));
	HPEN point = CreatePen(PS_SOLID, 25, RGB(255, 255, 255));
	HPEN arevCircle = CreatePen(PS_SOLID, 11, RGB(255, 255, 255));

	// Первая часть
	int i = 1;
	while ((coordsX[0] == coordsX[1] == coordsX[2] == coordsX[3] <= CENTREX) && (coordsY[0] == coordsY[1] == coordsY[2] == coordsY[3] <= СENTREY))
	{
		SelectObject(screen, arevWhite); //Рисуем отрезки до центра
		MoveToEx(screen, coordsX[0], coordsY[0], NULL);
		coordsX[0] += 4; coordsY[0] += 2;
		LineTo(screen, coordsX[0], coordsY[0]);

		MoveToEx(screen, coordsX[1], coordsY[1], NULL);
		coordsX[1] -= 4; coordsY[1] += 2;
		LineTo(screen, coordsX[1], coordsY[1]);

		MoveToEx(screen, coordsX[2], coordsY[2], NULL);
		coordsX[2] += 4; coordsY[2] -= 2;
		LineTo(screen, coordsX[2], coordsY[2]);

		MoveToEx(screen, coordsX[3], coordsY[3], NULL);
		coordsX[3] -= 4; coordsY[3] -= 2;
		LineTo(screen, coordsX[3], coordsY[3]);
		if (i % 2 == 0) {
			SelectObject(screen, arevBlack); //Удаляем отрезки, чтобы анимация была плавной и не было линий на экране
			MoveToEx(screen, coordsX[0], coordsY[0], NULL);
			//x1 += 2; y1 += 2;
			LineTo(screen, coordsX[0] - 4*2, coordsY[0] - 2*2);

			MoveToEx(screen, coordsX[1], coordsY[1], NULL);
			//x2 -= 2; y2 += 2;
			LineTo(screen, coordsX[1] + 4*2, coordsY[1] - 2*2);

			MoveToEx(screen, coordsX[2], coordsY[2], NULL);
			//x3 += 2; y3 -= 2;
			LineTo(screen, coordsX[2] - 4*2, coordsY[2] + 2*2);

			MoveToEx(screen, coordsX[3], coordsY[3], NULL);
			//x4 -= 2; y4 -= 2;
			LineTo(screen, coordsX[3] + 4*2, coordsY[3] + 2*2);
		}
		i++;
		if (i % 10 == 0)
			Sleep(22);
	}
	// Точка по центру консоли
	SelectObject(screen, point); 
	MoveToEx(screen, CENTREX + 2, СENTREY, NULL);
	LineTo(screen, CENTREX + 2, СENTREY);
	
	// Вторая часть
	//int x = CENTREX; int R = CENTREX + 27; int y = sqrt(pow(R, 2) - pow(x, 2));
	SelectObject(screen, arevWhite);
	


	//variant 2
	i = 1;
	for (double x = 0.1; x < 10.0; x += 0.1) {

		double y0[] = { (sqrt(20 * x)), (sqrt(2.5 * x)), (-0.4 * (pow(sqrt(x), 4))), (-0.05 * (pow(sqrt(x), 4))), (-(sqrt(20 * x))), (-(sqrt(2.5 * x))), (0.05 * (pow(sqrt(x), 4))), (0.4 * (pow(sqrt(x), 4))) };
		double y1[] = { (sqrt(20 * (x + 0.1))), (sqrt(2.5 * (x + 0.1))), (-0.4 * (pow(sqrt((x + 0.1)), 4))), (-0.05 * (pow(sqrt((x + 0.1)), 4))), (-(sqrt(20 * (x + 0.1)))), (-(sqrt(2.5 * (x + 0.1)))), (0.05 * (pow(sqrt(x + 0.1), 4))), (0.4 * (pow(sqrt(x + 0.1), 4)))};

		for (int l = 0; l < 8; l++) {
			if (l < 4 && proverkaFunc(y1[l], x) != 404.0) {
				MoveToEx(screen, x * 10 + CENTREX, -10 * y0[l] + СENTREY, NULL);
				LineTo(screen, (x + 0.1) * 10 + CENTREX, -10 * y1[l] + СENTREY);
			}
			else if (l < 8 && proverkaFunc(y1[l], x) != 404.0) {
				MoveToEx(screen, -x * 10 + CENTREX, -10 * y0[l] + СENTREY, NULL);
				LineTo(screen, -(x + 0.1) * 10 + CENTREX, -10 * y1[l] + СENTREY);
			}
		}

		if (i % 6 == 0)
			Sleep(15);

		i++;
	}


	// Третья часть
	//double y = sqrt(25.00 - (x * x));

	SelectObject(screen, arevCircle);
	i = 1;
	double x1 = 0.2;
	double x2 = 0.04;
	double x3 = 0.04;
	
	for (double x = 0.1; x < 5.0; x += 0.1) {
		//7-8
		MoveToEx(screen, (x - 10.0) * 10 + CENTREX, -10 * sqrt(121.00 - ((x - 10.0) * (x - 10.0))) + СENTREY, NULL);
		LineTo(screen, ((x - 10.0) + 0.1) * 10 + CENTREX, -10 * sqrt(121.00 - (((x - 10.0) + 0.1) * ((x - 10.0) + 0.1))) + СENTREY);
		//8-1
		MoveToEx(screen, (x1 - 5.0) * 10 + CENTREX, -10 * sqrt(121.00 - ((x1 - 5.0) * (x1 - 5.0))) + СENTREY, NULL);
		LineTo(screen, ((x1 - 5.0) + 0.2) * 10 + CENTREX, -10 * sqrt(121.00 - (((x1 - 5.0) + 0.2) * ((x1 - 5.0) + 0.2))) + СENTREY);
		//1-2
		MoveToEx(screen, (x + 5.0) * 10 + CENTREX, -10 * sqrt(121.00 - ((x + 5.0) * (x + 5.0))) + СENTREY, NULL);
		LineTo(screen, ((x + 5.0) + 0.1) * 10 + CENTREX, -10 * sqrt(121.00 - (((x + 5.0) + 0.1) * ((x + 5.0) + 0.1))) + СENTREY);
		//2-4 and 6-7
		if (i < 25) {
			MoveToEx(screen, (x2 + 10.0) * 10 + CENTREX, -10 * sqrt(121.00 - ((x2 + 10.0) * (x2 + 10.0))) + СENTREY, NULL); //2-2.4
			LineTo(screen, ((x2 + 10.0) + 0.04) * 10 + CENTREX, -10 * sqrt(121.00 - (((x2 + 10.0) + 0.04) * ((x2 + 10.0) + 0.04))) + СENTREY);

			MoveToEx(screen, (-10.0 - x2) * 10 + CENTREX, -10 * -sqrt(121.00 - ((-10.0 - x2) * (-10.0 - x2))) + СENTREY, NULL); //6-6.7
			LineTo(screen, ((-10.0 - x2) - 0.04) * 10 + CENTREX, -10 * -sqrt(121.00 - (((-10.0 - x2) - 0.04) * ((-10.0 - x2) - 0.04))) + СENTREY);
			x2 += 0.04;
		}
		else  {
			MoveToEx(screen, (11.0 - x3) * 10 + CENTREX, -10 * -sqrt(121.00 - ((11.0 - x3) * (11.0 - x3))) + СENTREY, NULL); //2.4-4
			LineTo(screen, ((11.0 - x3) - 0.04) * 10 + CENTREX, -10 * -sqrt(121.00 - (((11.0 - x3) - 0.04) * ((11.0 - x3) - 0.04))) + СENTREY);

			MoveToEx(screen, (-11.0 + x3) * 10 + CENTREX, -10 * sqrt(121.00 - ((-11.0 + x3) * (-11.0 + x3))) + СENTREY, NULL); //6.7-7
			LineTo(screen, ((-11.0 + x3) + 0.04) * 10 + CENTREX, -10 * sqrt(121.00 - (((-11.0 + x3) + 0.04) * ((-11.0 + x3) + 0.04))) + СENTREY);
			x3 += 0.04;
		}
		//4-3
		MoveToEx(screen, (10.0 - x) * 10 + CENTREX, -10 * -sqrt(121.00 - ((10.0 - x) * (10.0 - x))) + СENTREY, NULL);
		LineTo(screen, ((10.0 - x) - 0.1) * 10 + CENTREX, -10 * -sqrt(121.00 - (((10.0 - x) - 0.1) * ((10.0 - x) - 0.1))) + СENTREY);
		//3-5
		MoveToEx(screen, (5.0 - x1) * 10 + CENTREX, -10 * -sqrt(121.00 - ((5.0 - x1) * (5.0 - x1))) + СENTREY, NULL);
		LineTo(screen, ((5.0 - x1) - 0.2) * 10 + CENTREX, -10 * -sqrt(121.00 - (((5.0 - x1) - 0.2) * ((5.0 - x1) - 0.2))) + СENTREY);
		//5-6
		MoveToEx(screen, (-5.0 - x) * 10 + CENTREX, -10 * -sqrt(121.00 - ((-5.0 - x) * (-5.0 - x))) + СENTREY, NULL);
		LineTo(screen, ((-5.0 - x) - 0.1) * 10 + CENTREX, -10 * -sqrt(121.00 - (((-5.0 - x) - 0.1) * ((-5.0 - x) - 0.1))) + СENTREY);
		

		if (i % 5 == 0)
			Sleep(15);
		i++;
		x1 += 0.2;
	}





	for (double x = -11.0; x < 10.9; x += 0.1) {
		MoveToEx(screen, x * 10 + CENTREX, -10 * sqrt(121.00 - (x * x)) + СENTREY, NULL);
		LineTo(screen, (x + 0.1) * 10 + CENTREX, -10 * sqrt(121.00 - ((x + 0.1) * (x + 0.1))) + СENTREY);

		MoveToEx(screen, x * 10 + CENTREX, -10 * -sqrt(121.00 - (x * x)) + СENTREY, NULL);
		LineTo(screen, (x + 0.1) * 10 + CENTREX, -10 * -sqrt(121.00 - ((x + 0.1) * (x + 0.1))) + СENTREY);

		if (i % 6 == 0)
			Sleep(10);
		i++;
	}
	



	Sleep(1000);
}

void authr()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD position;
	position.X = 45;
	position.Y = 7;
	SetConsoleCursorPosition(color, position);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY || FOREGROUND_BLUE);
	printf("_______________________________");
	position.X = 44;
	position.Y = 8;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 9;
	SetConsoleCursorPosition(color, position);
	printf("|       -Студент ФИТиКС-        |");
	position.X = 44;
	position.Y = 10;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|");
	position.X = 44;
	position.Y = 11;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 12;
	SetConsoleCursorPosition(color, position);
	printf("|        -Группы ПИН-221-       |");
	position.X = 44;
	position.Y = 13;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|");
	position.X = 44;
	position.Y = 14;
	SetConsoleCursorPosition(color, position);
	printf("|                               |");
	position.X = 44;
	position.Y = 15;
	SetConsoleCursorPosition(color, position);
	printf("|  <-Димитров Иван Симонович->  |");
	position.X = 44;
	position.Y = 16;
	SetConsoleCursorPosition(color, position);
	printf("|_______________________________|\n");
	_getch();
}



int main()
{
	

	//SetConsoleWindowInfo();
	//string Menu[] = { "0. Графическая заставка","1. Об авторе", "2. Построение таблицы", "3. Построение графиков", "4. Решение уравнения", "5. Вычисление интеграла", "6. Выход" };
	string Menu[] = { "Графическая заставка","Об авторе", "Построение таблицы", "Построение графиков", "Решение уравнения", "Вычисление интеграла", "Выход" };
	int activateMenu = 0;
	char click;


	SetConsoleTitle(L"Расчетно-графическая работа");
	setlocale(0, "RUS");
	ConsoleCursorVisible();

	menuAnim(Menu);
	
	

	while (true) {
		int x = 45, y = 11;

		for (int i = 0; i < size(Menu); i++)
		{
			if (i == activateMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			GoToXY(x, y++);
			cout << Menu[i] << endl;
		}

		click = _getch();

		switch (click)
		{
		case ESC:
			exit(0);
		case UP:
			if (activateMenu > 0)
				--activateMenu;
			break;
		case DOWN:
			if (activateMenu < size(Menu) - 1)
				++activateMenu;
			break;
		case ENTER:
			switch (activateMenu)
			{
			case 0: 
				system("CLS");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				animation();
				system("CLS");
				break;
			case 1: 
				system("CLS");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				authr();
				system("CLS");
				break;
			case 2: 
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				//table();
				system("CLS");
				break;
			case 3:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				//grafik();
				system("CLS");
				break;
			case 4:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				//uravn();
				system("CLS");
				break;
			case 5:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				//integral();
				//_getch();
				system("CLS");
				break;
			case 6:
				exit(0);
			}
			break;
		//default:
		//	cout << "Код " << (int)click << endl;
		}

	}



}

/* variant 1
	i = 1;
	for (double x = -9.0; x <= 9.0; x+=0.1) {

		if (x > 0 && ((sqrt(20 * (x + 0.1))) < 9.0)) {
			// 1
			MoveToEx(screen, x * 20 + CENTREX, -20 * (sqrt(20 * x)) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (sqrt(20 * (x + 0.1))) + СENTREY);
			//4
			MoveToEx(screen, x * 20 + CENTREX, -20 * (sqrt(2.5 * x)) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (sqrt(2.5 * (x + 0.1))) + СENTREY);
			//5
			MoveToEx(screen, x * 20 + CENTREX, -20 * (-0.4 * (pow(sqrt(x), 4))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (-0.4 * (pow(sqrt(x + 0.1), 4))) + СENTREY);
			//6
			MoveToEx(screen, x * 20 + CENTREX, -20 * (-0.05 * (pow(sqrt(x), 4))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (-0.05 * (pow(sqrt(x + 0.1), 4))) + СENTREY);
		}
		else if (x < 0 && ((-(sqrt(20 * (-(x + 0.1))))) > -9.0)) {
			//2
			MoveToEx(screen, x * 20 + CENTREX, -20 * (-(sqrt(20 * x))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (-(sqrt(20 * (x + 0.1)))) + СENTREY);
			//3
			MoveToEx(screen, x * 20 + CENTREX, -20 * (-(sqrt(2.5 * x))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (-(sqrt(2.5 * (x + 0.1)))) + СENTREY);
			//7
			MoveToEx(screen, x * 20 + CENTREX, -20 * (0.05 * (pow(sqrt(x), 4))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (0.05 * (pow(sqrt(x + 0.1), 4))) + СENTREY);
			//8
			MoveToEx(screen, x * 20 + CENTREX, -20 * (0.4 * (pow(sqrt(x), 4))) + СENTREY, NULL);
			LineTo(screen, (x + 0.1) * 20 + CENTREX, -20 * (0.4 * (pow(sqrt(x + 0.1), 4))) + СENTREY);
		}

		if (i%3 == 0)
			Sleep(22);
		i++;
		//y = sqrt(x + CENTREX)
	}*/