#include "allegro.h"
#include "gen.h"


void drawPolygon(parseData* myData, float vert[MAX_VERT], int red, int green, int blue, int thickness)
{
		al_draw_polygon(vert, myData->programSettings.n, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(red, green, blue), thickness, 1);
		return;
}

void calculateVertices(parseData* myData, float vert[MAX_VERT], float xo, float yo, float length)
{
	float r = (length) / (2 * (sin(M_PI / myData->programSettings.n)));
	float alpha = (2 * M_PI / myData->programSettings.n);

	for (int i = 0, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		vert[i] = xo + (r) * cos(alpha * h);
		h++;
	}

	for (int i = 1, h = 1; i < 2 * myData->programSettings.n; i += 2)
	{
		vert[i] = yo + (r) * sin(alpha*h);
		h++;
	}
}

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
		drawPolygon(myData, vert, red, green, blue, thickness); //Dibuja nuevo poligono

		//Achico lado
		length = (length*(myData->programSettings.lConstant));
		green -= 30;
		red += 35;
		blue -= 30;
		if (thickness > 0)
			thickness -= 1;
		for (int i = 0; i < myData->programSettings.n; i++)
		{
			generatePolygons(myData, vert[2*i], vert[2*i+1], length, red, green, blue, thickness); //Calcula la proxima generacion
		}
	}

	al_flip_display();
	al_rest(myData->programSettings.lEnd * myData->programSettings.lConstant * 0.001);

	return;
}

void generateUniforme(parseData* myData, float Ax, float Ay, float Bx, float By, float Cx, float Cy, int red, int green, int blue, int thickness, int rec_count)
{
	float vert[TRIANGLE_COORDS] = { Ax,Ay,Bx,By,Cx,Cy };
	float end = myData->programSettings.lEnd * SIZE_ADJUST;
	float centerX = (Ax + Bx + Cx) / 3;
	float centerY = (Ay + By + Cy) / 3;
	
	if((sqrt(pow(Cx - centerX, 2) + pow(Cy - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - centerX, 2) + pow(By - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Ax - centerX, 2) + pow(Ay - centerY, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - Ax, 2) + pow(By - Ay, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Cx - Ax, 2) + pow(Cy - Ay, 2)) < myData->programSettings.lEnd) || (sqrt(pow(Bx - Cx, 2) + pow(By - Cy, 2)) < myData->programSettings.lEnd))
		return;
	else
	{
		if (thickness > 0)
			thickness -= 1;
		rec_count++;

		if (green < 150)
			green += 30;
		if (green >= 150)
			red -= 30;
		blue += 5;

		al_draw_polygon(vert, TRIANGLE_COORDS / 2, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(red, green, blue), thickness, 2);
		
		al_flip_display();
		al_rest(0.03); 

		generateUniforme(myData, Ax, Ay, Bx, By, centerX, centerY, red, green, blue, thickness, rec_count);
		generateUniforme(myData, Cx, Cy, Ax, Ay, centerX, centerY, red, green, blue, thickness, rec_count);
		generateUniforme(myData, Bx, By, Cx, Cy, centerX, centerY, red, green, blue, thickness, rec_count);

		al_flip_display();
	}
}

void centerTriangle(parseData* parseData, float vert[MAX_VERT])
{
	const float angleConvert = M_PI / 180;
	float Ax = 0;
	float Ay = 0;

	float gamma = M_PI - parseData->programSettings.leftAngle * angleConvert - parseData->programSettings.rightAngle * angleConvert;

	float lIzq = parseData->programSettings.lStart*SIZE_ADJUST / sin(gamma) * sin(parseData->programSettings.rightAngle * angleConvert);

	float Bx = parseData->programSettings.lStart*SIZE_ADJUST;
	float By = 0;

	float Cx = cos(parseData->programSettings.leftAngle * angleConvert) * lIzq;
	float Cy = -(sin(parseData->programSettings.leftAngle * angleConvert)) * lIzq;

	float centerX = (Ax + Bx + Cx) / 3;
	float centerY = (Ay + By + Cy) / 3;

	centerX = SCREENWIDTH / 2 - centerX;
	centerY = SCREENHEIGHT / 2 + DOWNOFFSET - centerY; //No quedara centrado, sino un poco mas abajo por razones esteticas

	vert[0] = Ax + centerX;
	vert[1] = Ay + centerY;
	vert[2] = Bx + centerX;
	vert[3] = By + centerY;
	vert[4] = Cx + centerX;
	vert[5] = Cy + centerY;


}

void generateMandelbrot(parseData* myData)
{

	int cont = 0;
	double Xo = -1.0;    //LES ASIGNAMOS LOS VALORES POR LINEA DE COMANDO, OSEA QUE HAY QUE MODIFICAR ESTO
	double Xf = 1.0;
	double Yo = -1.0;
	double Yf = 1.0;
	int i, j, n;

	std::complex <double> Zo = std::complex <double>(Xo, Yo);   //coordenada de origen en el plano complejo

	for (i = 0; i < X_MAX; i++)
	{
		for (j = 0; j < Y_MAX; j++)
		{
			n = get_num_it(Zo + std::complex<double>(i*X_PASO, j*Y_PASO), Zo + std::complex<double>(i*X_PASO, j*Y_PASO), &cont);
			cont = 0;
			if (n == N_MAX)     //diverge -> negro
				al_draw_filled_rectangle(i, j, (i + 1), (j + 1), al_map_rgb(0, 0, (int)(N_MAX*pow((N_MAX - n) / N_MAX, 2))));   //hacemos un juego con valores exponenciales (no lineales) para generar un mejor efecto visual
			else
				al_draw_filled_rectangle(i, j, (i + 1), (j + 1), al_map_rgb((int)(N_MAX - N_MAX * pow((N_MAX - n) / N_MAX, 10)), ((int)(N_MAX - N_MAX * pow((N_MAX - n) / N_MAX, 6))), (int)(N_MAX*pow((N_MAX - n) / N_MAX, 10))));
			
		}
	}
	al_flip_display();
}

int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont)
{
	if (std::abs(z) >= RADIO || *cont == N_MAX) // CASO BASE
	{
		return 0;
	}

	else                // CASO RECURSIVO
	{
		z = z * z + z0;
		(*cont)++;	//contador de iteraciones
		return 1 + get_num_it(z, z0, cont);
	}
}