#include <allegro.h>
#include <stdlib.h>     //Para poder generar numeros aleatorios (srand;rand)
#include <time.h>       //Para poder usar la funcion time()
//Biblitecas creadas que tienen todas las funciones del juego("Modularidad")
#include "inicia.h"     //libreria con funcion que inicia allegro
#include "disparos.h"   //libreria con funciones de la logica de disparos
#include "personajes.h" //libreria con funciones de los personajes
#include "diseno.h"     //libreria con funciones del menu

#define ANCHO 600
#define ALTO  600

int main(){
    srand(time(NULL));//Genere numeros al azar
    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);

    // Inicia las imagenes y sonido del juego(libreria Allegro)
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP *portada=load_bitmap("Recursos/portada.bmp",NULL);
    BITMAP *fondo=load_bitmap("Recursos/fondo.bmp",NULL);
    BITMAP *img_muros=load_bitmap("Recursos/escudos.bmp",NULL);
    BITMAP *fin_juego = load_bitmap("Recursos/GameOver.bmp",NULL);
    BITMAP *fin_juegogana = load_bitmap("Recursos/finjuegogana.bmp",NULL);
    MIDI* musica_fondo=load_midi("Recursos/arena.mid");
    //Estructuras del juego
    NAVE N;        //Nave Jugador
    NAVE E[60];    //Nave Enemigo
    escudo ES[30]; //Escudos

    int azar=rand()%55; //para elegir el enemigo que va a disparar
    int mov=0;          //controla la animacion de los enemigos
    int i,j;            //contadores
    int lim=0;          //para detener el juego cuando los enemigos lleguen al final
    int dir=-5;         //para controlar el movimiento de los enemigos(pasos que dan)
    int vel_juego=12;
    int n_enemigos=55;

    inicia(&N,"Recursos/nave.bmp","Recursos/Bala2.bmp",6,12,30,20,ANCHO/2,ALTO-70,-8,0,3,"Recursos/0.wav","Recursos/explosion.wav");//Inicia la Nave
    Balas disparos[N.max_disp];         //Para las balas del jugador
    acomoda_enemigos(E);                //Inicia a los enemigos(posicion y parametros)
    Balas disp_E[E[0].max_disp_ene];    //Para las balas del enemigo
    iniciar_escudo(ES);                 //Inicia el escudo(posicion y paramtros)

    play_midi(musica_fondo,1);          //sonido de fondo del juego

    PORTADA(portada);                   //Inicia la portada del juego

    while((!key[KEY_ESC] && n_enemigos!=0) && N.vida>0 && lim==0){

            clear_to_color(buffer,0x000000);        //Borra el mapa de bits por el color especificado(negro)

            pintar_escudos(ES,img_muros,buffer);    //Pinta los Escudos

            if(temporizador(&E[0].tick,vel_juego)==1){  //Controla el mov. de los enemigos
                    mover_enemigos(E,&mov,&dir);
            }
            if(temporizador(&E[1].tick,300)==1){        //Controla la velocidad de los enemigos pasado un tiempo
                if(vel_juego>2)vel_juego-=1;
                if(dir<0){dir+=-1;}
                else{dir+=1;}
           }
            //Para la nave del jugador
            pinta(N,buffer,0,0);
            mueve(&N);
            crear_bala_nave(&N,disparos);
            dispara(&N,disparos,buffer);
            //Para elminar la bala y la nave enemiga cuando esta sea impactada
            for(i=0;i<55;i++){
                if(elimina_bala_objeto(&N,&E[i],disparos)==1){
                        n_enemigos--;
                        explosion1(E[i],buffer);
                }
            }
            //Para detectar a los enemigos cuando lleguen al final y detener el juego
            for(j=0;j<55;j++){
                if(E[j].y ==ALTO-70)lim=1;break;
            }

            eliminar_bala_escudo(&N,ES,disparos);        //elimina parte del escudo cuando esta sea disparada por el jugador
            pintar_enemigo(E,buffer,mov);                //se encarga de pintar al enemigo
            crear_bala_enemigo(E,&azar);                 //controla que enemigo dispara
            dispara(&E[azar],disp_E,buffer);             //genera los disparos para las naves enemigos

            if(elimina_bala_objeto(&E[azar],&N,disp_E)==1){ //Detecta cuando la nave recibe un disparo
                explosion2(N,buffer,fondo);
            }
            imprimir_fondo(fondo,buffer);               //Pinta el fondo
            eliminar_bala_escudo(&E[azar],ES,disp_E);   //elimina parte del escudo cuando esta sea disparada por el enemigo
            dibujar_vidas(N,buffer);                    //Pinta las vidas
            blit(buffer,screen, 0,0 , 0,0 ,ANCHO,ALTO); //Pinta el buffer sobre pantalla de nuevo

            rest(22);     //delay del bucle
    }
    stop_midi();          //Para la musica
    //imagenes del final del juego
    while(!key[KEY_ENTER] && !key[KEY_ESC] && !key[KEY_R] ){
        if (N.vida==0 || lim==1)blit(fin_juego,screen,0,0,0,0,600,600);
        if(n_enemigos==0)blit(fin_juegogana,screen,0,0,0,0,600,600);
    }

    return 0;
}
END_OF_MAIN();

