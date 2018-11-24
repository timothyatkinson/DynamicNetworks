INCDIRS=../Math Datasets ../Train ../ ../Datasets ../P-GP2/include
OBJECTS := dataset.c narma.c store_narma.c ../Math/*.c ../Train/*.c ../dnet.c ../util.c
CC=gcc

CFLAGS = 	$(foreach var,$(INCDIRS),-I $(var)) -O2 -lgp2 -lgsl -lgslcblas -lm -g

default:	$(OBJECTS)
		$(CC) $(OBJECTS) $(CFLAGS) -o store_narma_exec

clean:
		rm -f -r store_narma_exec
