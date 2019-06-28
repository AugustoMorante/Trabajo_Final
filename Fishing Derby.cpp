
#include "stdafx.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
constexpr auto ARRIBA = 72; //Asignar flecha ARRIBA del teclado
constexpr auto ABAJO = 80; //Asignar flecha ABAJO del teclado
using namespace std;
using namespace System;

void ObtenerXY(int x, int y)//Nos permite ubicar los caracteres a traves de coordenadas
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}

void OcultarCursor()//Este codigo oculta al cursor, mejorando la estetica del juego
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO c;
	c.dwSize = 1;
	c.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &c);
	return;
}

int UAX(int n)//UbicacionAleatoriaX - Genera la ubicacion aleatoria de los peces respecto a las columnas
{
	int x, i = 1;
	srand(time(NULL));
	while (i <= n)
	{
		x = 26 + rand() % (75 - 26);
		i++;
	}
	return x;
}

int UAY(int n)//UbicacionAleatoriaY - Genera la ubicacion aleatoria de los peces respecto a las filas
{
	int y, i = 1;
	srand(time(NULL));
	while (i <= n)
	{
		y = 11 + rand() % (25 - 11);
		i++;
	}
	return y;
}

int UADX(int n)//UbicacionAleatoriaDX - Genera la direccion de los peces solo puede devolver +1 o -1
{
	int dx, i = 1, num;
	srand(time(NULL));
	while (i <= n)
	{
		num = 1 + rand() % (11 - 1);
		i++;
	}
	if (num % 2 == 0)
	{
		dx = 1;
	}
	else
	{
		dx = -1;
	}
	return dx;
}

void ParteFija() //El escenario del juego, pescador y caña
{
	//MuellePlataforma
	for (int i = 0; i < 30; i++)
	{
		ObtenerXY(i, 6); cout << "=";
	}

	//MuelleParteInferiorMuelle
	for (int i = 0; i < 30; i = i + 2)
	{
		ObtenerXY(i, 7); cout << "/|";
	}



	//CañaDiagonal
	for (int i = 5; i > 1; i--)
	{
		for (int j = 29; j < 36; j = j + 2)
		{
			if (i == 2 && j == 35 || i == 3 && j == 33 || i == 4 && j == 31 || i == 5 && j == 29)
			{
				ObtenerXY(j, i); cout << " /";
			}
		}
	}

	//CañaHorizontal
	for (int i = 38; i < 50; i++)
	{
		ObtenerXY(i, 1); cout << "_";
	}

	//PescadorTorso
	for (int i = 4; i < 6; i++)
	{
		ObtenerXY(27, i); cout << "|";
	}

	//PescadorRodilla
	ObtenerXY(28, 5); cout << "/";

	//PescadorPierna
	ObtenerXY(29, 5); cout << "|";

	//PescadorCabeza
	ObtenerXY(27, 3); cout << "O";

	//PescadorBrazo

	ObtenerXY(28, 4); cout << "-";

	//MuelleSoporte
	for (int i = 8; i < 25; i++)
	{
		ObtenerXY(25, i); cout << "|";
	}

	//Titulo - Integrantes - Instrucciones 
	ObtenerXY(5, 10); cout << "Fishing Derby";
	ObtenerXY(4, 14); cout << "Augusto Morante";
	ObtenerXY(6, 16); cout << "José Roncal";
	ObtenerXY(5, 19); cout << "/\\: Subir caña";
	ObtenerXY(5, 21); cout << "\\/: Bajar caña";

	return;
}

void postgame(int vida)
{
	ObtenerXY(5, 10); cout << "             ";
	ObtenerXY(5, 19); cout << "              ";
	ObtenerXY(5, 21); cout << "              ";


	if (vida < 0)
	{
		ObtenerXY(7, 10); cout << "Game Over";
	}
	else
	{
		ObtenerXY(8, 10); cout << "Ganaste";
		ObtenerXY(6, 11); cout << "Felicidades";
	}

	ObtenerXY(2, 19); cout << "UPC - Programacion I";
	ObtenerXY(8, 21); cout << "2019-1";
}

