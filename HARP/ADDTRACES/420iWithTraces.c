#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
//cabecera openMP
#include <omp.h> 
#include "funcionesCroma.h"
#include <sys/time.h>
void chroma_conversion_420to422_interlaced(unsigned char *inbuffer, unsigned char *outbuffer, int width, int height, int bitdepth)
{
    int i, j, aux;
    struct timespec ts0, ts1;
    struct timespec ts2, ts3;
    struct timespec ts4, ts5;
    struct timespec ts6, ts7;
    struct timespec ts8, ts9;
    struct timespec ts10, ts11;
    struct timespec ts12, ts13;
    struct timespec ts14, ts15;
    struct timespec ts16, ts17;
    int minval = 1 << (bitdepth - 8);
    int maxval = (1 << bitdepth) - 1 - minval;
    if (bitdepth == 8)
    {
        unsigned char *Y = inbuffer;
        unsigned char *U = Y + width * height;
        unsigned char *V = U + width * height / 4;
        unsigned char *Yout = outbuffer;
        unsigned char *Uout = Yout + width * height;
        unsigned char *Vout = Uout + width * height / 2;
        memcpy(Yout, Y, width * height);
        clock_gettime(0, &ts0);
        clock_gettime(0, &ts2);
        mem_trace_def_mem("aux", &aux, sizeof(int), sizeof (aux));
        for (i = 0;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("U", &U[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j]);
                        mem_trace_read("U", &U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[i * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                        (aux = (24 * (int) U[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j] - 41 * (int) U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 1169 * (int) U[i * (width / 2) + j] - 128 * (int) U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Uout", &Uout[(2 * i) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Uout[(2 * i) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts3);
        for (i = 0;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("V", &V[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j]);
                        mem_trace_read("V", &V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[i * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                        (aux = (24 * (int) V[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j] - 41 * (int) V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 1169 * (int) V[i * (width / 2) + j] - 128 * (int) V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Vout", &Vout[(2 * i) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Vout[(2 * i) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts5);
        clock_gettime(0, &ts6);
        for (i = 0;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("U", &U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[i * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j]);
                        (aux = (- 76 * (int) U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 783 * (int) U[i * (width / 2) + j] + 330 * (int) U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] - 13 * (int) U[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Uout", &Uout[(2 * i + 2) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Uout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts7);
        clock_gettime(0, &ts8);
        for (i = 0;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("V", &V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[i * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j]);
                        (aux = (- 76 * (int) V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 783 * (int) V[i * (width / 2) + j] + 330 * (int) V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] - 13 * (int) V[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Vout", &Vout[(2 * i + 2) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Vout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts9);
        clock_gettime(0, &ts10);
        for (i = 1;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("U", &U[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j]);
                        mem_trace_read("U", &U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[i * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                        (aux = (- 13 * (int) U[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j] + 330 * (int) U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 783 * (int) U[i * (width / 2) + j] - 76 * (int) U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Uout", &Uout[(2 * i - 1) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Uout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts11);
        clock_gettime(0, &ts12);
        for (i = 1;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("V", &V[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j]);
                        mem_trace_read("V", &V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[i * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                        (aux = (- 13 * (int) V[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j] + 330 * (int) V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 783 * (int) V[i * (width / 2) + j] - 76 * (int) V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Vout", &Vout[(2 * i - 1) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Vout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts13);
        clock_gettime(0, &ts14);
        for (i = 1;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("U", &U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[i * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                        mem_trace_read("U", &U[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j]);
                        (aux = (- 128 * (int) U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 1169 * (int) U[i * (width / 2) + j] - 41 * (int) U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 24 * (int) U[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Uout", &Uout[(2 * i + 1) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Uout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts15);
        clock_gettime(0, &ts16);
        for (i = 1;
            i < height / 2;
            i += 2)
        {
            mem_trace_iter_start("i", i);
            {
                for (j = 0;
                    j < width / 2;
                    j++)
                {
                    mem_trace_iter_start("j", j);
                    {
                        mem_trace_read("V", &V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[i * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                        mem_trace_read("V", &V[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j]);
                        (aux = (- 128 * (int) V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 1169 * (int) V[i * (width / 2) + j] - 41 * (int) V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 24 * (int) V[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                        mem_trace_write("Vout", &Vout[(2 * i + 1) * (width / 2) + j]);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        mem_trace_read("aux", &aux);
                        (Vout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                    }
                    mem_trace_iter_end("j", j);
                }
            }
            mem_trace_iter_end("i", i);
        }
        clock_gettime(0, &ts17);
        clock_gettime(0, &ts1);
        printf("total time=%ld ns\n", (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec));
        printf("\tbucle U f1 p time=%ld ns\n", (ts3.tv_sec - ts2.tv_sec) * 1000000000 + (ts3.tv_nsec - ts2.tv_nsec));
        printf("\tbucle V f1 p time=%ld ns\n", (ts5.tv_sec - ts4.tv_sec) * 1000000000 + (ts5.tv_nsec - ts4.tv_nsec));
        printf("\tbucle U f1 i time=%ld ns\n", (ts7.tv_sec - ts6.tv_sec) * 1000000000 + (ts7.tv_nsec - ts6.tv_nsec));
        printf("\tbucle V f1 i time=%ld ns\n", (ts9.tv_sec - ts8.tv_sec) * 1000000000 + (ts9.tv_nsec - ts8.tv_nsec));
        printf("\tbucle U f2 p time=%ld ns\n", (ts11.tv_sec - ts10.tv_sec) * 1000000000 + (ts11.tv_nsec - ts10.tv_nsec));
        printf("\tbucle V f2 p time=%ld ns\n", (ts13.tv_sec - ts12.tv_sec) * 1000000000 + (ts13.tv_nsec - ts12.tv_nsec));
        printf("\tbucle U f2 i time=%ld ns\n", (ts15.tv_sec - ts14.tv_sec) * 1000000000 + (ts15.tv_nsec - ts14.tv_nsec));
        printf("\tbucle V f2 i time=%ld ns\n", (ts17.tv_sec - ts16.tv_sec) * 1000000000 + (ts17.tv_nsec - ts16.tv_nsec));
    }
    else
        if (bitdepth == 10)
        {
            unsigned short *Y = (unsigned short *) inbuffer;
            unsigned short *U = Y + width * height;
            unsigned short *V = U + width * height / 4;
            unsigned short *Yout = (unsigned short *) outbuffer;
            unsigned short *Uout = Yout + width * height;
            unsigned short *Vout = Uout + width * height / 2;
            memcpy(Yout, Y, width * height * sizeof(short));
            clock_gettime(0, &ts0);
            for (i = 0;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("U", &U[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j]);
                            mem_trace_read("U", &U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[i * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                            (aux = (24 * (int) U[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j] - 41 * (int) U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 1169 * (int) U[i * (width / 2) + j] - 128 * (int) U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Uout", &Uout[(2 * i) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Uout[(2 * i) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts3);
            clock_gettime(0, &ts4);
            for (i = 0;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("V", &V[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j]);
                            mem_trace_read("V", &V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[i * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                            (aux = (24 * (int) V[(((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j] - 41 * (int) V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 1169 * (int) V[i * (width / 2) + j] - 128 * (int) V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Vout", &Vout[(2 * i) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Vout[(2 * i) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts5);
            clock_gettime(0, &ts6);
            for (i = 0;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("U", &U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[i * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j]);
                            (aux = (- 76 * (int) U[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 783 * (int) U[i * (width / 2) + j] + 330 * (int) U[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] - 13 * (int) U[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Uout", &Uout[(2 * i + 2) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Uout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts7);
            clock_gettime(0, &ts8);
            for (i = 0;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("V", &V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[i * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j]);
                            (aux = (- 76 * (int) V[(((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j] + 783 * (int) V[i * (width / 2) + j] + 330 * (int) V[(((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j] - 13 * (int) V[(((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Vout", &Vout[(2 * i + 2) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Vout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts9);
            clock_gettime(0, &ts10);
            for (i = 1;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("U", &U[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j]);
                            mem_trace_read("U", &U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[i * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                            (aux = (- 13 * (int) U[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j] + 330 * (int) U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 783 * (int) U[i * (width / 2) + j] - 76 * (int) U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Uout", &Uout[(2 * i - 1) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Uout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts11);
            clock_gettime(0, &ts12);
            for (i = 1;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("V", &V[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j]);
                            mem_trace_read("V", &V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[i * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                            (aux = (- 13 * (int) V[(((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j] + 330 * (int) V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 783 * (int) V[i * (width / 2) + j] - 76 * (int) V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Vout", &Vout[(2 * i - 1) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Vout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts13);
            clock_gettime(0, &ts14);
            for (i = 1;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("U", &U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[i * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                            mem_trace_read("U", &U[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j]);
                            (aux = (- 128 * (int) U[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 1169 * (int) U[i * (width / 2) + j] - 41 * (int) U[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 24 * (int) U[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Uout", &Uout[(2 * i + 1) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Uout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts15);
            clock_gettime(0, &ts16);
            for (i = 1;
                i < height / 2;
                i += 2)
            {
                mem_trace_iter_start("i", i);
                {
                    for (j = 0;
                        j < width / 2;
                        j++)
                    {
                        mem_trace_iter_start("j", j);
                        {
                            mem_trace_read("V", &V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[i * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j]);
                            mem_trace_read("V", &V[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j]);
                            (aux = (- 128 * (int) V[(((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j] + 1169 * (int) V[i * (width / 2) + j] - 41 * (int) V[(((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j] + 24 * (int) V[(((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j] + 512) / 1024);
                            mem_trace_write("Vout", &Vout[(2 * i + 1) * (width / 2) + j]);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            mem_trace_read("aux", &aux);
                            (Vout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                        }
                        mem_trace_iter_end("j", j);
                    }
                }
                mem_trace_iter_end("i", i);
            }
            clock_gettime(0, &ts17);
            clock_gettime(0, &ts1);
            printf("total time=%ld ns\n", (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec));
            printf("\tbucle U f1 p time=%ld ns\n", (ts3.tv_sec - ts2.tv_sec) * 1000000000 + (ts3.tv_nsec - ts2.tv_nsec));
            printf("\tbucle V f1 p time=%ld ns\n", (ts5.tv_sec - ts4.tv_sec) * 1000000000 + (ts5.tv_nsec - ts4.tv_nsec));
            printf("\tbucle U f1 i time=%ld ns\n", (ts7.tv_sec - ts6.tv_sec) * 1000000000 + (ts7.tv_nsec - ts6.tv_nsec));
            printf("\tbucle V f1 i time=%ld ns\n", (ts9.tv_sec - ts8.tv_sec) * 1000000000 + (ts9.tv_nsec - ts8.tv_nsec));
            printf("\tbucle U f2 p time=%ld ns\n", (ts11.tv_sec - ts10.tv_sec) * 1000000000 + (ts11.tv_nsec - ts10.tv_nsec));
            printf("\tbucle V f2 p time=%ld ns\n", (ts13.tv_sec - ts12.tv_sec) * 1000000000 + (ts13.tv_nsec - ts12.tv_nsec));
            printf("\tbucle U f2 i time=%ld ns\n", (ts15.tv_sec - ts14.tv_sec) * 1000000000 + (ts15.tv_nsec - ts14.tv_nsec));
            printf("\tbucle V f2 i time=%ld ns\n", (ts17.tv_sec - ts16.tv_sec) * 1000000000 + (ts17.tv_nsec - ts16.tv_nsec));
        }
    return;
}
