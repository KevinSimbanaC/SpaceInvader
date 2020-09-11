#include "diseno.h"
//Funcion que dibuja la portada del principio del juego asi como la animacion de cargando
void PORTADA(BITMAP* p){
    int parpadeo=0;
    int y=0;
    int cont=0;
    short int salida=0;
    short int carga=0;
    while(salida!=1){
            if(parpadeo<25) blit(p,screen,0,y,0,100,600,400);
            else blit(p,screen,600,y,0,100,600,400);

            if(key[KEY_ENTER]){
                y=400;
                carga=1;
            }
            if(carga==1)cont++;
            if(cont>400)salida=1;

            rest(5);
            if(++parpadeo==50) parpadeo=0;
    }

    clear_to_color(screen,0x000000);

}
//Fncion que imprime el fondo del juego
void imprimir_fondo(BITMAP* fondo,BITMAP* buffer){
    masked_blit(fondo,buffer,0,0,0,0,600,600);
}
