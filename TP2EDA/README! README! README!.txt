Diseñador de fractales elaborado por Guido Panaggio, Agustin Hrubisiuk y Alan Mechoulam.
1er Cuatri, Estructura de Datos y Algoritmos, 2018.

El programa posee tres fractales distintos, triangulos de centro de masa uniforme, poligonos con centro en cada vertice
del anterior y finalmente el famoso mandelbrot.

OPCIONES:

Al programa se lo puede ejecutar por lineas de comandos con las siguientes opciones/parametros:

******IMPORTANTE**************************************************************************************
 Si no se elige tipo de fractal, pero si otras opciones, se dibujara el fractal
default de todas maneras. Si se elige tipo pero no se da opciones, para cada fractal se dibujara un
default distinto.
******************************************************************************************************

-type (DEFAULT = POLIGONO 6 LADOS): Fractal a dibujar.
	POLIGONO
	UNIFORME
	MANDELBROT
-lstart: Largo del primer lado del fractal. Solo para uniforme o poligono.
	(0-100], mas grande que lend.
-lend: Largo del ultimo lado del fractal. Solo para uniforme o poligono.
	(0-100), mas chico que lstart.
-lconstant: Constante por la cual se multiplica a lstart para achicarlo. Solo para poligono.
	(0-1)
-leftangle: Angulo izquierdo del primer triangulo. Solo para uniforme.
	(0-90]
-rightangle: Angulo derecho del primer triangulo. Solo para uniforme.
	(0-90]
-n: Cantidad de lados del poligono. Solo para poligono.
	[3-25]
-xo -xf -yo -yf: Ubicacion del set de mandelbrot. Solo para mandelbrot.
	(-inf-inf)

noaudio: con este parametro se podra optar por una experiencia insonora.


******************ATENCION********************
Se recomienda elegir un lstart no mayor a 50 a partir de los 12 lados.
Para UNIFORME, el lstart no se considera como valor en pixeles, sino que esta multiplicado por 4 por razones esteticas.
Los angulos de UNIFORME van de 0 a 90 para ambos casos, asi se interpreto la consigna ya que en un lado dice que van de
-90 a 90 y en otro de 0 a 90.