/////////////////////////ESTO LO COPIE DE UN EJEMPLO, PUEDE TENER COSITAS/TERMINOLOGIA DISTINTA A LA QUE USAMOS///////////////////////////////////

#include <stdio.h> 
#include <stdlib.h> 
#include <allegro5/allegro.h> // Librería inicial de Allegro 
#include <allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include <math.h> //Para usar trigonometria
#define VENTANA_X 800
#define VENTANA_Y 700


// Variables globales 
ALLEGRO_DISPLAY *dis = NULL;

void recursiva(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float IEnd);

// Funciones 
void inicializar(void)
{
	// Inicializar los addons 
	if (!al_init())
	{
		fprintf(stderr, "Error al inicializar Allegro."); // Imprimir errores en stream STDERR
		exit(-1);
	}
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Error al inicializar el addon de primitivas."); // Imprimir errores en stream STDERR
		exit(-2);
	}

	dis = al_create_display(VENTANA_X, VENTANA_Y); // Crear el display de tamaño 500x300 píxeles

	
}
void finalizar()
{
	al_shutdown_primitives_addon(); // Finalizar el addon de primitivas
	al_destroy_display(dis); // Destruir la ventana 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int main(void)
{
	inicializar();

	
	/////////////Datos Hardcodeados para probar//////////////
	float IStart = 400;
	float IEnd = 1;
	float lado_base = IStart;
	float lado_izquierdo;
	float lado_derecho;
	float angulo_D = 60;
	float angulo_I = 60;
	float angulo_S;

	float Ix = 200;
	float Iy = 400;

	float Dx;
	float Dy;

	float Sx;
	float Sy;

	float CentroX;
	float CentroY;

	/////////////////////////////////////////////////////////

	/*Cada vez que se utilice una función trigonométrica, al ángulo se lo dividirá por 57,3 para expresarlo en radianes, ya que la librería math.h
	sólo acepta los ángulos en radianes.*/

	angulo_S = 180 - angulo_D - angulo_I;	//La suma de los ángulos internos de un triángulo da 180°

	lado_izquierdo = (lado_base / sin(angulo_S/ 57.3)) * sin(angulo_D / 57.3);	// En un triángulo, la "Regla de los Senos" dice que:
																				//(lado1/sen(ángulo1)) = (lado2/sen(ángulo2)) = (lado3/sen(ángulo3))
	lado_derecho = (lado_base / sin(angulo_S / 57.3)) * sin(angulo_I / 57.3);	//https://www.mathsisfun.com/algebra/trig-sine-law.html
																				//Advertencia: no malinterpretar el nombre de la regla al traducirla al español

	Dx = Ix + lado_base;
	Dy = Iy;	//Por interpretación de consigna, la base siempre será horizontal, por lo que las coordenada "Y" serán iguales.

	Sx = Ix + cos(angulo_I / 57.3) * lado_izquierdo;	//Consideramos que la base que es dada como dato debería ser la parte inferior del triángulo (para
	Sy = Iy - sin(angulo_I / 57.3) * lado_izquierdo;	//que se viera igual que el triángulo del ejemplo de la consigna). Debido a esto, se suma el coseno
														//y se resta el seno.
														
		CentroX = (Ix + Dx + Sx) / 3;
		CentroY = (Iy + Dy + Sy) / 3;


	al_draw_line(Ix, Iy, Dx, Dy, al_map_rgba(0, 255, 255, 255), 1);			//Dibujo el triángulo inicial
	al_draw_line(Ix, Iy, Sx, Sy, al_map_rgba(255, 0, 0, 50), 1);
	al_draw_line(Dx, Dy, Sx, Sy, al_map_rgba(255, 255, 255, 255), 1);
	

	al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer


	recursiva(Ix, Iy, Sx, Sy, CentroX, CentroY, IEnd);
	recursiva(Dx, Dy, Sx, Sy, CentroX, CentroY, IEnd);
	recursiva(Ix, Iy, Dx, Dy, CentroX, CentroY, IEnd);


	getchar();
	finalizar();

	return 0;
}


void recursiva(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float IEnd)
{
	int caso_base = 0;
	int rojo = rand() % 256;
	int verde = rand() % 256;
	int azul = rand() % 256;

	float Nuevo_CentroX;
	float Nuevo_CentroY;

if ((sqrt(pow(Bx - Ax, 2) + pow(By - Ay, 2)) < IEnd) || (sqrt(pow(Cx - Ax, 2) + pow(Cy - Ay, 2)) < IEnd) || (sqrt(pow(Bx - Cx, 2) + pow(By - Cy, 2)) < IEnd))
	//Condición para la recursiva, que ningun lado sea menor al dato IEnd
	{
		caso_base = 1;
	}

	if (!caso_base)
	{
		al_draw_line(Ax, Ay, Bx, By, al_map_rgba(rojo, verde, azul, 255), 1);
		al_draw_line(Ax, Ay, Cx, Cy, al_map_rgba(rojo, verde, azul, 255), 1);
		al_draw_line(Bx, By, Cx, Cy, al_map_rgba(rojo, verde, azul, 255), 1);
		al_flip_display();

		Nuevo_CentroX = (Ix + Dx + Sx) / 3;
		Nuevo_CentroY = (Iy + Dy + Sy) / 3;

		recursiva(Ax, Ay, Cx, Cy, Nuevo_CentroX, Nuevo_CentroY, IEnd);
		recursiva(Bx, By, Cx, Cy, Nuevo_CentroX, Nuevo_CentroY, IEnd);
		recursiva(Ax, Ay, Bx, By, Nuevo_CentroX, Nuevo_CentroY, IEnd);
	}

	
}


