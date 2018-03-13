#include "allegro.h"
#include "gen.h"

void generatePolygons(parseData* myData, float xo, float yo, float length, int red, int green, int blue, int thickness)
{

	
	float vert[MAX_VERT] = { 0 };

	if (length < myData->programSettings.lEnd)
	{
		return; //Caso base
	}

	else //Caso recursivo
	{
		calculateVertices(myData, vert, xo, yo, length);
		
		al_draw_polygon(vert, myData->programSettings.n, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(red, green, blue), thickness, 1); //Dibuja nuevo poligono

		//Achico lado
		length = (length*(myData->programSettings.lConstant));

		//Los colores dependen de que tan alejado del centro de la pantalla se halle el centro del triangulo
		if (green >= 168)
			green += (sqrt(pow(xo - SCREENWIDTH / 2, 2) + pow(yo - SCREENHEIGHT / 2, 2)))/3;
		if(red <= 168)
			red -= (sqrt(pow(xo - SCREENWIDTH / 2, 2) + pow(yo - SCREENHEIGHT / 2, 2)))/3;

		//Se achica el espesor
		if (thickness > 0)
			thickness -= 1;

		//Se llama a la funcion recursiva N veces
		for (int i = 0; i < myData->programSettings.n; i++)
		{
			generatePolygons(myData, vert[2*i], vert[2*i+1], length, red, green, blue, thickness); //Calcula la proxima generacion
		}
	}

	al_flip_display();
	
	//Mas iteraciones tienen menos delay
	al_rest(myData->programSettings.lEnd * myData->programSettings.lConstant * 0.001);

	return;
}

void calculateVertices(parseData* myData, float vert[MAX_VERT], float xo, float yo, float length)
{
	//Se calcula primero el radio de la circunferencia que pasa por todos los vertices del poligono
	float r = (length) / (2 * (sin(M_PI / myData->programSettings.n)));
	//Luego se calcula el angulo entre dos vertices
	float alpha = (2 * M_PI / myData->programSettings.n);

	for (int i = 0, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		//Por cada vertice, se rota a partir del centro de masa en funcion del angulo calculado anteriormente
		vert[i] = xo + (r)* cos(alpha * h);
		h++;
	}

	for (int i = 1, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		//Idem para coordinadas en Y
		vert[i] = yo + (r)* sin(alpha*h);
		h++;
	}
}

void generateUniforme(parseData* myData, float Ax, float Ay, float Bx, float By, float Cx, float Cy, int red, int green, int blue, int thickness, int rec_count)
{
	float vert[TRIANGLE_COORDS] = { Ax,Ay,Bx,By,Cx,Cy }; //Coordenadas de los vertices del triangulo
	float end = myData->programSettings.lEnd * SIZE_ADJUST; //Por razones esteticas, lstart y lend no son su valor
															//real en pixeles, sino multiplicados por una constante
	float centerX = (Ax + Bx + Cx) / 3;	//Se calculan los
	float centerY = (Ay + By + Cy) / 3;	//centros de masa del triangulo
	
	if((sqrt(pow(Cx - centerX, 2) + pow(Cy - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - centerX, 2) + pow(By - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Ax - centerX, 2) + pow(Ay - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - Ax, 2) + pow(By - Ay, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Cx - Ax, 2) + pow(Cy - Ay, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - Cx, 2) + pow(By - Cy, 2)) < myData->programSettings.lEnd))
		return; //Se fija en la condicion base
	
	else
	{
		//Achica el espesor
		if (thickness > 0)
			thickness -= 1;

		//Colores
		if (green < 150)
			green += 30;
		if (green >= 150)
			red -= 30;
		blue += 5;
		
		//Se dibuja el triangulo
		al_draw_polygon(vert, TRIANGLE_COORDS / 2, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(red, green, blue), thickness, 2);
		
		al_flip_display();
		al_rest(0.03); 

		//Se llama a la funcion recursiva
		generateUniforme(myData, Ax, Ay, Bx, By, centerX, centerY, red, green, blue, thickness, rec_count);
		generateUniforme(myData, Cx, Cy, Ax, Ay, centerX, centerY, red, green, blue, thickness, rec_count);
		generateUniforme(myData, Bx, By, Cx, Cy, centerX, centerY, red, green, blue, thickness, rec_count);

		al_flip_display();
	}
}

