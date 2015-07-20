#ifndef _FUNCIONES_CHROMA_
#define _FUNCIONES_CHROMA_

#ifndef clip
#define clip(a,min,max) a<min? min : ((a>max)? max : a)
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


//#define _HABILITAR_SECCIONES_
#define _HABILITAR_FOR_


/* Imagen Progresiva: Antialising y submuestreo de crominancia */
void chroma_conversion_422to420_progressive(unsigned char *inbuffer,unsigned char *outbuffer,int width,int height,int bitdepth);
/* Imagen Progresiva: Interpolacion de crominancia */
void chroma_conversion_420to422_progressive(unsigned char *inbuffer,unsigned char *outbuffer,int width,int height,int bitdepth);
/* Imagen Entrelazada: Antialising y submuestreo de crominancia */
void chroma_conversion_422to420_interlaced(unsigned char *inbuffer,unsigned char *outbuffer,int width,int height,int bitdepth);
/* Imagen Entrelazada: interpolacion de crominancia */
void chroma_conversion_420to422_interlaced(unsigned char *inbuffer,unsigned char *outbuffer,int width,int height,int bitdepth);

#endif
