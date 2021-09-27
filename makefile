CC=g++
CFLAG=-c
LDFLAGS=-march=x86-64
SRC1=client.cpp mc.cpp
SRC2=server.cpp ms.cpp
OBJ1=$(SRC1:.cpp=.o)
OBJ2=$(SRC2:.cpp=.o)
EXE1=mc
EXE2=ms

all: $(SRC1) $(SRC2) $(EXE1) $(EXE2)

$(EXE1): $(OBJ1)
	$(CC) $(LDFLAGS) $(OBJ1) -o $@

$(EXE2): $(OBJ2)
	$(CC) $(LDFLAGS) $(OBJ2) -o $@

.cpp.o:
	$(CC) $(CFLAG) $< -o $@

clear:
	rm -rf *.o