#include<allegro.h>
#ifndef _PERSONAJES_H
#define  _PERSONAJES_H

struct NAVE{
    int x,y;            //Coordenadas
    int n_disp;         //cantidad de disparos dentro del juego
    int max_disp;       //disparos permitidos
    int max_disp_ene;   //disparos permitidos enemigo
    int tick;           //controla el tiempo de la nave
    int ancho_b,alto_b; //dimensiones de la imagen de la bala
    int ancho_p,alto_p; // dimensiones de la imagen del personaje
    int dir_bala;       //hacia donde va la bala
    int tipo;           //para determinar el tipo de jugador dentro del juego
    int vida;           //vida del personaje
    //Declaracion de las variables graficas y sonido de la libreria Allegro
    BITMAP* img_nav;
    BITMAP* img_bala;
    BITMAP* exp_enem;
    SAMPLE* disparo;
    SAMPLE* explo;
};
struct Balas{
    int x , y;      //Coordenadas de las balas
    int dx , dy;    //Variables temporables de las balas(controla sus desplazamientos)

};
struct escudo{
    int x,y;   //Posiciones de los escudos
    int dan;   //Variable daño de cada parte del escudo
    int tipo; //para pintar la imagen
};

typedef struct Balas Balas;
typedef struct NAVE NAVE;
typedef struct escudo escudo;

void inicia(NAVE *N,char* ruta_nave, char*ruta_bala,int _ancho_b,int _alto_b,
            int _ancho_p,int _alto_p,int _x,int _y,int _dir_bala,int _tipo,int _vida,char *m_disp,char *m_exp);
void pinta(NAVE N,BITMAP* buffer,int ix,int iy);
void mueve(NAVE *N);
int temporizador(int *tick,int tiempo);
void dispara(NAVE *N,Balas disparos[],BITMAP* buffer);
void acomoda_enemigos(NAVE E[]);
void pintar_enemigo(NAVE E[],BITMAP* buffer,int mov);
void explosion1(NAVE E,BITMAP* buffer);
void explosion2(NAVE N,BITMAP*buffer,BITMAP* fondo);
void iniciar_escudo(escudo muros[]);
void pintar_escudos(escudo ES[],BITMAP* img_mur,BITMAP* buffer);
void crear_bala_enemigo(NAVE E[],int *azar);
void crear_bala_nave(NAVE *N,Balas disparos[]);
short int limites(NAVE E[],int *dir);
void mover_enemigos(NAVE E[],int *mov, int *dir);
void dibujar_vidas(NAVE N,BITMAP* buffer);
#endif // PERSONAJES_H_INCLUDED