void centerTriangle(parseData* parseData, float vert[MAX_VERT])
{
	//Esta funcion se utiliza para que todo triangulo pedido por usuario siempre
	//se encuentre alineado su centro de masa con el centro de la pantalla, en vez de elegir un vertice
	//fijo en algun punto central de la pantalla por el cual siempre se comienza.
	//
	//Cabe destacar que los triangulos estan corridos levemente hacia
	//abajo por una constante DOWNOFFSET por razones esteticas.

	const float angleConvert = M_PI / 180;	//Para operar en radianes

	//Se elije un vertice por el cual comenzar a dibujar en el (0,0) para una vez computado el triangulo
	//poder realizarle un corrimiento a todos sus vertices, tanto como su centro de masa este alejado del centro
	//de la pantalla.

	float Ax = 0;
	float Ay = 0;

	//Se calcula el angulo superior
	float gamma = M_PI - parseData->programSettings.leftAngle * angleConvert - parseData->programSettings.rightAngle * angleConvert;

	//Se calcula el lado izquierdo
	float lIzq = parseData->programSettings.lStart*SIZE_ADJUST / sin(gamma) * sin(parseData->programSettings.rightAngle * angleConvert);

	//Luego, considerando por consigna que el lado base siempre debe estar horizontal
	//Se calcula el segundo vertice del lado base.
	float Bx = parseData->programSettings.lStart*SIZE_ADJUST;
	float By = 0;

	//Se calcula el tercer vertice del triangulo
	float Cx = cos(parseData->programSettings.leftAngle * angleConvert) * lIzq;
	float Cy = -(sin(parseData->programSettings.leftAngle * angleConvert)) * lIzq;

	//Finalmente, se calcula el centro de masa del triangulo
	float centerX = (Ax + Bx + Cx) / 3;
	float centerY = (Ay + By + Cy) / 3;

	//A este centro de masa se lo corre tanto alejado del centro de pantalla este
	//No quedara centrado, sino un poco mas abajo por razones esteticas
	centerX = SCREENWIDTH / 2 - centerX;
	centerY = SCREENHEIGHT / 2 + DOWNOFFSET - centerY;

	//Finalmente, a cada vertice del triangulo se le realiza un corrimiento tanto el centro de masa
	//del mismo triangulo alejado del centro de pantalla este.
	vert[0] = Ax + centerX;
	vert[1] = Ay + centerY;
	vert[2] = Bx + centerX;
	vert[3] = By + centerY;
	vert[4] = Cx + centerX;
	vert[5] = Cy + centerY;


}

void generateMandelbrot(parseData* myData)
{

	int cont = 0, n;
	const float stepX = (myData->programSettings.xf - myData->programSettings.xo) / (SCREENWIDTH - 200); //-200 porque la pantalla no es cuadrada
	const float stepY = (myData->programSettings.yf - myData->programSettings.yo) / (SCREENHEIGHT);
	float radio;

	//Se utilizo la libreria estandar <complex> de C++
	std::complex <double> Zo = std::complex <double>(myData->programSettings.xo, myData->programSettings.yo);   //coordenada de origen en el plano complejo

	//Se calcula el radio de nuestro plano imaginario
	if (abs(myData->programSettings.xf) + abs(myData->programSettings.xo) >= abs(myData->programSettings.yf) + abs(myData->programSettings.yo))
		radio = (abs(myData->programSettings.xf) + abs(myData->programSettings.xo)) / 2;
	else
		radio = (abs(myData->programSettings.yf) + abs(myData->programSettings.yo)) / 2;

	//Para estar en sincronia con la musica
	al_rest(0.5);

	//Se itera una vez por cada pixel en la pantalla
	for (int i = 0; i < SCREENWIDTH; i++)
	{
		for (int j = 0; j < SCREENHEIGHT; j++)
		{
			//Se llama a la funcion recursiva, la cual devuelve la profundidad
			//Esta recibe en la primera llamada excepcionalmente exactamente dos veces el mismo parametro
			n = get_num_it(Zo + std::complex<double>((i)*stepX, j*stepY), Zo + std::complex<double>(i*stepX, j*stepY), &cont, radio);
			cont = 0;
			if (n == N_MAX)     //Diverge -> negro
			{
				al_draw_pixel(i, j, al_map_rgb(0, 0, (int)(N_MAX*pow((N_MAX - n) / N_MAX, 2))));   //Hacemos un juego con valores exponenciales (no lineales) para generar un mejor efecto visual
				al_rest(0.0001);
			}
			else
				al_draw_pixel(i, j, al_map_rgb((int)(N_MAX - N_MAX * pow((N_MAX - n) / N_MAX, 10)), ((int)(N_MAX - N_MAX * pow((N_MAX - n) / N_MAX, 10))), (int)(N_MAX*pow((N_MAX - n) / N_MAX, 10))));
		}

	al_flip_display();
	al_rest(0.008);
	}
}

int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont, float radio)
{
	if (std::abs(z) >= radio || *cont == N_MAX) // CASO BASE
	{
		return 0;
	}

	else                // CASO RECURSIVO
	{
		z = z * z + z0;
		(*cont)++;	//contador de iteraciones
		return 1 + get_num_it(z, z0, cont, radio);
	}
}