#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO

#define X_MAX	600.0
#define Y_MAX	600.0
#define N_MAX   255
#define X_PASO  ((2 - (-2))/X_MAX)      // EN LUGAR DE 2 Y -2 IRIAN LOS argv[]
#define Y_PASO  ((2 - (-2))/Y_MAX)
#define RADIO   2                       // NO SE EL RADIO CUAL SERIA

int get_num_it(double complex z, double complex z0, int *cont);


int main(void)      //void mandelbrot(double -2, double 2, double -2, double 2)
{
    
    
    
    /*********************** INICIALISO TODO***************************/
    
    
    
    
   ALLEGRO_DISPLAY *display = NULL; 
   if(!al_init()) 
   {
          fprintf(stderr, "failed to initialize allegro!\n");
          return -1;
   }
 
   if(!al_init_primitives_addon())
   {
	  fprintf(stderr, "failed to initialize primitives!\n");
	  return -1;
   }
   
   display = al_create_display(X_MAX, Y_MAX);
 
   if(!display) 
   {
	  al_shutdown_primitives_addon();
	  fprintf(stderr, "failed to create display!\n");
      return -1;
   }
   
   
   /**********************TODO INICIADO*****************************/
   
   
   al_clear_to_color(al_color_name("black"));
   al_flip_display();
   
   int cont = 0;
   double Xo = -2.0;
   double Xf = 2.0;
   double Yo = -2.0;
   double Yf = 2.0;
   int i, j, n;
   
   double complex Zo = Xo + Yo*I;   //coordenada de origen en el plano complejo
   
   for (i = 0; i < X_MAX; i++)
   {
       for (j = 0; j < Y_MAX; j++)
       {
           //printf("Z = %f + %f*i\n",creal(Zo + i*X_PASO + j*Y_PASO*I), cimag(Zo + i*X_PASO + j*Y_PASO*I));
           n = get_num_it(Zo + i*X_PASO + j*Y_PASO*I, Zo + i*X_PASO + j*Y_PASO*I, &cont);
           cont = 0;
           al_draw_filled_rectangle(i, j, i+1, j+1, al_map_rgb(0,0,N_MAX - n));
           if(n>5)
           printf("n = %d\n",n);
       }
   }
   al_flip_display();
   al_rest(5.0);
   
   al_destroy_display(display);
   al_shutdown_primitives_addon();
    
    return (EXIT_SUCCESS);
}

int get_num_it(double complex z, double complex z0, int *cont)
{
    if (sqrt(creal(z)*creal(z) + cimag(z)*cimag(z)) >= RADIO) // CASO BASE
    {
        return 0;
        
    }
    else if (*cont == 255)
    {
        return 0;   //para sacar todo lo que estuvimos acumulando por las iteraciones
    }
    else                // CASO RECURSIVO
    {
        z = z*z + z0;
        (*cont)++;
        return 1 + get_num_it(z, z0, cont);
    }
}
