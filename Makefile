SOURCES=SelectionMode.c A5WorldUtils.c
RFILES=SelectionMode.r
RNAME=SelectionMode
RESID=7000
RESTYPE=XCMD

BIN_DIR=~/Programming/mpw/build/bin
LD=$(BIN_DIR)/mpw link
REZ=$(BIN_DIR)/mpw Rez
CC=./sc.sh
RINCLUDES=~/mpw/Interfaces/RIncludes

LDFLAGS=-w -t 'rsrc' -c 'RSED' -rt $(RESTYPE)=$(RESID) \
	-m MAIN -sg $(RNAME)

LIBRARIES={Libraries}HyperXLib.o \
	{Libraries}Interface.o \
    //{Libraries}MathLib.o \
	//{CLibraries}StdCLib.o \
	//{Libraries}MacRuntime.o \
	//{Libraries}IntEnv.o

TOOLBOXFLAGS=-d OLDROUTINENAMES=1 -typecheck relaxed

OBJECTS=$(SOURCES:%.c=build/obj/%.o)

all: prepass build/$(RNAME).rsrc

prepass:
	mkdir -p build build/obj

build/$(RNAME).rsrc: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@
	$(REZ) -rd $(RFILES) -o $@ -i $(RINCLUDES) -append

build/obj/%.o : %.c
	$(CC) $(TOOLBOXFLAGS) $< -o $@

clean:
	rm -rf build
