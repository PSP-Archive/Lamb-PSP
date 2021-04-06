#include <pspiofilemgr.h>
#include "debug.h"

int debuglog(const char * string)
{
  // Append Data
  return appendBufferToFile(LOGFILE, (void*)string, strlen(string));
}

int appendBufferToFile(const char * path, void * buffer, int buflen)
{
  // Written Bytes
  int written = 0;
 
  // Open File for Appending
  SceUID file = sceIoOpen(path, PSP_O_APPEND | PSP_O_CREAT | PSP_O_WRONLY, 0777);
 
  // Opened File
  if(file >= 0)
  {
    // Write Buffer
    written = sceIoWrite(file, buffer, buflen);
   
    // Close File
    sceIoClose(file);
  }
 
  // Return Written Bytes
  return written;
}

int saveRaw(void *data,int width,int height,int format,int swizzle,int lenght)
{
	int written = 0;
	
	//unsigned short p = (byte1 << 8) | byte2;
	
	// Open File
	SceUID file = sceIoOpen(TEXTUREFILE, PSP_O_CREAT | PSP_O_WRONLY, 0777);
	// Opened File
	if(file >= 0)
	{
	
		//my small header...
		written = sceIoWrite(file, &width, sizeof(int));
		written = sceIoWrite(file, &height, sizeof(int));
		written = sceIoWrite(file, &format, sizeof(int));
		written = sceIoWrite(file, &swizzle, sizeof(int));
		
		//image raw data
		//int buflen = (width * height) * textureFormat;
		//lenght
		//written = sceIoWrite(file, data, buflen);
		written = sceIoWrite(file, data, lenght);
		
		// Close File
		sceIoClose(file);
	}
	
	return written;
}