int ganancia(int &y, int &c) //Regula el puntaje obtenido segun la ubicacion del pez
{
	int g;

	if (y >= 11 && y <= 13)
	{
		g = 10;
		c = 0;
	}
	if (y >= 14 && y <= 16)
	{
		g = 15;
		c = 0;
	}
	if (y >= 17 && y <= 19)
	{
		g = 20;
		c = 0;
	}
	if (y >= 20 && y <= 22)
	{
		g = 25;
		c = 0;
	}
	if (y == 23 || y == 24)
	{
		g = 30;
		c++;
	}
	return g;
}

int rt(int &n)//Regulacion del tiempo de acuerdo al nivel (+dificultad)	
{
	int m;

	if (n == 1)
		m = 4;

	if (n == 2)
		m = 2;

	if (n == 3)
		m = 1;

	return m;
}

//Matriz del tiburón
int tiburon[6][3] = { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } };
void tibu(int &x, int &y) { //Dibujo del tburon en direccion a la derecha - x & y son las coordenadas de la ubicación del tiburon
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 && j == 0 || i == 0 && j == 4) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "\\";
			}
			if (i == 0 && j == 3 || i == 2 && j == 3)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "|";
			}
			if (i == 1 && j == 1 || i == 1 && j == 2 || i == 1 && j == 3)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "<";
			}
			if (i == 1 && j == 4)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "O";
			}
			if (i == 1 && j == 5)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << ">";
			}
			if (i == 2 && j == 0 || i == 2 && j == 4) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "/";
			}
			if (i == 1 && j == 0 || i == 0 && j == 1 || i == 0 && j == 2 || i == 0 && j == 5 || i == 2 && j == 1 || i == 2 && j == 2 || i == 2 && j == 5)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << " ";
			}
		}
	}
}
void tibuInvertido(int &x, int &y) { //Dibujo del tiburon en direccion a la izquierda - x & y son las coordenadas de la ubicación del tiburon
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 && j == 1 || i == 0 && j == 5) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "/";
			}
			if (i == 0 && j == 2 || i == 2 && j == 2)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "|";
			}
			if (i == 1 && j == 2 || i == 1 && j == 3 || i == 1 && j == 4)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << ">";
			}
			if (i == 1 && j == 1)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "O";
			}
			if (i == 1 && j == 0)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "<";
			}
			if (i == 2 && j == 1 || i == 2 && j == 5) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "\\";
			}
			if (i == 0 && j == 0 || i == 2 && j == 0 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 5 || i == 2 && j == 3 || i == 2 && j == 4)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << " ";
			}
		}
	}
}
void borrarTibu(int &x, int &y) { //Matriz 6x3 de caracteres en blanco - x & y son las coordenadas de la ubicación del tiburon
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (tiburon[i][j]) {
				Console::SetCursorPosition(x + j, y + i);
				cout << " ";
			}
		}
	}
}

void movimientoTiburon(int &x, int &y, int &dx) //Une a las tres funciones anteriores
{
	borrarTibu(x, y);
	if (x + dx < 26 || x + dx + 5 == 80)dx = -dx;
	x += dx;
	if (dx > 0)
	{
		tibu(x, y);
	}
	else
	{
		tibuInvertido(x, y);
	}
	return;
}

bool tiburonComer(int &x, int &y) //Indica cuando el tiburon puede comerse a los peces teniendo como bases la ubicacion
{
	bool comer = 0;
	if (y == 8 || y == 9 || y == 10)
	{
		if (x == 48 || x == 49 || x == 50 || x == 51 || x == 52)
		{
			comer = 1;
		}
	}
	return comer;
}

