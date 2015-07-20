#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h> 
#include "funcionesCroma.h"
#include "stdafx.h"
#include <sys/time.h>
int inbuffer;
int outbuffer;
int width = 640;
int height = 420;
int bitdepth = 8;
int main(void)
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
    inbuffer = width * height;
    outbuffer = inbuffer;
    int minval = 1 << (bitdepth - 8);
    int maxval = (1 << bitdepth) - 1 - minval;
    unsigned char Y[inbuffer];
    unsigned char U[inbuffer];
    unsigned char V[outbuffer / 4];
    unsigned char Yout[outbuffer];
    unsigned char Uout[outbuffer];
    unsigned char Vout[outbuffer / 4];
    if (bitdepth == 8)
    {
        memcpy(Yout, Y, width * height);
        clock_gettime(0, &ts0);
        clock_gettime(0, &ts2);
        MPI_Status stat;
        int size, myid;
        int *argcVar = NULL;
        char ***argvVar = NULL;
        MPI_Init(argcVar, argvVar);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        const int FTAG = 0;
        const int ATAG = 1;
        const int RTAG = 2;
        const int WTAG = 3;
        const int SWTAG = 4;
        const int FRTAG = 5;
        const int FWTAG = 6;
        double timeStart = MPI_Wtime();
        double timeFinish;
        int coordVector0[1];
        int partSize = ((height / 2 - (0))) / (size - 1) > 0 ? ((height / 2 - (0))) / (size - 1) : 1;
        int offset;
        if (myid == 0)
        {
            int followIN = 0;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Recv(&coordVector0, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&U[coordVector0[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector0, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Uout[coordVector0[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Recv(&coordVector0, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&U[coordVector0[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector0, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Uout[coordVector0[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 1 : 
                                        MPI_Recv(&coordVector0, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&U[coordVector0[0]], coordVector0[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector0, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Uout[coordVector0[0]], coordVector0[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char U_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char Uout_Open2MuliCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector0[0] = (((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector0, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector0[0] = (((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector0, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector0[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector0, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector0[0] = (((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector0, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (aux = (24 * (int) U_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj - 41 * (int) U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 1169 * (int) U_iMulOpenwidthDiv2ClosePlusj - 128 * (int) U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024);
                                    (Uout_Open2MuliCloseMulOpenwidthDiv2ClosePlusj = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                    (idxForReadWriteSwitch = 0);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, WTAG, MPI_COMM_WORLD);
                                    (coordVector0[0] = (2 * i) * (width / 2) + j);
                                    MPI_Send(&coordVector0, 1, MPI_INT, 0, WTAG, MPI_COMM_WORLD);
                                    MPI_Send(&Uout_Open2MuliCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, WTAG, MPI_COMM_WORLD);
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (0))) / (size - 1) > 0 ? ((height / 2 - (0))) / (size - 1) : 1);
        int coordVector1[1];
        clock_gettime(0, &ts3);
        if (myid == 0)
        {
            int followIN = 0;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Recv(&coordVector1, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&V[coordVector1[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector1, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Vout[coordVector1[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Recv(&coordVector1, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&V[coordVector1[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector1, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Vout[coordVector1[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 2 : 
                                        MPI_Recv(&coordVector1, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&V[coordVector1[0]], coordVector1[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector1, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Vout[coordVector1[0]], coordVector1[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char V_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector1[0] = (((0) > (i - 4)) ? (0) : (i - 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector1, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector1[0] = (((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector1, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector1[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector1, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector1[0] = (((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector1, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (24 * (int) V_OpenOpenOpen0CloseGreaterOpeniSub4CloseCloseAskOpen0CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj - 41 * (int) V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 1169 * (int) V_iMulOpenwidthDiv2ClosePlusj - 128 * (int) V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Vout[(2 * i) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (0))) / (size - 1) > 0 ? ((height / 2 - (0))) / (size - 1) : 1);
        int coordVector2[1];
        clock_gettime(0, &ts5);
        clock_gettime(0, &ts6);
        if (myid == 0)
        {
            int followIN = 0;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Recv(&coordVector2, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&U[coordVector2[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector2, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Uout[coordVector2[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Recv(&coordVector2, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&U[coordVector2[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector2, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Uout[coordVector2[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 1 : 
                                        MPI_Recv(&coordVector2, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&U[coordVector2[0]], coordVector2[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector2, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Uout[coordVector2[0]], coordVector2[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector2[0] = (((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector2, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector2[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector2, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector2[0] = (((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector2, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector2[0] = (((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector2, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 76 * (int) U_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 783 * (int) U_iMulOpenwidthDiv2ClosePlusj + 330 * (int) U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj - 13 * (int) U_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Uout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (0))) / (size - 1) > 0 ? ((height / 2 - (0))) / (size - 1) : 1);
        int coordVector3[1];
        clock_gettime(0, &ts7);
        clock_gettime(0, &ts8);
        if (myid == 0)
        {
            int followIN = 0;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Recv(&coordVector3, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&V[coordVector3[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector3, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Vout[coordVector3[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Recv(&coordVector3, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&V[coordVector3[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector3, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Vout[coordVector3[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 2 : 
                                        MPI_Recv(&coordVector3, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&V[coordVector3[0]], coordVector3[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector3, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Vout[coordVector3[0]], coordVector3[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector3[0] = (((0) > (i - 2)) ? (0) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector3, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector3[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector3, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector3[0] = (((height / 2 - 2) < (i + 2)) ? (height / 2 - 2) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector3, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector3[0] = (((height / 2 - 2) < (i + 4)) ? (height / 2 - 2) : (i + 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector3, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 76 * (int) V_OpenOpenOpen0CloseGreaterOpeniSub2CloseCloseAskOpen0CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 783 * (int) V_iMulOpenwidthDiv2ClosePlusj + 330 * (int) V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj - 13 * (int) V_OpenOpenOpenheightDiv2Sub2CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub2CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Vout[(2 * i + 2) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (1))) / (size - 1) > 0 ? ((height / 2 - (1))) / (size - 1) : 1);
        int coordVector4[1];
        clock_gettime(0, &ts9);
        clock_gettime(0, &ts10);
        if (myid == 0)
        {
            int followIN = 1;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Recv(&coordVector4, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&U[coordVector4[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector4, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Uout[coordVector4[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Recv(&coordVector4, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&U[coordVector4[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector4, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Uout[coordVector4[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 1 : 
                                        MPI_Recv(&coordVector4, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&U[coordVector4[0]], coordVector4[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector4, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Uout[coordVector4[0]], coordVector4[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char U_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector4[0] = (((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector4, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector4[0] = (((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector4, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector4[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector4, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector4[0] = (((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector4, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 13 * (int) U_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj + 330 * (int) U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 783 * (int) U_iMulOpenwidthDiv2ClosePlusj - 76 * (int) U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Uout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (1))) / (size - 1) > 0 ? ((height / 2 - (1))) / (size - 1) : 1);
        int coordVector5[1];
        clock_gettime(0, &ts11);
        clock_gettime(0, &ts12);
        if (myid == 0)
        {
            int followIN = 1;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Recv(&coordVector5, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&V[coordVector5[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector5, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Vout[coordVector5[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Recv(&coordVector5, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&V[coordVector5[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector5, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Vout[coordVector5[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 2 : 
                                        MPI_Recv(&coordVector5, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&V[coordVector5[0]], coordVector5[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector5, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Vout[coordVector5[0]], coordVector5[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char V_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector5[0] = (((1) > (i - 4)) ? (1) : (i - 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector5, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector5[0] = (((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector5, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector5[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector5, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector5[0] = (((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector5, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 13 * (int) V_OpenOpenOpen1CloseGreaterOpeniSub4CloseCloseAskOpen1CloseDotOpeniSub4CloseCloseMulOpenwidthDiv2ClosePlusj + 330 * (int) V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 783 * (int) V_iMulOpenwidthDiv2ClosePlusj - 76 * (int) V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Vout[(2 * i - 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (1))) / (size - 1) > 0 ? ((height / 2 - (1))) / (size - 1) : 1);
        int coordVector6[1];
        clock_gettime(0, &ts13);
        clock_gettime(0, &ts14);
        if (myid == 0)
        {
            int followIN = 1;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Recv(&coordVector6, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&U[coordVector6[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector6, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Uout[coordVector6[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Recv(&coordVector6, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&U[coordVector6[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector6, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Uout[coordVector6[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 1 : 
                                        MPI_Recv(&coordVector6, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&U[coordVector6[0]], coordVector6[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector6, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Uout[coordVector6[0]], coordVector6[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector6[0] = (((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector6, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector6[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector6, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector6[0] = (((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector6, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 1);
                                    (coordVector6[0] = (((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector6, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 128 * (int) U_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 1169 * (int) U_iMulOpenwidthDiv2ClosePlusj - 41 * (int) U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 24 * (int) U_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Uout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        (partSize = ((height / 2 - (1))) / (size - 1) > 0 ? ((height / 2 - (1))) / (size - 1) : 1);
        int coordVector7[1];
        clock_gettime(0, &ts15);
        clock_gettime(0, &ts16);
        if (myid == 0)
        {
            int followIN = 1;
            int killed = 0;
            for (int to = 1;
                    to < size;
                    ++to)
            {
                if ((followIN + partSize) < height / 2)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((height / 2 - followIN) > 0)
                    {
                        (partSize = height / 2 - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&minval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&width, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&height, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&aux, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&maxval, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                            MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 1 : 
                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 2 : 
                            MPI_Recv(&coordVector7, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                            MPI_Send(&V[coordVector7[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 3 : 
                            MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 4 : 
                            MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 5 : 
                            MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                        case 6 : 
                            MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                            break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                                MPI_Recv(&coordVector7, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&Vout[coordVector7[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                        }
                    }
                    else
                        if (stat.MPI_TAG == SWTAG)
                        {
                            switch (partSize)
                            {
                                case 0 : 
                                    do
                                    {
                                        MPI_Recv(&partSize, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                                        if (stat.MPI_TAG == RTAG)
                                        {
                                            switch (partSize)
                                            {
                                                case 0 : 
                                                    MPI_Send(&minval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 1 : 
                                                    MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 2 : 
                                                    MPI_Recv(&coordVector7, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                                    MPI_Send(&V[coordVector7[0]], 1, MPI_UNSIGNED_CHAR, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 3 : 
                                                    MPI_Send(&width, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 4 : 
                                                    MPI_Send(&height, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 5 : 
                                                    MPI_Send(&aux, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                                case 6 : 
                                                    MPI_Send(&maxval, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                                    break;
                                            }
                                        }
                                    }
                                    while (stat.MPI_TAG != WTAG);
                                    MPI_Recv(&coordVector7, 1, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Recv(&Vout[coordVector7[0]], 1, MPI_UNSIGNED_CHAR, source, WTAG, MPI_COMM_WORLD, &stat);
                                    break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 2 : 
                                        MPI_Recv(&coordVector7, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                        MPI_Send(&V[coordVector7[0]], coordVector7[1], MPI_UNSIGNED_CHAR, source, FRTAG, MPI_COMM_WORLD);
                                        break;
                                }
                            }
                            else
                                if (stat.MPI_TAG == FWTAG)
                                {
                                    switch (partSize)
                                    {
                                        case 0 : 
                                            MPI_Recv(&coordVector7, 2, MPI_INT, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Recv(&Vout[coordVector7[0]], coordVector7[1], MPI_UNSIGNED_CHAR, source, FWTAG, MPI_COMM_WORLD, &stat);
                                            break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < height / 2)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((height / 2 - followIN) > 0)
                                            {
                                                (partSize = height / 2 - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&minval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&width, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&height, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&aux, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&maxval, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > height / 2)
                                        {
                                            MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                                            killed++;
                                        }
                                        followIN += partSize;
                                        if (killed == size - 1)
                                        {
                                            break;
                                        }
                                    }
            }
        }
        if (myid != 0)
        {
            while (1)
            {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                if (stat.MPI_TAG == ATAG)
                {
                    MPI_Recv(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    int idxForReadWriteSwitch;
                    MPI_Recv(&minval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&width, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&height, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&aux, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&maxval, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    for (int i = offset;
                            i < offset + partSize;
                            ++i)
                    {
                        unsigned char V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_iMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj;
                        unsigned char V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj;
                        {
                            {
                                for (j = 0;
                                        j < width / 2;
                                        j++)
                                {
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector7[0] = (((1) > (i - 2)) ? (1) : (i - 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector7, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector7[0] = i * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector7, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_iMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector7[0] = (((height / 2 - 1) < (i + 2)) ? (height / 2 - 1) : (i + 2)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector7, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    (idxForReadWriteSwitch = 2);
                                    (coordVector7[0] = (((height / 2 - 1) < (i + 4)) ? (height / 2 - 1) : (i + 4)) * (width / 2) + j);
                                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Send(&coordVector7, 1, MPI_INT, 0, RTAG, MPI_COMM_WORLD);
                                    MPI_Recv(&V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj, 1, MPI_UNSIGNED_CHAR, 0, RTAG, MPI_COMM_WORLD, &stat);
                                    ((aux = (- 128 * (int) V_OpenOpenOpen1CloseGreaterOpeniSub2CloseCloseAskOpen1CloseDotOpeniSub2CloseCloseMulOpenwidthDiv2ClosePlusj + 1169 * (int) V_iMulOpenwidthDiv2ClosePlusj - 41 * (int) V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus2CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus2CloseCloseMulOpenwidthDiv2ClosePlusj + 24 * (int) V_OpenOpenOpenheightDiv2Sub1CloseLowerOpeniPlus4CloseCloseAskOpenheightDiv2Sub1CloseDotOpeniPlus4CloseCloseMulOpenwidthDiv2ClosePlusj + 512) / 1024));
                                    (Vout[(2 * i + 1) * (width / 2) + j] = aux < minval ? minval : ((aux > maxval) ? maxval : aux));
                                }
                            }
                        }
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
        if (myid == 0)
        {
            (timeFinish = MPI_Wtime());
        }
        MPI_Finalize();
        if (myid == 0)
        {
            printf("MPI_Wtime measured: %1.2f\n", timeFinish - timeStart);
            clock_gettime(0, &ts17);
            clock_gettime(0, &ts1);
            printf("\tbucle U f1 p time=%ld ns\n", (ts3.tv_sec - ts2.tv_sec) * 1000000000 + (ts3.tv_nsec - ts2.tv_nsec));
            printf("\tbucle V f1 p time=%ld ns\n", (ts5.tv_sec - ts4.tv_sec) * 1000000000 + (ts5.tv_nsec - ts4.tv_nsec));
            printf("\tbucle U f1 i time=%ld ns\n", (ts7.tv_sec - ts6.tv_sec) * 1000000000 + (ts7.tv_nsec - ts6.tv_nsec));
            printf("\tbucle V f1 i time=%ld ns\n", (ts9.tv_sec - ts8.tv_sec) * 1000000000 + (ts9.tv_nsec - ts8.tv_nsec));
            printf("\tbucle U f2 p time=%ld ns\n", (ts11.tv_sec - ts10.tv_sec) * 1000000000 + (ts11.tv_nsec - ts10.tv_nsec));
            printf("\tbucle V f2 p time=%ld ns\n", (ts13.tv_sec - ts12.tv_sec) * 1000000000 + (ts13.tv_nsec - ts12.tv_nsec));
            printf("\tbucle U f2 i time=%ld ns\n", (ts15.tv_sec - ts14.tv_sec) * 1000000000 + (ts15.tv_nsec - ts14.tv_nsec));
            printf("\tbucle V f2 i time=%ld ns\n", (ts17.tv_sec - ts16.tv_sec) * 1000000000 + (ts17.tv_nsec - ts16.tv_nsec));
            
            printf("total time=%ld ns\n", (ts1.tv_sec - ts0.tv_sec) * 1000000000 + (ts1.tv_nsec - ts0.tv_nsec));
        }
    }
    return 1;
}
