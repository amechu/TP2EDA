/*#include <stdio.h>
#include <complex>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO


#define X_MAX	600.0
#define Y_MAX	600.0
#define N_MAX   255.0
#define X_PASO  ((2 - (-2))/X_MAX)      // EN LUGAR DE 2 Y -2 IRIAN LOS argv[]
#define Y_PASO  ((2 - (-2))/Y_MAX)
#define RADIO   2                       // QUE EL RADIO SE MODIFIQUE SEGUN LOS argv[]

int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont);


int main(void)      //void mandelbrot(double -2, double 2, double -2, double 2)
{
   
   int cont = 0;
   double Xo = -2.0;    //LES ASIGNAMOS LOS VALORES POR LINEA DE COMANDO, OSEA QUE HAY QUE MODIFICAR ESTO
   double Xf = 2.0;
   double Yo = -2.0;
   double Yf = 2.0;
   int i, j, n;
   
   std::complex <double> Zo = (Xo, Yo);   //coordenada de origen en el plano complejo
   
   for (i = 0; i < X_MAX; i++)
   {
       for (j = 0; j < Y_MAX; j++)
       {
           n = get_num_it(Zo + i*X_PASO + j*Y_PASO*I, Zo + (i*X_PASO, j*Y_PASO), &cont);
           cont = 0;
           if(n == N_MAX)     //diverge -> negro
               al_draw_filled_rectangle(i, j, i+1, j+1, al_map_rgb(0,0,(int)(N_MAX*pow((N_MAX - n)/N_MAX,2))));   //hacemos un juego con valores exponenciales (no lineales) para generar un mejor efecto visual
           else
               al_draw_filled_rectangle(i, j, i+1, j+1, al_map_rgb((int)(N_MAX-N_MAX*pow((N_MAX - n)/N_MAX,6)),((int)(N_MAX-N_MAX*pow((N_MAX - n)/N_MAX,6))),(int)(N_MAX*pow((N_MAX - n)/N_MAX,2))));
           
       }
   }
   al_flip_display();
   al_rest(10.0);
    
    return (EXIT_SUCCESS);
}

int get_num_it(std::complex <double> z, std::complex <double> z0, int *cont)
{
    if (std::norm(z) >= RADIO || *cont == N_MAX) // CASO BASE
    {
        return 0;
    }

    else                // CASO RECURSIVO
    {
        z = z*z + z0;
        (*cont)++;	//contador de iteraciones
        return 1 + get_num_it(z, z0, cont);
    }
}

*/