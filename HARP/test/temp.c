#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h> 
#include "funcionesCroma.h"
#include "stdafx.h"

#define _TIME_MESAURE_1_	
#define _TIME_MESAURE_2_
#define _TIME_MESAURE_3_
#define _TIME_MESAURE_4_
#define _TIME_MESAURE_5_
#define _TIME_MESAURE_6_
#define _TIME_MESAURE_7_
#define _TIME_MESAURE_8_
#define _TIME_MESAURE_9_

#if defined(_TIME_MESAURE_1_) || defined (_TIME_MESAURE_2_) || defined (_TIME_MESAURE_3_) || defined (_TIME_MESAURE_4_) || defined (_TIME_MESAURE_5_) || defined (_TIME_MESAURE_6_) || defined (_TIME_MESAURE_7_) || defined (_TIME_MESAURE_8_) || defined (_TIME_MESAURE_9_) 
#include <time.h>
#endif
#ifdef _TIME_MESAURE_1_
#define _GET_TIME_1_ clock_gettime(CLOCK_REALTIME, &ts0);
#define _PUT_TIME_1_ clock_gettime(CLOCK_REALTIME, &ts1);printf("total time=%ld ns\n",(ts1.tv_sec-ts0.tv_sec)*1000000000+(ts1.tv_nsec-ts0.tv_nsec));
#else
#define _GET_TIME_1_
#define _PUT_TIME_1_
#endif

#ifdef _TIME_MESAURE_2_
#define _GET_TIME_21_ clock_gettime(CLOCK_REALTIME, &ts2);
#define _GET_TIME_22_ clock_gettime(CLOCK_REALTIME, &ts3);
#define _PUT_TIME_2_ printf("\tbucle U f1 p time=%ld ns\n",(ts3.tv_sec-ts2.tv_sec)*1000000000+(ts3.tv_nsec-ts2.tv_nsec));
#else
#define _GET_TIME_21_
#define _GET_TIME_22_
#define _PUT_TIME_2_
#endif

#ifdef _TIME_MESAURE_3_
#define _GET_TIME_31_ clock_gettime(CLOCK_REALTIME, &ts4);
#define _GET_TIME_32_ clock_gettime(CLOCK_REALTIME, &ts5);
#define _PUT_TIME_3_ printf("\tbucle V f1 p time=%ld ns\n",(ts5.tv_sec-ts4.tv_sec)*1000000000+(ts5.tv_nsec-ts4.tv_nsec));
#else
#define _GET_TIME_31_ 
#define _GET_TIME_32_ 
#define _PUT_TIME_3_ 
#endif

#ifdef _TIME_MESAURE_4_
#define _GET_TIME_41_ clock_gettime(CLOCK_REALTIME, &ts6);
#define _GET_TIME_42_ clock_gettime(CLOCK_REALTIME, &ts7);
#define _PUT_TIME_4_ printf("\tbucle U f1 i time=%ld ns\n",(ts7.tv_sec-ts6.tv_sec)*1000000000+(ts7.tv_nsec-ts6.tv_nsec));
#else
#define _GET_TIME_41_ 
#define _GET_TIME_42_ 
#define _PUT_TIME_4_ 
#endif

#ifdef _TIME_MESAURE_5_
#define _GET_TIME_51_ clock_gettime(CLOCK_REALTIME, &ts8);
#define _GET_TIME_52_ clock_gettime(CLOCK_REALTIME, &ts9);
#define _PUT_TIME_5_ printf("\tbucle V f1 i time=%ld ns\n",(ts9.tv_sec-ts8.tv_sec)*1000000000+(ts9.tv_nsec-ts8.tv_nsec));
#else
#define _GET_TIME_51_ 
#define _GET_TIME_52_ 
#define _PUT_TIME_5_ 
#endif

