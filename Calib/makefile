TARGET = calib

all:$(TARGET)

RIBF132Parameter.o: RIBF132Parameter.cc
	g++ -c RIBF132Parameter.cc `root-config --cflags`	

RIBF132Raw.o: RIBF132Raw.cc
	g++ -c RIBF132Raw.cc `root-config --cflags`

RIBF132CalibOut.o: RIBF132CalibOut.cc
	g++ -c RIBF132CalibOut.cc `root-config --cflags`

calib.o: calib.cc
	g++ -c calib.cc setup.C optics_function.C `root-config --cflags`


$(TARGET): calib.o RIBF132Parameter.o RIBF132Raw.o RIBF132CalibOut.o	
	g++ calib.o RIBF132Parameter.o RIBF132Raw.o RIBF132CalibOut.o -o $@  `root-config --cflags --glibs` -lXMLParser -lXMLIO

clean:
	rm -f $(TARGET) calib.o RIBF132Parameter.o RIBF132Raw.o setup.o optics_function.o RIBF132CalibOut.o


