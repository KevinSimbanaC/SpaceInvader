#include <allegro.h>
#include "personajes.h"

#ifndef _DISPAROS_H
#define  _DISPAROS_H

short int colision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);
short int crear_bala(int *n_disparos, const int max_disparos,Balas disparos[], int X, int Y ,const int dy);
void pintar_bala(int *n_disparos, const int max_disparos,Balas disparos[],BITMAP* buffer, BITMAP* bala, int ancho, int alto);
void eliminar(Balas disparos[],int *n_disparos,int cont);
void elimina_bala(int *n_disparos, const int max_disparos,Balas disparos[],const int ANCHO, const int ALTO);
short int elimina_bala_objeto(NAVE *N,NAVE *E,Balas B[]);
void eliminar_bala_escudo(NAVE *N,escudo ES[],Balas B[]);

#endif