int peces[4][1] = { { 1 },{ 1 },{ 1 },{ 1 } };//Matriz de un pez
void pez(int &x, int &y) {//Dibujo del pez en direccion a la derecha
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0 || j == 3) {
				Console::SetCursorPosition(x + j, y + i);
				cout << ">";
			}
			if (j == 1)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "<";
			}
			if (j == 2)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "O";
			}
		}
	}
}
void pezInvertido(int &x, int &y) {//Dibujo del pez en direccion a la izquierda
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0 || j == 3) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "<";
			}
			if (j == 1)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "O";
			}
			if (j == 2)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << ">";
			}
		}
	}
}
void borrarPez(int &x, int &y) {//Dibujo en blanco de la matriz 4x1
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0 || j == 3) {
				Console::SetCursorPosition(x + j, y + i);
				cout << "  ";
			}
			if (j == 1)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "  ";
			}
			if (j == 2)
			{
				Console::SetCursorPosition(x + j, y + i);
				cout << "  ";
			}
		}
	}
}


void enganche(int &x, int &y, int &dx)//Permite el enganche del pez a la caña
{

	ObtenerXY(x + 1, y + 1); cout << "       ";
	ObtenerXY(x - 1, y - 1); cout << "       ";

	if (dx > 0)
	{
		pez(x, y);
	}
	else
	{
		pezInvertido(x, y);
	}

	return;
}

//Esta función, ademas de permitir el desplazamiento de los peces, se encarga tambien de la interaccion de estos con la caña y el tiburon
int movimientoPez(int &x, int &y, int t, int &x1, int &y1, int &dx, int &ox1, int&oy1, int &xt, int &n, int &c, int &m, int &v, int &libras)
{
	int azahar;
	if (x != x1 && x1 != 2 || y != y1 && x1 != 2)//Permite el desplazamiento solamente cuando el pez no entra en contacto con el caracter de la caña
	{
		borrarPez(x1, y1);
		if (x1 + dx < 26 || x1 + dx + 3 == 80)dx = -dx;
		x1 += dx;

		if (t == 4 && n == 3 || t == 5 && n == 3 || t == 6 && n == 3 || t == 6 && n == 2)//Elimina los peces segun el nivel del juego
		{
			borrarPez(x1, y1);
		}
		else
		{
			if (dx > 0)
			{
				pez(x1, y1);
			}
			else
			{
				pezInvertido(x1, y1);
			}
		}
	}
	else
	{
		x1 = 2;
		ObtenerXY(x, y);
		enganche(x, y, dx);
		if (x == 50, y == 5)//Suelta al cuando llega al punto más alto
		{
			x1 = ox1;
			y1 = oy1;
			ObtenerXY(x, y); cout << "     ";
			libras = libras + ganancia(oy1, c);
		}
		if (tiburonComer(xt, y) == 1)//El pez se regenera a su punto de partida original si entra en contacto con el tiburon
		{
			x1 = ox1;
			y1 = oy1;
			ObtenerXY(x, y); cout << "     ";
			c = 0;
		}
		if (c == 3)
		{
			azahar = rand() % 10;
			if (azahar == 0)
			{
				v++;
				c = 0;
			}
			else
			{
				m++;
				c = 0;
			}
		}
		if (c > 3)
			c = 0;
	}
	return libras;//retorna las libras ganadas
}

