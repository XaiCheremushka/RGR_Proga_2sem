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
	if (y <= 10.0 && y >= -10.0) 
		return y;
	else 
		return 404.0;
}



//Анимация меню
void menuAnim(string Menu[7]) {
	setlocale(0, "RUS");
	
	int kPoz = KPG; // предельная точка
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	for (int i = 6; i >= 0; i--) {
		for (int j = 0; j <= kPoz; j++) {
			Sleep(10);
			ConsoleCursorVisible();
			GoToXY(45, j - 1);
			cout << "                                  " << endl;
			GoToXY(45, j);
			cout << Menu[i] << endl;
			if (kPoz < KPG)
				for (int l = KPG; l >= kPoz + 1; l--) {
					GoToXY(45, l);
					//cout << Menu[size(Menu)-(KPG-l)-1] << endl;
					cout << Menu[7 - (KPG - l) - 1] << endl;
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
	SelectObject(screen, arevCircle);
	i = 1;
	double x1 = 0.2;
	double x2 = 0.0;
	double x3 = 0.0;
	
	for (double x = 0.1; x <= 5.0; x += 0.1) {
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
		if (i <= 25) {
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
		
		if (i % 3 == 0)
			Sleep(22);
		i++;
		x1 += 0.2;
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

void table()
{
	HANDLE table = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(table, FOREGROUND_BLUE);
	int i;
	float F1[20], F2[20], dx, x[20], b = 3.1416, a = -b;
	dx = fabs(b - a) / 19.0;
	x[0] = a;
	SetConsoleTextAttribute(table, FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("\n F1 = 2 - cos(x)  F2 = |x + 10|^3 \n");
	SetConsoleTextAttribute(table,  FOREGROUND_RED);
	printf("\n Максимальные значения функций F1 и F2 - красный цвет\n");
	SetConsoleTextAttribute(table, FOREGROUND_GREEN);
	printf("\n Минимальные значения функций F1 и F2 - зеленый цвет\n");
	SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf(" _________________________________________\n");
	printf("|   I   |    X    |    F1    |     F2     |\n");
	printf("|-------|---------|----------|------------|\n");
	for (i = 0; i < 20; i++)
	{
		F1[i] = 2 - cos(x[i]);
		F2[i] = pow(abs(x[i] + 10), 3);
		if (i != 19)
			x[i + 1] = x[i] + dx;
		else 
			x[i] = x[i] + dx;
	}
	float max1, max2, min1, min2;
	max1 = F1[0];
	min1 = F1[0];
	max2 = F2[0];
	min2 = F2[0];
	for (i = 1; i < 20; i++)
	{
		if (F1[i] > max1) max1 = F1[i];
		if (F1[i] < min1) min1 = F1[i];
		if (F2[i] > max2) max2 = F2[i];
		if (F2[i] < min2) min2 = F2[i];
	}
	for (i = 0; i < 20; i++)
	{
		if (x[i] < 0.0)
			printf("|  %3d  |  %5.3f |", i + 1, x[i]);
		else 
			printf("|  %3d  |   %5.3f |", i + 1, x[i]);

		if (F1[i] == max1)
		{
			SetConsoleTextAttribute(table,  FOREGROUND_RED);
			printf("  %6.3f  ", F1[i]);
			SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("|");
		}
		else
		{
			if (F1[i] == min1)
			{
				SetConsoleTextAttribute(table, FOREGROUND_GREEN);
				printf("  %6.3f  ", F1[i]);
				SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("|");
			}
			else
			{
				SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("  %6.3f  |", F1[i]);
			}
		}

		if (F2[i] == max2)
		{
			SetConsoleTextAttribute(table,  FOREGROUND_RED);
			printf("  %6.3f  ", F2[i]);
			SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("|\n");
		}
		else
		{
			if (F2[i] < 1000)
				printf(" ");
			if (F2[i] == min2)
			{
				SetConsoleTextAttribute(table, FOREGROUND_GREEN);
				printf("  %6.3f  ", F2[i]);
				SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("|\n");
			}
			else
			{
				SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("  %6.3f  |\n", F2[i]);
			}
		}
	}
	printf("|_______|_________|__________|____________|\n");
	SetConsoleTextAttribute(table, FOREGROUND_GREEN | FOREGROUND_BLUE);
	_getch();

	
}

void graficF2() {
	system("cls");
	int pravka;

	HDC screen = GetDC(GetConsoleWindow());
	HPEN pen_white = CreatePen(PS_DASH, 2, RGB(255, 255, 255));
	HPEN pen = CreatePen(PS_DASH, 2, RGB(255, 0, 0));
	HPEN pen2 = CreatePen(PS_DASH, 2, RGB(255, 100, 120));
	SelectObject(screen, pen_white);
	//const int CENTREX = 550;
	//const int CENTREY = 300;
	// Ось Х
	MoveToEx(screen, CENTREX - 238, СENTREY, NULL);
	LineTo(screen, CENTREX + 400, СENTREY);
	// Ось У
	MoveToEx(screen, CENTREX, СENTREY - 250, NULL);
	LineTo(screen, CENTREX, СENTREY + 250);
	// Стрелочка у оси Х
	MoveToEx(screen, CENTREX + 400 - 25, СENTREY + 10, NULL);
	LineTo(screen, CENTREX + 400, СENTREY);
	LineTo(screen, CENTREX + 400 - 25, СENTREY - 10);
	// Стрелочка у оси У
	MoveToEx(screen, CENTREX + 10, СENTREY - 240 + 25, NULL);
	LineTo(screen, CENTREX, СENTREY - 240);
	LineTo(screen, CENTREX - 10, СENTREY - 240 + 25);
	// Палочки
	for (int i = -238; i <= 360; i += 20) {
		MoveToEx(screen, CENTREX + i, СENTREY - 5, NULL);
		LineTo(screen, CENTREX + i, СENTREY + 5);
	}
	for (int i = -200; i <= 240; i += 20) {
		MoveToEx(screen, CENTREX - 5, СENTREY + i, NULL);
		LineTo(screen, CENTREX + 5, СENTREY + i);
	}
	// Подпись осей и начала координат
	SetBkMode(screen, TRANSPARENT);
	SetTextColor(screen, RGB(255, 255, 255));
	TextOut(screen, CENTREX + 15, СENTREY - 230, L"Y", 1);
	TextOut(screen, CENTREX + 380, СENTREY + 15, L"X", 1);
	TextOut(screen, CENTREX - 12, СENTREY + 2, L"0", 1);
	TextOut(screen, CENTREX + 15, СENTREY + 10, L"3", 1);
	TextOut(screen, CENTREX - 40, СENTREY - 27, L"300", 3);
	// Подпись кривой функции
	SetTextColor(screen, RGB(255, 0, 0));
	TextOut(screen, CENTREX + 200, СENTREY - 110, L"y = |x + 10|^3", 18);
	// Cам график
	SelectObject(screen, pen2);
	int i = 1;
	for (double x = -20; x < -3.1416; x += 0.01) {
		MoveToEx(screen, 6.6 * x + CENTREX, -0.066 * pow(abs(x + 10), 3) + СENTREY, NULL);
		LineTo(screen, 6.6 * (x + 0.01) + CENTREX, -0.066 * pow(abs((x + 0.01) + 10), 3) + СENTREY);
		i++;
		if (i % 20 == 0)
			Sleep(1);
	}
	SelectObject(screen, pen);
	i = 1;
	for (double x = -3.1416; x <= 3.1416; x += 0.01) {
		MoveToEx(screen, 6.6 * x + CENTREX, -0.066 * pow(abs(x + 10), 3) + СENTREY, NULL);
		LineTo(screen, 6.6 * (x + 0.01) + CENTREX, -0.066 * pow(abs((x + 0.01) + 10), 3) + СENTREY);
		i++;
		if (i % 20 == 0)
			Sleep(1);
	}
}

void grafik()
{
	system("cls");
	int pravka;

	HDC screen = GetDC(GetConsoleWindow());
	HPEN pen_white = CreatePen(PS_DASH, 2, RGB(255, 255, 255));
	HPEN pen = CreatePen(PS_DASH, 2, RGB(80, 170, 220));
	HPEN pen2 = CreatePen(PS_DASH, 2, RGB(255, 0, 0));
	SelectObject(screen, pen_white);
	//const int CENTREX = 550;
	//const int CENTREY = 300;
	// Ось Х
	MoveToEx(screen, CENTREX - 238, СENTREY, NULL);
	LineTo(screen, CENTREX + 400, СENTREY);
	// Ось У
	MoveToEx(screen, CENTREX, СENTREY - 250, NULL);
	LineTo(screen, CENTREX, СENTREY + 250);
	// Стрелочка у оси Х
	MoveToEx(screen, CENTREX + 400 - 25, СENTREY + 10, NULL);
	LineTo(screen, CENTREX + 400, СENTREY);
	LineTo(screen, CENTREX + 400 - 25, СENTREY - 10);
	// Стрелочка у оси У
	MoveToEx(screen, CENTREX + 10, СENTREY - 240 + 25, NULL);
	LineTo(screen, CENTREX, СENTREY - 240);
	LineTo(screen, CENTREX - 10, СENTREY - 240 + 25);
	// Палочки
	for (int i = -238; i <= 360; i += 20) {
		MoveToEx(screen, CENTREX + i, СENTREY - 5, NULL);
		LineTo(screen, CENTREX + i, СENTREY + 5);
	}
	for (int i = -200; i <= 240; i += 20) {
		MoveToEx(screen, CENTREX - 5, СENTREY + i, NULL);
		LineTo(screen, CENTREX + 5, СENTREY + i);
	}
	// Подпись осей и начала координат
	SetBkMode(screen, TRANSPARENT);
	SetTextColor(screen, RGB(255, 255, 255));
	TextOut(screen, CENTREX + 15, СENTREY - 230, L"Y", 1);
	TextOut(screen, CENTREX + 380, СENTREY + 15, L"X", 1);
	TextOut(screen, CENTREX - 12, СENTREY + 2, L"0", 1);
	TextOut(screen, CENTREX + 15, СENTREY + 10, L"1", 1);
	TextOut(screen, CENTREX - 15, СENTREY - 27, L"1", 1);
	// Подпись кривой функции
	SetTextColor(screen, RGB(80, 170, 220));
	TextOut(screen, CENTREX + 250, СENTREY - 80, L"y = 2 - cos(x)", 15);
	SetTextColor(screen, RGB(255, 0, 0));
	TextOut(screen, CENTREX + 200, СENTREY - 110, L"y = |x + 10|^3", 18);
	// Cам график
	int i = 1;
	SelectObject(screen, pen);
	for (double x = -3.1416; x <= 3.1416; x += 0.01) {
		MoveToEx(screen, 20 * x + CENTREX, -20 * (2 - cos(x)) + СENTREY, NULL);
		LineTo(screen, 20 * (x + 0.01) + CENTREX, -20 * (2 - cos(x + 0.01)) + СENTREY);
		i++;
		if (i % 20 == 0)
			Sleep(1);
	}
	_getch();
	graficF2();
	_getch();
}


double f1(double x)
{
	return 0.5 + cos(x) - 2 * x * sin(x);
}


void uravn()
{
	GoToXY(0, 0);
	double a, b, e = 0.001, x = 0; // e - точность
	cout << "Уравнение 0.5 + cos(x) - 2 * x * sin(x) = 0." << endl;
	cout << "Введите начало промежутка » ";
	cin >> a;
	cout << "Введите конец промежутка » ";
	cin >> b;
	//cout << "Введите точность » ";
	//cin >> e;
	if (f1(a) * f1(b) < 0)
	{
		while (true)
		{
			x = (a + b) / 2;
			if (fabs(f1(x)) < e) break;
			if (f1(a) * f1(x) < 0)
			{
				a = a;
				b = x;
			}
			else
			{
				a = x;
				b = b;
			}
		}
		cout << "Метод половинного деления" << endl;
		cout << "Корень x = " << x << endl;
		while (true)
		{
			x = (a * f1(b) - b * f1(a)) / (f1(b) - f1(a));
			if (fabs(f1(x)) < e) break;
			if (f1(a) * f1(x) < 0)
			{
				a = a;
				b = x;
			}
			else
			{
				a = x;
				b = b;
			}
		}
		cout << "Метод хорд" << endl;
		cout << "Корень x = " << x << endl;
	}
	else
	{
		cout << "Условие сходимости не выполнено" << endl;
	}
	_getch();
}

double f(double x)
{
	return cos(x) / (sin(x) + cos(x));
}
double left_rect(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0.0;
	for (int i = 0; i <= n - 1; i++) {
		sum += h * f(a + i * h);
	}
	return sum;
}
double right_rect(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0.0;
	for (int i = 1; i <= n; i++) {
		sum += h * f(a + i * h);
	}
	return sum;
}
double trap(double a, double b, int n) {
	double h = (b - a) / n;
	double sum = f(a) + f(b);
	for (int i = 0; i <= n - 1; i++) {
		sum += 2 * f(a + i * h);
	}
	sum *= h / 2;
	return sum;
}

void integral()
{
	GoToXY(0,0);
	double a, b;
	int n;
	float h, x, f;
	printf("Вычисление интеграла cos(x) / (sin(x) + cos(x))\n");
	cout << "Введите нижний предел интегрирования - ";
	cin >> a;
	//a = 1;
	//b = 2;
	cout << "\nВведите верхний предел интегрирования - ";
	cin >> b;
	//n = 1000;
	cout << "\nВведите количество частей, на которые следует разделить интервал интегрирования - ";
	cin >> n;
	const double eps = 0.001;
	int k = 10;
	int i = 0;
	double diff;
	do {
		i++;
		diff = fabs(left_rect(a, b, k * i) - left_rect(a, b, k * (i + 1)));
	} while (diff > eps);
	do {
		i++;
		diff = fabs(right_rect(a, b, k * i) - right_rect(a, b, k * (i + 1)));
	} while (diff > eps);
	do {
		i++;
		diff = fabs(trap(a, b, k * i) - trap(a, b, k * (i + 1)));
	} while (diff > eps);
	cout << "Метод левых прямоугольников = " << left_rect(a, b, k * (i + 1)) << "\n";
	cout << "Метод правых прямоугольников = " << right_rect(a, b, k * (i + 1)) << "\n";
	cout << "Метод трапеций = " << trap(a, b, k * (i + 1));
	_getch();
}

int main()
{
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
				table();
				system("CLS");
				break;
			case 3:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				grafik();
				system("CLS");
				break;
			case 4:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				uravn();
				system("CLS");
				break;
			case 5:
				system("CLS");
				GoToXY(x, y);
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				integral();
				_getch();
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
