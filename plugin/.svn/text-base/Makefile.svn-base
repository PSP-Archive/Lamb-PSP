TARGET  = lamb
OBJS    = main.o exports.o debug.o hook.o hook_display.o
LIBS    = -lpspctrl_driver -lpsppower_driver -lpspdisplay_driver
CFLAGS  = -O2 -G0 -Wall -fno-builtin-printf -DRELEASE
#CFLAGS  = -O2 -G0 -Wall -fno-builtin-printf
ASFLAGS = $(CFLAGS)

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
