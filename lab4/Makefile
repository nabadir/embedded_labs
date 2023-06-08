CLFAGS = -O
CC = g++

WiimoteAccel: main.o WiimoteAccel.o ZedBoard.o
	$(CC) $(CFLAGS) -o WiimoteAccel main.o WiimoteAccel.o ZedBoard.o

main.o: main.cpp ZedBoard.cpp
	$(CC) $(CFLAGS) -c main.cpp ZedBoard.cpp 


WiimoteAccel.o: WiimoteAccel.cpp ZedBoard.cpp
	$(CC) $(CFLAGS) -c WiimoteAccel.cpp ZedBoard.cpp

ZedBoard.o: ZedBoard.cpp
	$(CC) $(CFLAGS) -c ZedBoard.cpp

clean:
	rm -f core *.o WiimoteAccel
