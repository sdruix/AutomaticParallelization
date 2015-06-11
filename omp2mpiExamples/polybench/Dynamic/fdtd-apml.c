#include <string.h>
#include <math.h>


/* Default problem size. */
#ifndef CZ
# define CZ 400
#endif
#ifndef CYM
# define CYM 400
#endif
#ifndef CXM
# define CXM 400
#endif

double ch;
double mui;
double Ex[CZ + 1][CYM + 1][CXM + 1];
double Ey[CZ + 1][CYM + 1][CXM + 1];
double Bza[CZ + 1][CYM + 1][CXM + 1];
double Hz[CZ + 1][CYM + 1][CXM + 1];
double clf[CZ + 1][CYM + 1];
double tmp[CZ + 1][CYM + 1];
double Ry[CZ + 1][CYM + 1];
double Ax[CZ + 1][CYM + 1];
double cymh[CYM + 1];
double cyph[CYM + 1];
double cxmh[CXM + 1];
double cxph[CXM + 1];
double czm[CZ + 1];
double czp[CZ + 1];

static void init_array() {
  int i, j, k;

  mui = 2341;
  ch = 42;
  for (i = 0; i <= CZ;) {
    czm[i] = ((double)i + 1) / CXM;
    czp[i] = ((double)i + 2) / CXM;
    i++;
  }
  for (i = 0; i <= CXM;) {
    cxmh[i] = ((double)i + 3) / CXM;
    cxph[i] = ((double)i + 4) / CXM;
    i++;
  }
  for (i = 0; i <= CYM;) {
    cymh[i] = ((double)i + 5) / CXM;
    cyph[i] = ((double)i + 6) / CXM;
    i++;
  }

  for (i = 0; i <= CZ;) {
    for (j = 0; j <= CYM;) {
      Ry[i][j] = ((double)i * j + 10) / CYM;
      Ax[i][j] = ((double)i * j + 11) / CYM;
      for (k = 0; k <= CXM; ) {
        Ex[i][j][k] = ((double)i * (j + 1) + k + 1) / CXM;
        Ey[i][j][k] = ((double)(i - 4) * j + k + 2) / CYM;
        Hz[i][j][k] = ((double)(i + 3) * (j + 7) + k + 3) / CZ;
        k++;
      }
      j++;
    }
    i++;
  }
}


int main(int argc, char** argv) {
  int iz, iy, ix;
  int Cz = CZ;
  int Cym = CYM;
  int Cxm = CXM;

  /* Initialize array. */
  init_array();

  #pragma omp parallel for private (iy, ix) check
  for (iz = 0; iz < Cz; iz++) {
    for (iy = 0; iy < Cym; iy++) {
      for (ix = 0; ix < Cxm; ix++) {
        clf[iz][iy] = Ex[iz][iy][ix] - Ex[iz][iy + 1][ix] + Ey[iz][iy][ix + 1]
            - Ey[iz][iy][ix];
        tmp[iz][iy] = (cymh[iy] / cyph[iy]) * Bza[iz][iy][ix] - (ch / cyph[iy])
            * clf[iz][iy];
        Hz[iz][iy][ix] = (cxmh[ix] / cxph[ix]) * Hz[iz][iy][ix] + (mui
            * czp[iz] / cxph[ix]) * tmp[iz][iy] - (mui * czm[iz] / cxph[ix])
            * Bza[iz][iy][ix];
        Bza[iz][iy][ix] = tmp[iz][iy];
      }
      clf[iz][iy] = Ex[iz][iy][Cxm] - Ex[iz][iy + 1][Cxm] + Ry[iz][iy]
          - Ey[iz][iy][Cxm];
      tmp[iz][iy] = (cymh[iy] / cyph[iy]) * Bza[iz][iy][Cxm] - (ch / cyph[iy])
          * clf[iz][iy];
      Hz[iz][iy][Cxm] = (cxmh[Cxm] / cxph[Cxm]) * Hz[iz][iy][Cxm] + (mui
          * czp[iz] / cxph[Cxm]) * tmp[iz][iy] - (mui * czm[iz] / cxph[Cxm])
          * Bza[iz][iy][Cxm];
      Bza[iz][iy][Cxm] = tmp[iz][iy];
      for (ix = 0; ix < Cxm; ix++) {
        clf[iz][iy] = Ex[iz][Cym][ix] - Ax[iz][ix] + Ey[iz][Cym][ix + 1]
            - Ey[iz][Cym][ix];
        tmp[iz][iy] = (cymh[Cym] / cyph[iy]) * Bza[iz][iy][ix]
            - (ch / cyph[iy]) * clf[iz][iy];
        Hz[iz][Cym][ix] = (cxmh[ix] / cxph[ix]) * Hz[iz][Cym][ix] + (mui
            * czp[iz] / cxph[ix]) * tmp[iz][iy] - (mui * czm[iz] / cxph[ix])
            * Bza[iz][Cym][ix];
        Bza[iz][Cym][ix] = tmp[iz][iy];
      }
      clf[iz][iy] = Ex[iz][Cym][Cxm] - Ax[iz][Cxm] + Ry[iz][Cym]
          - Ey[iz][Cym][Cxm];
      tmp[iz][iy] = (cymh[Cym] / cyph[Cym]) * Bza[iz][Cym][Cxm] - (ch
          / cyph[Cym]) * clf[iz][iy];
      Hz[iz][Cym][Cxm] = (cxmh[Cxm] / cxph[Cxm]) * Hz[iz][Cym][Cxm] + (mui
          * czp[iz] / cxph[Cxm]) * tmp[iz][iy] - (mui * czm[iz] / cxph[Cxm])
          * Bza[iz][Cym][Cxm];
      Bza[iz][Cym][Cxm] = tmp[iz][iy];
    }
  }


 double total = 0;
  for (int iter = 0; iter < Cz; iter++) {
      for (int iter2 = 0; iter2 < Cym; iter2++) {
          for (int iter3 = 0; iter3 < Cxm; iter3++) {
            total+=Bza[iter][iter2][iter3];
            }
        }
  }
  
 printf("total=%f\n",total);



  return 0;
}
