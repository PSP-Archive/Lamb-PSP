#ifndef PSP_DEBUG_H
#define PSP_DEBUG_H

#include <string.h>

#define LOGFILE "ms0:/psphook.log"
#define TEXTUREFILE "ms0:/test.raw"

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef long            LONG;

typedef struct tagBITMAPFILEHEADER {
   //    WORD    bfType;
        DWORD   bfSize;
        DWORD   bfReserved;
        DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD	biSize;
	LONG	biWidth;
	LONG	biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	biXPelsPerMeter;
	LONG	biYPelsPerMeter;
	DWORD	biClrUsed;
	DWORD	biClrImportant;
} BITMAPINFOHEADER;

// Debug Log
int debuglog(const char * string);

// Append Buffer to File
int appendBufferToFile(const char * path, void * buffer, int buflen);

//save raw texture image
int saveRaw(void *data,int width,int height,int format,int swizzle,int lenght);

#endif 