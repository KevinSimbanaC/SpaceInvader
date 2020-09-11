#include"personajes.h"
#include"disparos.h"
#include"diseno.h"
#define ANCHO 600
#define ALTO  600

//***Permite Iniciar cada uno de los parametros de la Nave del jugador y de los enemigos***
void inicia(NAVE *N,char* ruta_nave, char*ruta_bala,int _ancho_b,int _alto_b,
            int _ancho_p,int _alto_p,int _x,int _y,int _dir_bala,int _tipo,int _vida,char *m_disp,char *m_exp){
    N->x=_x;
    N->y=_y;
    N->n_disp=0;
    N->max_disp_ene=2;
    N->max_disp=3;
    N->img_nav=load_bitmap(ruta_nave,NULL);
    N->img_bala=load_bitmap(ruta_bala,NULL);
    N->tick=0;
    N->ancho_b=_ancho_b;
    N->alto_b=_alto_b;
    N->ancho_p=_ancho_p;
    N->alto_p=_alto_p;
    N->dir_bala=_dir_bala;
    N->tipo=_tipo;
    N->vida=_vida;
    N->exp_enem=load_bitmap("Recursos/pum_enemigo.bmp",NULL);
    N->disparo=load_wav(m_disp);
    N->explo=load_wav(m_exp);
}
//***Permite pintar a la nave y enemigos de acuerdo a sus coordenadas de posicion***
void pinta(NAVE N,BITMAP* buffer,int ix,int iy){
    masked_blit(N.img_nav,buffer,ix*N.ancho_p,iy*N.alto_p,N.x,N.y,N.ancho_p,N.alto_p);
}
//***Permite mover a la Nave cambiando sus coordenadas
void mueve(NAVE *N){
    if(key[KEY_RIGHT] && N->x!=520) N->x+=5;
    if(key[KEY_LEFT] && N->x!=50) N->x-=5;
}
//***Funcion que actua como un temporizador de tiempo para el movimiento de los enemigos retorna un 1(true) y 0(false)***
int temporizador(int *tick,int tiempo){
    *tick=*tick+1;
    if(*tick==tiempo){
        *tick=0;
        return 1;
    }
    return 0;
}
//***Permite crear la accion de los disparos de la Nave y de los enemigos
//dentro de esta funcion se encuentran otras funciones ubicadas en la libreria creada "disparos" ***
void dispara(NAVE *N,Balas disparos[],BITMAP* buffer){
        if(N->tipo){//Entra a la condicion si es un enemigo
            crear_bala(&N->n_disp,N->max_disp_ene,disparos,N->x,N->y,N->dir_bala);
            pintar_bala(&N->n_disp,N->max_disp_ene,disparos,buffer,N->img_bala,N->ancho_b,N->alto_b);
            elimina_bala(&N->n_disp,N->max_disp_ene,disparos,ANCHO,ALTO);}
        else{   //Entra a la condicion si el que dispara es el jugador
                pintar_bala(&N->n_disp,N->max_disp,disparos,buffer,N->img_bala,N->ancho_b,N->alto_b);
                elimina_bala(&N->n_disp,N->max_disp,disparos,ANCHO,ALTO);
        }
}
//***Permite ubicar a los enemigo dandoles coordenadas a cada uno para luego iniciarlos en la funcion "inicia" ***
void acomoda_enemigos(NAVE E[]){
    int indice=-1;
    int _tipo=0;
    int i,j;
    for(i=0;i<5;i++){
        _tipo++;//tipo de enemigo para pintar el adecuado
        if(_tipo==4)_tipo=1;
        for(j=0;j<11;j++){
            indice++;
            inicia(&E[indice],"Recursos/enemigos.bmp","Recursos/Bala_enem.bmp",6,12,25,20,140+j*30,130+i*24,8,_tipo,1,
                   "Recursos/10.wav","Recursos/11.wav");
        }
    }
}
//***Permite pintar a los enemigos de acuerdo su vida llamando a la funcion "pinta" ***
void pintar_enemigo(NAVE E[],BITMAP* buffer,int mov){
    int indice=-1;
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<11;j++){
            indice++;
            if(E[indice].vida>0)
            pinta(E[indice],buffer,mov,E[indice].tipo-1);
        }
    }
}
//***Funcion que controla la explosion de la nave enemiga***
void explosion1(NAVE E,BITMAP* buffer){
    play_sample(E.explo,100,150,1000,0);
    BITMAP* parche= create_bitmap(25,20);
    clear_to_color(parche,0x000000); //PARA 1ERO BORRAR LA NAVE Y LUEGO PINTAR LA EXPLOSION
    blit(parche,buffer,0,0,E.x,E.y,25,20);
    masked_blit(E.exp_enem,buffer,0,0,E.x-10,E.y,41,34);
}
//***Funcion que controla la explosion del jugador como su animacion***
void explosion2(NAVE N,BITMAP*buffer,BITMAP* fondo){
     int i,j;
     play_sample(N.explo,100,150,1000,0);
     BITMAP* parche= create_bitmap(30,20);
     clear_to_color(parche,0x000000);
     for(j=0;j<6;j++){//cuantas veces la animacion de la explosion
        for(i=1;i<=2;i++){//ver desde donde se agarra la imagen
            blit(parche,buffer,0,0,N.x,N.y,30,20);
            masked_blit(N.img_nav,buffer,i*30,0,N.x,N.y,30,20);
            imprimir_fondo(fondo,buffer);
            blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
            rest(40);
        }
     }
}
//***Permite iniciar a los escudos (posicion y daño)
void iniciar_escudo(escudo muros[]){
    char pos_muros[3][22] = { //para poder ubicar cada parte del escudo y su correspondiente imagen
        "AEC   AEC   AEC   AEC",
        "B D   B D   B D   B D",
        };
    int i,j,r=0;

    for(i=0;i<21;i++){ //recorre las columnas
        for(j=0;j<2;j++){//recorre las filas
            if(pos_muros[j][i] != ' '){
                muros[r].x=90+i*20;//la dimension en x que tiene el muro y su correpondiente posicion
                muros[r].y=450+j*15;
                muros[r].dan=0;
                //Para pintar cada escudo de manera correcta
                if(pos_muros[j][i]=='A')muros[r].tipo=0;
                if(pos_muros[j][i]=='B')muros[r].tipo=1;
                if(pos_muros[j][i]=='C')muros[r].tipo=2;
                if(pos_muros[j][i]=='D')muros[r].tipo=3;
                if(pos_muros[j][i]=='E')muros[r].tipo=4;
                r++;
            }
        }
    }
}
//***Dibuja a los escudos segun su nivel de daño***
void pintar_escudos(escudo ES[],BITMAP* img_mur,BITMAP* buffer){
    int i;
    for(i=0;i<20;i++){
        if(ES[i].dan!=3)
            masked_blit(img_mur,buffer,ES[i].dan*20,ES[i].tipo*16,ES[i].x,ES[i].y,20,16);
    }
}
//***Funcion que controla que enemigo dispara***
void crear_bala_enemigo(NAVE E[],int *azar){
    if(E[*azar].n_disp == 0) {
        *azar=rand()%55;
        while(E[*azar].vida==0)*azar=rand()%55;//cambia de enemigo si este tiene vida 0
    }
}
//***Permite crear las balas del jugador llama a la funcion temporizador para que no todas las balas salgan juntas***
void crear_bala_nave(NAVE *N,Balas disparos[]){
    if(key[KEY_W] && temporizador(&(N->tick),5)==1){
                if(crear_bala(&(N->n_disp),N->max_disp,disparos,N->x,N->y,N->dir_bala))//funcion ubicada en "disparos.c"
                    play_sample(N->disparo,100,150,1000,0);
                }
}
//***Permite detectar los limites para que las naves enemigas cambien su direccion de izquierda a derecha***
short int limites(NAVE E[],int *dir){
    int i;
    for(i=0;i<55;i++){
        if((E[i].x>520 || E[i].x<50) && E[i].vida!=0){
            *dir=(-1)*(*dir);
            return 1; //true
        }
    }return 0;//false
}
//***Permite mover a todos los enemigos aumentando sus coordenadas con la variable dir***
void mover_enemigos(NAVE E[],int *mov, int *dir){
    int i,j;
    for(i=0;i<55;i++)E[i].x+=*(dir);

    *mov=*mov+1;      //animacion de las naves enemigas
    if(*mov==2)*mov=0;

    if(limites(E,dir)==1){ //detecta los limites para cambiar sus coordenadas en y
        for(j=0;j<55;j++)E[j].y+=10;
    }
}
//***Dibuja las vidas segun la variable de la estructura N.vida
void dibujar_vidas(NAVE N,BITMAP* buffer){
    int x;
    for(x = 0; x < N.vida; x++)
    {
        masked_blit(N.img_nav,buffer, 0 , 0 , 460+x*30 , 50, 30,20);
    }
}
