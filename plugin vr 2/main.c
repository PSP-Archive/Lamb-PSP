#include <pspkernel.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspdisplay_kernel.h>
#include <psputilsforkernel.h>
#include <pspsysmem_kernel.h>
//#include <string.h>
//#include <stdio.h>
#include "hook.h"
#include "debug.h"

/*------------------------------------------------------------------------------*/
/* module info																	*/
/*------------------------------------------------------------------------------*/
PSP_MODULE_INFO( "lamb", PSP_MODULE_KERNEL, 1, 1 );

static SceUID MainThreadID = -1;

#define MAX_THREAD	64


static int MainThread( SceSize args, void *argp )
{
	hookDisplay();

	sceKernelDcacheWritebackInvalidateAll();
	sceKernelIcacheInvalidateAll();

	unsigned int paddata_old = 0;
	SceCtrlData paddata;
	
	sceKernelDelayThread(10000);

	
	while(1)
	{
		sceCtrlPeekBufferPositive(&paddata, 1);
		
		if(paddata.Buttons != paddata_old)
		{
			//press "note" button and magick begin
			if(paddata.Buttons & PSP_CTRL_NOTE)
			{
				//can parse command list
				can_parse = 1;
				
			}
		}
		paddata_old = paddata.Buttons;
		sceKernelDelayThread(10000);
	}

	return( 0 );
}

/*------------------------------------------------------------------------------*/
/* module_start																	*/
/*------------------------------------------------------------------------------*/
#define GET_JUMP_TARGET(x)		(0x80000000|(((x)&0x03FFFFFF)<<2))

int module_start( SceSize args, void *argp )
{
	MainThreadID = sceKernelCreateThread( "DrakonTest", MainThread, 16, 0x800, 0, NULL );
	if ( MainThreadID >= 0 )
	{
		sceKernelStartThread( MainThreadID, args, argp );
	}
	
	return( 0 );
}

/*------------------------------------------------------------------------------*/
/* module_stop																	*/
/*------------------------------------------------------------------------------*/
int module_stop( SceSize args, void *argp )
{

	if ( MainThreadID    >= 0 ){ sceKernelDeleteThread( MainThreadID ); }

	return( 0 );
}
