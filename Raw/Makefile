# anaroot directory

all: MakeTree

ROOTCFLAGS  = $(shell $(CFG_ROOT_BIN)root-config --cflags)
ROOTLIBS    = $(shell $(CFG_ROOT_BIN)root-config --libs)

CFLAGS = -I$(TARTSYS)/include
LFLAGS = -L$(TARTSYS)/lib

GXX = g++

.SUFFIXES: .C .o

.C.o:
	$(GXX) -v $(CFLAGS) $(ROOTCFLAGS) -c $<

MakeTree: MakeTree.C
	$(GXX) -v  $(CFLAGS) $(LFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -lanacore -lanadali -lanabrips -lXMLParser -o $@ MakeTree.C

clean:
	rm -f MakeTree.C~ MakeTree.o MakeTree
