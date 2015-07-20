CC = gcc
MPICC = mpicc
MPIRUN = mpirun
MPECC = mpecc
CFLAGS = -O3
LDFLAGS= -lm
SERIALORI = heat2DOriginal
SERIAL = heat2D
PARALLEL = heat2D-mpi
PINGPONG = ping-pong
HELLO = hello

all: clean $(SERIAL) $(PARALLEL)

$(SERIAL):  
	$(CC) $(CFLAGS) $(SERIAL).c -o $(SERIAL).out $(LDFLAGS)
	$(CC) $(CFLAGS) $(SERIALORI).c -o $(SERIALORI).out $(LDFLAGS)

$(PARALLEL): 
	$(MPICC) $(CFLAGS) $(PARALLEL).c -o $@.out $(LDFLAGS)

test:  $(SERIAL) $(PARALLEL)
	@echo
	@echo "Running:"
	@./$(SERIAL).out -s 6 -f serial.dat
	@./$(SERIALORI).out -s 6 -f serialOri.dat
	@mpirun -np 3 ./$(PARALLEL).out -s 6 -f parallel.dat 	
	@echo 
	@echo -n "Checking results with original: "
	@diff -qs serialOri.dat parallel.dat
	@echo -n "Checking results with alternative: "
	@diff -qs serial.dat parallel.dat

$(PINGPONG):
	#$(MPECC) -mpilog -g -pg $(PINGPONG).c -o $@.out -lmpe
	$(MPICC) -g -pg $(PINGPONG).c -o $@.out 

$(HELLO):
	$(MPICC) -g -pg $(HELLO).c -o $@.out 

clean:
	rm -f $(SERIAL) $(PARALLEL)  *.o


