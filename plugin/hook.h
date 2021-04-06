#ifndef _HOOK_H_
#define _HOOK_H_
/*------------------------------------------------------------------------------*/
/* hook																			*/
/*------------------------------------------------------------------------------*/
#include "hook_display.h"


/*------------------------------------------------------------------------------*/
/* prototype																	*/
/*------------------------------------------------------------------------------*/
extern void *HookNidAddress( SceModule *mod, char *libname, u32 nid );
extern void *HookSyscallAddress( void *addr );
extern void HookFuncSetting( void *addr, void *entry );

#endif	// _HOOK_H_
