/*------------------------------------------------------------------------------*/
/* RemoteJoyLite																*/
/*------------------------------------------------------------------------------*/
#include <pspkernel.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspdisplay_kernel.h>
#include <psputilsforkernel.h>
#include <pspsysmem_kernel.h>
#include <string.h>
#include <stdio.h>
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

	//scePowerTick( 0 );
	
	unsigned int paddata_old = 0;
	char file[64], flag = 0, size = 0;
	int x, y, fd, count = 0, thread_count_start, thread_count_now;
	SceUID thread_buf_start[MAX_THREAD], thread_buf_now[MAX_THREAD], myThread = sceKernelGetThreadId();
	SceCtrlData paddata;
	
	sceKernelDelayThread(10000);

	sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, thread_buf_start, MAX_THREAD, &thread_count_start);

	
	while(1)
	{
		sceCtrlPeekBufferPositive(&paddata, 1);
		
		if(paddata.Buttons != paddata_old)
		{
			//press "note" button and magick begin
			if(paddata.Buttons & PSP_CTRL_NOTE)
			{
		
				// IdList Now
				sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, thread_buf_now, MAX_THREAD, &thread_count_now);

				//hold all threads for a moment
				for(x = 0; x < thread_count_now; x++)
				{
					// thread id match 0 or 1
					unsigned char match = 0;
					SceUID tmp_thid = thread_buf_now[x];
					for(y = 0; y < thread_count_start; y++)
					{
						if((tmp_thid == thread_buf_start[y]) || (tmp_thid == myThread))
						{
							match = 1;
							y = thread_count_start;
						}
					}
					if(thread_count_start == 0) match = 1;
					if(match == 0)
					{
						sceKernelSuspendThread(tmp_thid);
					}

				}
					
				
				//can parse command list
				can_parse = 1;
				
				//resume all threads
				for(x = 0; x < thread_count_now; x++)
				{
					// thread id match 0 or 1
					unsigned char match = 0;
					SceUID tmp_thid = thread_buf_now[x];
					for(y = 0; y < thread_count_start; y++)
					{
						if((tmp_thid == thread_buf_start[y]) || (tmp_thid == myThread))
						{
							match = 1;
							y = thread_count_start;
						}
					}
					if(thread_count_start == 0) match = 1;
					if(match == 0)
					{
						sceKernelResumeThread(tmp_thid);
					}
				}
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