#ifdef _TIME_MESAURE_6_
#define _GET_TIME_61_ clock_gettime(CLOCK_REALTIME, &ts10);
#define _GET_TIME_62_ clock_gettime(CLOCK_REALTIME, &ts11);
#define _PUT_TIME_6_ printf("\tbucle U f2 p time=%ld ns\n",(ts11.tv_sec-ts10.tv_sec)*1000000000+(ts11.tv_nsec-ts10.tv_nsec));
#else
#define _GET_TIME_61_
#define _GET_TIME_62_
#define _PUT_TIME_6_
#endif

#ifdef _TIME_MESAURE_7_
#define _GET_TIME_71_ clock_gettime(CLOCK_REALTIME, &ts12);
#define _GET_TIME_72_ clock_gettime(CLOCK_REALTIME, &ts13);
#define _PUT_TIME_7_ printf("\tbucle V f2 p time=%ld ns\n",(ts13.tv_sec-ts12.tv_sec)*1000000000+(ts13.tv_nsec-ts12.tv_nsec));
#else
#define _GET_TIME_71_
#define _GET_TIME_72_
#define _PUT_TIME_7_
#endif

#ifdef _TIME_MESAURE_8_
#define _GET_TIME_81_ clock_gettime(CLOCK_REALTIME, &ts14);
#define _GET_TIME_82_ clock_gettime(CLOCK_REALTIME, &ts15);
#define _PUT_TIME_8_ printf("\tbucle U f2 i time=%ld ns\n",(ts15.tv_sec-ts14.tv_sec)*1000000000+(ts15.tv_nsec-ts14.tv_nsec));
#else
#define _GET_TIME_81_
#define _GET_TIME_82_
#define _PUT_TIME_8_
#endif

#ifdef _TIME_MESAURE_9_
#define _GET_TIME_91_ clock_gettime(CLOCK_REALTIME, &ts16);
#define _GET_TIME_92_ clock_gettime(CLOCK_REALTIME, &ts17);
#define _PUT_TIME_9_ printf("\tbucle V f2 i time=%ld ns\n",(ts17.tv_sec-ts16.tv_sec)*1000000000+(ts17.tv_nsec-ts16.tv_nsec));
#else
#define _GET_TIME_91_
#define _GET_TIME_92_
#define _PUT_TIME_9_
#endif