void main() {
	setlocale(LC_ALL, "spanish");
	OcultarCursor();
	ParteFija();
	bool gameOver = 0;
	int x = 50, y = 4;
	ObtenerXY(x, y); cout << "|";
	int nivel = 1, libras = 90, vida = 3, c = 0;
	int minutos = rt(nivel), segundos = 59, ms = 5;
	int x0 = 26, y0 = 8, dx0 = 1;//Punto de partida del tiburon
	//Punto de partida delos peces - todos son aleatorios
	int x1 = UAX(1), y1 = UAY(1), dx1 = UADX(1);//x1
	int x2 = UAX(2), y2 = UAY(2), dx2 = UADX(2);//x2
	int x3 = UAX(3), y3 = UAY(3), dx3 = UADX(3);//x3
	int x4 = UAX(4), y4 = UAY(4), dx4 = UADX(4);//x4
	int x5 = UAX(5), y5 = UAY(5), dx5 = UADX(5);//x5
	int x6 = UAX(6), y6 = UAY(6), dx6 = UADX(6);//x6

	//Puntos de partida originales de los peces, nunca cambian durante el transcurso del juego
	int ox1 = x1, oy1 = y1;
	int ox2 = x2, oy2 = y2;
	int ox3 = x3, oy3 = y3;
	int ox4 = x4, oy4 = y4;
	int ox5 = x5, oy5 = y5;
	int ox6 = x6, oy6 = y6;


	while (gameOver == false)
	{
		//Display
		ObtenerXY(0, 0); cout << "NIVEL " << nivel;
		ObtenerXY(22, 0); cout << "VIDAS " << vida;
		ObtenerXY(42, 0); cout << "LIBRAS ";
		if (libras >= 10 && libras <= 99)
			cout << "0";
		if (libras >= 0 && libras <= 9)
			cout << "00";
		cout << libras;
		ObtenerXY(65, 0); cout << "TIEMPO 0" << minutos << " : ";
		if (segundos >= 0 && segundos <= 9)
			cout << "0";
		cout << segundos;

		//AguaLimite
		for (int i = 30; i < 80; i = i + 2)
		{
			ObtenerXY(i, 7); cout << " ~";
		}

		//CañaCuerdaFija
		for (int i = 2; i < 4; i++)
		{
			ObtenerXY(50, i); cout << "|";
		}

		//Permite la entrada en el juego usando las flechas
		if (_kbhit())
		{
			char tecla = _getch();
			if (tecla == ABAJO)
			{
				if (y > 23)
				{
					y--;
				}
				else
				{
					y++;
				}
			}
			if (y != 4)
			{
				ObtenerXY(x, y); cout << " ";
			}
			if (tecla == ARRIBA)
			{
				if (y < 5)
				{
					y++;
				}
				else
				{
					y--;
					ObtenerXY(50, 24); cout << " ";
				}
			}
			ObtenerXY(x, y); cout << "|";
			for (int i = 4; i < y + 1; i++)
			{
				ObtenerXY(x, i); cout << "|";
			}
		}

		movimientoTiburon(x0, y0, dx0);

		libras = movimientoPez(x, y, 1, x1, y1, dx1, ox1, oy1, x0, nivel, c, minutos, vida, libras);

		libras = movimientoPez(x, y, 2, x2, y2, dx2, ox2, oy2, x0, nivel, c, minutos, vida, libras);

		libras = movimientoPez(x, y, 3, x3, y3, dx3, ox3, oy3, x0, nivel, c, minutos, vida, libras);

		libras = movimientoPez(x, y, 4, x4, y4, dx4, ox4, oy4, x0, nivel, c, minutos, vida, libras);

		libras = movimientoPez(x, y, 5, x5, y5, dx5, ox5, oy5, x0, nivel, c, minutos, vida, libras);

		libras = movimientoPez(x, y, 6, x6, y6, dx6, ox6, oy6, x0, nivel, c, minutos, vida, libras);


		//Permite el desplazamiento del tiempo indicando sus limites junto con las condiciones
		ms--;
		if (ms < 0)
		{
			segundos--;
			ms = 5;
		}
		if (segundos < 0)
		{
			segundos = 59;
			ms = 5;
			minutos--;
		}

		if (minutos < 0)
		{
			vida--;
			c = 0;
			minutos = rt(nivel);
			segundos = 59;
			ms = 5;
		}

		if (vida < 0)
			gameOver = 1;

		if (libras >= 100)
		{
			nivel++;
			c = 0;
			libras = 90;
			minutos = rt(nivel);
			segundos = 59;
			ms = 5;
		}

		if (nivel > 3)
			gameOver = 1;

		_sleep(100);
	}

	postgame(vida);

	_getch();
}


//FUNCIONALIDAD ADICIONAL

/*

Cuando el jugador pesque 3 peces de las 2 últimas filas de FORMA CONSECUTIVA obtendra un bono

 El bono varía segun probabilidad:
 - 1 minuto extra (90%)
 - 1 vida extra (10%)

 En caso si el jugador pesca un pez de una fila más arriba o el tiburon se coma a un pez, el contador regresa a 0

*/