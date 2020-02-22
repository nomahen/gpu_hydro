#### set USEICC to 0 if you want gcc compiler options, else set to 1 to use icc
########  gcc generally used for debugging with -g option so we can use gdb
USEICC = 0

ifeq ($(USEICC),0)
CC       = gcc
CCFLAGS  = -O0 -g -ggdb -fsanitize=address -fno-omit-frame-pointer
endif

EXTRALIBS = -lm

CC_COMPILE  = $(CC) $(CCFLAGS) -c
CC_LOAD     = $(CC) $(CCFLAGS)

.c.o:
	$(CC_COMPILE) $*.c

EXE = do_good
all: $(EXE)

OBJS = \
bc.o cfl.o grid_init.o hll.o main.o primconsflux.o sim_init.o sim_initBlock.o \
soln_FOG.o soln_ReconEvolveAvg.o soln_getFlux.o soln_reconstruct.o soln_update.o \
io.o

INCS = \
decs.h defs.h config.h


$(OBJS) : $(INCS) makefile

$(EXE): $(OBJS) $(INCS) makefile
	$(CC_LOAD) $(OBJS) $(EXTRALIBS) -o $(EXE)

clean:
	/bin/rm -f *.o *.il
	/bin/rm -f $(EXE) 
