MPW=~/Programming/mpw/build/bin/mpw

RINCLUDES=~/mpw/Interfaces/RIncludes

PPC_LDFLAGS =-m main -w -c 'RSED' -t 'rsrc'

PPC_LIBRARIES={SharedLibraries}InterfaceLib \
	{SharedLibraries}StdCLib \
	{PPCLibraries}StdCRuntime.o \
	{PPCLibraries}PPCCRuntime.o \
    {Libraries}HyperXLib.o

TOOLBOXFLAGS=-d OLDROUTINENAMES=1 -typecheck relaxed

SOURCES=SelectionMode.c

PPC_OBJECTS=$(SOURCES:%.c=build/obj/%.o)

RFILES=SelectionMode.r
EXECUTABLE=SelectionMode

all: prepass build/$(EXECUTABLE)

prepass:
	mkdir -p build build/obj

build/$(EXECUTABLE): $(PPC_OBJECTS)
	$(MPW) PPCLink $(PPC_LDFLAGS) $(PPC_OBJECTS) $(PPC_LIBRARIES) -o $@; \
	Rez -rd $(RFILES) -o $@ -i $(RINCLUDES) -append

build/obj/%.o : %.c
	./mrc.sh $(TOOLBOXFLAGS) $< -o $@; \

clean:
	rm -rf build
