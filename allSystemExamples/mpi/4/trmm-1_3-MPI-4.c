#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double alpha;
double A[2048][2048];
double B[2048][2048];
static void init_array()
{
    int i, j;
    alpha = 12435;
    for (i = 0;
        i < 2048;
        )
    {
        for (j = 0;
            j < 2048;
            )
        {
            A[i][j] = ((double) i * j) / 2048;
            B[i][j] = ((double) i * j + 1) / 2048;
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    int i, j, k;
    int n = 2048;
    int size, myid;

      init_array();
    
    MPI_Status stat;
    
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
    int coordVector0[2];
    int partSize, offset;
    for (i = 1;
        i < n;
        i++)
    {
        (partSize = (((i - (0))) / (size - 1)) > 0 ? ((((i - (0))) / (size - 1)) / 4) : 1);
        if (myid == 0)
        {
            int followIN = 0;
            int killed = 0;
            for (int to = 1;
                to < size;
                ++to)
            {
                if ((followIN + partSize) < i)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&alpha, 1, MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((i - followIN) > 0)
                    {
                        (partSize = i - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&alpha, 1, MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (killed != size - 1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                        MPI_Send(&alpha, 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                        case 1 : 
                        MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                        MPI_Send(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                        case 2 : 
                        MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                        MPI_Send(&A[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                            MPI_Recv(&coordVector0, 2, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                            MPI_Recv(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, WTAG, MPI_COMM_WORLD, &stat);
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
                                            MPI_Send(&alpha, 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                            case 1 : 
                                            MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Send(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                            case 2 : 
                                            MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Send(&A[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                        }
                                    }
                                }
                                while (stat.MPI_TAG != WTAG);
                                MPI_Recv(&coordVector0, 2, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, WTAG, MPI_COMM_WORLD, &stat);
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
                                    MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FRTAG, MPI_COMM_WORLD);
                                    break;
                                    case 2 : 
                                    MPI_Recv(&coordVector0, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Send(&A[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FRTAG, MPI_COMM_WORLD);
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
                                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FWTAG, MPI_COMM_WORLD, &stat);
                                        break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        MPI_Recv(&B[offset], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < i)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&alpha, 1, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((i - followIN) > 0)
                                            {
                                                (partSize = i - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&alpha, 1, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > i)
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
                    MPI_Recv(&alpha, 1, MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&B[offset], partSize * (2048), MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD, &stat);
                    (coordVector0[0] = i);
                    (coordVector0[1] = ((i + 1) - coordVector0[0]));
                    (idxForReadWriteSwitch = 2);
                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                    MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                    MPI_Recv(&A[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    (coordVector0[0] = i);
                    (coordVector0[1] = (offset > (i + 1)) ? ((i + 1) - (i)) : (offset - (i)));
                    if ((i) < offset && coordVector0[1] > 0)
                    {
                        (idxForReadWriteSwitch = 1);
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    }
                    (coordVector0[0] = ((offset + partSize) > (i)) ? (offset + partSize) : (i));
                    (coordVector0[1] = ((offset + partSize) > (i)) ? (i + 1 - (offset + partSize)) : (i + 1 - i));
                    if ((i + 1) > offset + partSize && coordVector0[1] > 0)
                    {
                        (idxForReadWriteSwitch = 1);
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    }
                    for (int j = offset;
                        j < offset + partSize;
                        ++j)
                    {
                        double B_i_j;
                        double A_i_k;
                        {
                            {
                                for (k = 0;
                                    k < i;
                                    k++)
                                {
                                    B_i_j = B[i][j];
                                    (B[i][j] += alpha * A[i][k] * B[j][k]);
                                }
                            }
                        }
                    }
                    (idxForReadWriteSwitch = 0);
                    (coordVector0[0] = i < offset);
                    (coordVector0[1] = (offset > i + 1) ? (i + 1 - i) : (offset - i));
                    if ((i) <= offset && coordVector0[1] > 0)
                    {
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FWTAG, MPI_COMM_WORLD);
                    }
                    (idxForReadWriteSwitch = 0);
                    (coordVector0[0] = ((offset + partSize) > (i)) ? (offset + partSize) : (i));
                    (coordVector0[1] = ((offset + partSize) > (i)) ? (i + 1 - (offset + partSize)) : (i + 1 - i));
                    if ((i + 1) >= offset + partSize && coordVector0[1] > 0)
                    {
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FWTAG, MPI_COMM_WORLD);
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&B[offset], partSize * (2048), MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
            }
        }
      
	#pragma omp parallel for private(k)
	  for (j = i;
	      j < i + 1;
	      j++)
	  {
	      for (k = 0;
		  k < i;
		  k++)
	      {
		  B[i][j] += alpha * A[i][k] * B[j][k];
	      }
	  }
(partSize = (((n - (i + 1))) / (size - 1)) > 0 ? ((((n - (i + 1))) / (size - 1)) / 4) : 1);
        if (myid == 0)
        {
            int followIN = i + 1;
            int killed = 0;
            for (int to = 1;
                to < size;
                ++to)
            {
                if ((followIN + partSize) < n)
                {
                    MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&alpha, 1, MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                }
                else
                    if ((n - followIN) > 0)
                    {
                        (partSize = n - followIN);
                        MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&i, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&alpha, 1, MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                        MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
                    }
                    else
                    {
                        MPI_Send(&offset, 1, MPI_INT, to, FTAG, MPI_COMM_WORLD);
                        killed++;
                    }
                followIN += partSize;
            }
            while (killed != size - 1)
            {
                MPI_Recv(&partSize, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                int source = stat.MPI_SOURCE;
                if (stat.MPI_TAG == RTAG)
                {
                    switch (partSize)
                    {
                        case 0 : 
                        MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                        break;
                        case 1 : 
                        MPI_Send(&alpha, 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                        case 2 : 
                        MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                        MPI_Send(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                        case 3 : 
                        MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                        MPI_Send(&A[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                        break;
                    }
                }
                else
                    if (stat.MPI_TAG == WTAG)
                    {
                        switch (partSize)
                        {
                            case 0 : 
                            MPI_Recv(&coordVector0, 2, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                            MPI_Recv(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, WTAG, MPI_COMM_WORLD, &stat);
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
                                            MPI_Send(&i, 1, MPI_INT, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                            case 1 : 
                                            MPI_Send(&alpha, 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                            case 2 : 
                                            MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Send(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                            case 3 : 
                                            MPI_Recv(&coordVector0, 2, MPI_INT, source, RTAG, MPI_COMM_WORLD, &stat);
                                            MPI_Send(&A[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, RTAG, MPI_COMM_WORLD);
                                            break;
                                        }
                                    }
                                }
                                while (stat.MPI_TAG != WTAG);
                                MPI_Recv(&coordVector0, 2, MPI_INT, source, WTAG, MPI_COMM_WORLD, &stat);
                                MPI_Recv(&B[coordVector0[0]][coordVector0[1]], 1, MPI_DOUBLE, source, WTAG, MPI_COMM_WORLD, &stat);
                                break;
                            }
                        }
                        else
                            if (stat.MPI_TAG == FRTAG)
                            {
                                switch (partSize)
                                {
                                    case 2 : 
                                    MPI_Recv(&coordVector0, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FRTAG, MPI_COMM_WORLD);
                                    break;
                                    case 3 : 
                                    MPI_Recv(&coordVector0, 2, MPI_INT, source, FRTAG, MPI_COMM_WORLD, &stat);
                                    MPI_Send(&A[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FRTAG, MPI_COMM_WORLD);
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
                                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, source, FWTAG, MPI_COMM_WORLD, &stat);
                                        break;
                                    }
                                }
                                else
                                    if (stat.MPI_TAG == ATAG)
                                    {
                                        MPI_Recv(&offset, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD, &stat);
                                        MPI_Recv(&B[offset], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD, &stat);
                                        if ((followIN + partSize) < n)
                                        {
                                            MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&alpha, 1, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                            MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                        }
                                        else
                                            if ((n - followIN) > 0)
                                            {
                                                (partSize = n - followIN);
                                                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&i, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&alpha, 1, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                                MPI_Send(&B[followIN], partSize * (2048), MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                                            }
                                        if ((followIN + partSize) > n)
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
                    MPI_Recv(&i, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&alpha, 1, MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD, &stat);
                    MPI_Recv(&B[offset], partSize * (2048), MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD, &stat);
                    (coordVector0[0] = i);
                    (coordVector0[1] = ((i + 1) - coordVector0[0]));
                    (idxForReadWriteSwitch = 3);
                    MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                    MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                    MPI_Recv(&A[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    (coordVector0[0] = i);
                    (coordVector0[1] = (offset > (i + 1)) ? ((i + 1) - (i)) : (offset - (i)));
                    if ((i) < offset && coordVector0[1] > 0)
                    {
                        (idxForReadWriteSwitch = 2);
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    }
                    (coordVector0[0] = ((offset + partSize) > (i)) ? (offset + partSize) : (i));
                    (coordVector0[1] = ((offset + partSize) > (i)) ? (i + 1 - (offset + partSize)) : (i + 1 - i));
                    if ((i + 1) > offset + partSize && coordVector0[1] > 0)
                    {
                        (idxForReadWriteSwitch = 2);
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FRTAG, MPI_COMM_WORLD);
                        MPI_Recv(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FRTAG, MPI_COMM_WORLD, &stat);
                    }
                    for (int j = offset;
                        j < offset + partSize;
                        ++j)
                    {
                        double B_i_j;
                        double A_i_k;
                        {
                            {
                                for (k = 0;
                                    k < i;
                                    k++)
                                {
                                    B_i_j = B[i][j];
                                    (B[i][j] += alpha * A[i][k] * B[j][k]);
                                }
                            }
                        }
                    }
                    (idxForReadWriteSwitch = 0);
                    (coordVector0[0] = i < offset);
                    (coordVector0[1] = (offset > i + 1) ? (i + 1 - i) : (offset - i));
                    if ((i) <= offset && coordVector0[1] > 0)
                    {
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FWTAG, MPI_COMM_WORLD);
                    }
                    (idxForReadWriteSwitch = 0);
                    (coordVector0[0] = ((offset + partSize) > (i)) ? (offset + partSize) : (i));
                    (coordVector0[1] = ((offset + partSize) > (i)) ? (i + 1 - (offset + partSize)) : (i + 1 - i));
                    if ((i + 1) >= offset + partSize && coordVector0[1] > 0)
                    {
                        MPI_Send(&idxForReadWriteSwitch, 1, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&coordVector0, 2, MPI_INT, 0, FWTAG, MPI_COMM_WORLD);
                        MPI_Send(&B[coordVector0[0]], coordVector0[1] * (2048), MPI_DOUBLE, 0, FWTAG, MPI_COMM_WORLD);
                    }
                    MPI_Send(&partSize, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, 0, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&B[offset], partSize * (2048), MPI_DOUBLE, 0, ATAG, MPI_COMM_WORLD);
                }
                else
                    if (stat.MPI_TAG == FTAG)
                    {
                        break;
                    }
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
        double total = 0;
        for (int x = 0;
            x < n;
            ++x)
        {
            for (int y = 0;
                y < n;
                ++y)
            {
                total += B[x][y];
            }
        }
        printf("Total: %f\n", total);
    }
    return 0;
}