/* Imagen Entrelazada: interpolacion de crominancia */
int inbuffer;
int outbuffer;
int width = 640;
int height = 420;
int bitdepth = 8;
int main(void){
    int i,j,aux;
#ifdef _TIME_MESAURE_1_
    struct timespec ts0,ts1;
#endif
#ifdef _TIME_MESAURE_2_
    struct timespec ts2,ts3;
#endif	
#ifdef _TIME_MESAURE_3_
    struct timespec ts4,ts5;
#endif
#ifdef _TIME_MESAURE_4_
    struct timespec ts6,ts7;
#endif
#ifdef _TIME_MESAURE_5_
    struct timespec ts8,ts9;
#endif
#ifdef _TIME_MESAURE_6_
    struct timespec ts10,ts11;
#endif	
#ifdef _TIME_MESAURE_7_
    struct timespec ts12,ts13;
#endif
#ifdef _TIME_MESAURE_8_
    struct timespec ts14,ts15;
#endif
#ifdef _TIME_MESAURE_9_
    struct timespec ts16,ts17;
#endif
    inbuffer = width*height;
    outbuffer = inbuffer;
    /* Valores mínimo y máximo */
    int minval = 1<<(bitdepth-8);
    int maxval = (1<<bitdepth)-1-minval;
    unsigned char Y[inbuffer];
    unsigned char U[Y+width*height];
    unsigned char V[U+width*height/4];
    unsigned char Yout[outbuffer];
    unsigned char Uout[Yout+width*height];
    unsigned char Vout[Uout+width*height/4];
    if( bitdepth==8 ){

        /* Luminancia */
        memcpy(Yout,Y,width*height);
        
        /* Crominancia */
        _GET_TIME_1_
		
                /* Primer Campo */
                /* Líneas Pares */
        _GET_TIME_21_
                
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=0;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente U */
                        aux = (24*(int)U[max(0,i-4)*(width/2)+j]-41*(int)U[max(0,i-2)*(width/2)+j]+1169*(int)U[i*(width/2)+j]-128*(int)U[min(height/2-2,i+2)*(width/2)+j]+512)/1024;
                        Uout[(2*i)*(width/2)+j] = clip(aux,minval,maxval);
                    }
                }	
        _GET_TIME_22_
                
                
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=0;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente V */
                        (aux = (24*(int)V[max(0,i-4)*(width/2)+j]-41*(int)V[max(0,i-2)*(width/2)+j]+1169*(int)V[i*(width/2)+j]-128*(int)V[min(height/2-2,i+2)*(width/2)+j]+512)/1024);
                        (Vout[(2*i)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }
        _GET_TIME_32_
                
        _GET_TIME_41_
                
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=0;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente U */
                        (aux = (-76*(int)U[max(0,i-2)*(width/2)+j]+783*(int)U[i*(width/2)+j]+330*(int)U[min(height/2-2,i+2)*(width/2)+j]-13*(int)U[min(height/2-2,i+4)*(width/2)+j]+512)/1024);
                        (Uout[(2*i+2)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }
        _GET_TIME_42_
                
        _GET_TIME_51_
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=0;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente V */
                        (aux = (-76*(int)V[max(0,i-2)*(width/2)+j]+783*(int)V[i*(width/2)+j]+330*(int)V[min(height/2-2,i+2)*(width/2)+j]-13*(int)V[min(height/2-2,i+4)*(width/2)+j]+512)/1024);
                        (Vout[(2*i+2)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }
        _GET_TIME_52_
                
                /* Segundo Campo */
                /* Líneas Pares */
        _GET_TIME_61_
                
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=1;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente U */
                        (aux = (-13*(int)U[max(1,i-4)*(width/2)+j]+330*(int)U[max(1,i-2)*(width/2)+j]+783*(int)U[i*(width/2)+j]-76*(int)U[min(height/2-1,i+2)*(width/2)+j]+512)/1024);
                        (Uout[(2*i-1)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }	
        _GET_TIME_62_
                
        _GET_TIME_71_
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=1;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente V */
                        (aux = (-13*(int)V[max(1,i-4)*(width/2)+j]+330*(int)V[max(1,i-2)*(width/2)+j]+783*(int)V[i*(width/2)+j]-76*(int)V[min(height/2-1,i+2)*(width/2)+j]+512)/1024);
                        (Vout[(2*i-1)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }	
        _GET_TIME_72_
                
                /* Líneas Impares */
        _GET_TIME_81_
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=1;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente U */
                        (aux = (-128*(int)U[max(1,i-2)*(width/2)+j]+1169*(int)U[i*(width/2)+j]-41*(int)U[min(height/2-1,i+2)*(width/2)+j]+24*(int)U[min(height/2-1,i+4)*(width/2)+j]+512)/1024);
                        (Uout[(2*i+1)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }
        _GET_TIME_82_
                
        _GET_TIME_91_
#pragma omp parallel for private(i,j,maxval) shared(height,width) check
                for(i=1;i<height/2;i+=2){
                    for(j=0;j<width/2;j++){
                        /* Componente V */
                        (aux = (-128*(int)V[max(1,i-2)*(width/2)+j]+1169*(int)V[i*(width/2)+j]-41*(int)V[min(height/2-1,i+2)*(width/2)+j]+24*(int)V[min(height/2-1,i+4)*(width/2)+j]+512)/1024);
                        (Vout[(2*i+1)*(width/2)+j] = clip(aux,minval,maxval));
                    }
                }
        _GET_TIME_92_
        _PUT_TIME_1_
        _PUT_TIME_2_
        _PUT_TIME_3_
        _PUT_TIME_4_
        _PUT_TIME_5_
        _PUT_TIME_6_
        _PUT_TIME_7_
        _PUT_TIME_8_
        _PUT_TIME_9_
    }
    return 1;
}

