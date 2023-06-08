CLFAGS = -g -Wall
CC = g++

PROJECT = main

REF1 = GPIO



$(PROJECT): $(PROJECT).o $(REF1).o
	$(CC) $(PROJECT).o $(REF1).o -o $(PROJECT)

$(PROJECT).o: $(PROJECT).cpp $(REF1).h
	$(CC) $(CFLAGS) -c $(PROJECT).cpp 

$(REF1).o: $(REF1).cpp $(REF1).h 
	$(CC) $(CFLAGS) -c $(REF1).cpp

clean:
	rm -f *.o $(PROJECT)
