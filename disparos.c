#include <allegro.h>
#include "disparos.h"
//***Permite saber cuando una bala colisiona con un enemigo o el jugador
//de acuerdo a las coordenadas de posicion de las Naves y balas, y asi como su alto y ancho de imagen***
short int colision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
    if((x1<x2+w2)&&(x2<x1+w1)&&(y1<y2+h2)&&(y2<y1+h1)){
            return 1;//true
    }
    return 0;//false
}
//**logica de los disparos**
short int crear_bala(int *n_disparos, const int max_disparos ,Balas disparos[] ,int X, int Y , const int dy){
    if( *n_disparos < max_disparos-1){ // n -1 disparos permitidos
       *n_disparos=*n_disparos+1;
       disparos[*n_disparos].x  = X+11;
       disparos[*n_disparos].y  = Y;
       disparos[*n_disparos].dx = 0;
       disparos[*n_disparos].dy = dy;
       return 1;
   }
   return 0;
}
//**Pinta las balas de acuerdo a sus coordenadas(cada bala es una estuctura que tiene sus propias coordenadas)**
void pintar_bala(int *n_disparos, const int max_disparos,Balas disparos[],BITMAP* buffer, BITMAP* bala,int ancho,int alto){
     int cont;
     if ( *n_disparos > 0 && *n_disparos < max_disparos){
            for ( cont = 1; cont <= *n_disparos; cont++){
                       disparos[cont].x += disparos[cont].dx;
                       disparos[cont].y += disparos[cont].dy;
                       masked_blit( bala, buffer, 0, 0, disparos[cont].x, disparos[cont].y, ancho, alto);
            }
     }
}
//**Para poder eliminar las balas en juego y poder repetirlas**
void eliminar(Balas disparos[],int *n_disparos,int cont){
        Balas Btemp;
        Btemp = disparos[cont];
        disparos[cont] = disparos[*n_disparos];
        disparos[*n_disparos] = Btemp;
        *n_disparos=*n_disparos-1;
        if ( *n_disparos < 0 ) *n_disparos=0;
}
//**Permite eliminar la bala cuando llega a los limites**
void elimina_bala(int *n_disparos, const int max_disparos,Balas disparos[],const int ANCHO, const int ALTO){
      int cont;
      if ( *n_disparos > 0 && *n_disparos < max_disparos){
            for ( cont = 1; cont <= *n_disparos; cont++){
                  if ( disparos[cont].y > ALTO || disparos[cont].y < 0 ||
                       disparos[cont].x > ANCHO|| disparos[cont].x < 0  )
                    {
                        eliminar(disparos,n_disparos,cont);
                    }
            }
      }
}
//**Elimina la bala cuando choca con el enemigo o jugador**
short int elimina_bala_objeto(NAVE *N,NAVE *E,Balas B[]){
     int cont;
     if ( N->n_disp > 0 && N->n_disp < N->max_disp){
            for ( cont = 1; cont <= N->n_disp; cont++){
                   if(colision(E->x,E->y,E->ancho_p,E->alto_p,
                    B[cont].x,B[cont].y,N->ancho_b,N->alto_b)==1 && E->vida>0){
                        eliminar(B,&(N->n_disp),cont);
                        E->vida--;
                        return 1;//true
                    }
            }
    }
    return 0;//false
}
//**Elimina la bala cuando choca con los escudos y aumenta el daño del escudo**
void eliminar_bala_escudo(NAVE *N,escudo ES[],Balas B[]){
     int cont,i;
        if ( N->n_disp > 0 && N->n_disp < N->max_disp){
            for ( cont = 1; cont <= N->n_disp; cont++){
                for(i=0;i<20;i++){
                    if(colision(ES[i].x,ES[i].y,20,16,B[cont].x,B[cont].y,N->ancho_b,N->alto_b) && ES[i].dan<3)
                       {
                        eliminar(B,&(N->n_disp),cont);
                        ES[i].dan++;
                       }
                }
            }
        }
}
