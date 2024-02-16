#include <iostream>
#include <conio2.h>
#include <ctime>
#include <vector>
#include <windows.h>
using namespace std;

class Obstaculo {
private:
	int x;
	int y;
	
public:
	Obstaculo(int posX, int posY) : x(posX), y(posY) {}
	
	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
	void mover() {
		// Mover horizontalmente hacia la izquierda
		x--;
		
		// Si el obstáculo llega al borde izquierdo, reiniciar en el borde derecho
		if (x <= 1) {
			x = 24;
		}
	}
	
	void dibujar() {
		gotoxy(x, y);
		putch('O');
	}
};

class Rana {
private:
	int x;
	int y;
	int puntaje;
	
public:
	Rana(): puntaje (0) {	
		reiniciarPosicion();	
//		x = 12;  // Posición inicial en el eje X
//		y = 11; // Posición inicial en el eje Y
	}	
	
	void reiniciarPosicion() {
		x = 12;  // Posición inicial en el eje X
		y = 11;  // Posición inicial en el eje Y
	}
	
	void aumentarPuntaje(int puntos) {
		puntaje += puntos;
	}
	
	int getPuntaje() const {
		return puntaje;
	}
	
	
	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
	void moverArriba() {
		if (y > 0) {
			y = y - 1;
		}
	}
	
	void moverAbajo() {
		if (y < 15) { // Ajusta el límite inferior según la altura de tu consola
			y = y + 1;
		}
	}
	
	void dibujar() {
		clrscr();
		
		//lineas de los laterales
		for (int i = 2; i < 11; ++i) {
			gotoxy(1, i);
			cout << "|";
			gotoxy(24, i);
			cout << "|";
		}
		
		//líneas superior e inferior
		for (int i = 2; i <= 23; ++i) {
			gotoxy(i, 1);
			cout << "_";
			gotoxy(i,5);
			cout << "_";
			gotoxy(i,6);
			cout << "_";
			gotoxy(i,10);
			cout << "_";
		}
		
		gotoxy(x, y);
		putch('R');
	}
	
	bool colision(Obstaculo &obstaculo) {
		return x == obstaculo.getX() && y == obstaculo.getY();
	}
	
	void manejarEntrada() {
		if (_kbhit()) {
			int tecla = getch();
			if (tecla == 72) { // Código ASCII para la tecla arriba
				moverArriba();
			} else if (tecla == 80) { // Código ASCII para la tecla abajo
				moverAbajo();
			}
		}
	}
};

void esperar(int milisegundos) {
	clock_t fin = clock() + milisegundos * CLOCKS_PER_SEC / 1000;
	while (clock() < fin) {
	}
}

int main(int argc, char *argv[]) {
	clrscr();
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	
	Rana rana;
	
	// Crear varios obstáculos
	vector<Obstaculo> obstaculos;
	obstaculos.push_back(Obstaculo(24, 2));
	obstaculos.push_back(Obstaculo(13, 4));
	obstaculos.push_back(Obstaculo(18, 7));
	obstaculos.push_back(Obstaculo(17, 9));
	obstaculos.push_back(Obstaculo(8, 3));
	obstaculos.push_back(Obstaculo(12, 8));
	obstaculos.push_back(Obstaculo(14, 2));
	obstaculos.push_back(Obstaculo(22, 9));
	obstaculos.push_back(Obstaculo(7, 8));
	obstaculos.push_back(Obstaculo(15, 3));
	obstaculos.push_back(Obstaculo(3, 10));	
	obstaculos.push_back(Obstaculo(22, 4));	
	
	
	while (true) {  // Bucle principal del juego
		rana.dibujar();
		
		// Mover y dibujar cada obstáculo
		for (Obstaculo &obstaculo : obstaculos) {
			obstaculo.mover();
			obstaculo.dibujar();
			
			// Lógica de colisiones
			if (rana.colision(obstaculo)) {
				clrscr();
				cout << "¡Colisión! Juego terminado." << endl;
				return 0;
			}
		}
		
		// Verificar si la rana ha llegado a la posición de victoria
		if (rana.getY() == 1) {
			rana.reiniciarPosicion();  // Reiniciar posición de la rana
			rana.aumentarPuntaje(50); // Aumentar puntaje al ganar
			clrscr();
			cout << "¡Has ganado! Puntaje: " << rana.getPuntaje() << endl;
			esperar(2000); 
		}
		
		// Imprimir indicaciones de control en la parte inferior
		gotoxy(1, 13);
		cout << "Controles: (tu eres 'R')" << endl
			<< "Flecha arriba (para desplazarse hacia arriba)" << endl
			<< "Flecha abajo (para desplazarse hacia abajo)"<< endl
			<< " " << endl	
			<< "PUNTAJE: " << rana.getPuntaje();
		
		rana.manejarEntrada();
		
		// Espera corta para controlar la velocidad de actualización de la pantalla
		esperar(100);
	}
	
	return 0;
}
