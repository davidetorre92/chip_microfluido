CC=gcc
LD=$(CC)
CFLAGS=-c -g -I$(CUDA_HOME)/include -I${NIFTI_HOME}/include -Wall
LDLIBS=-lm
OBJECTS=data_handler.o sectors.o blockmaps.o cells.o

all: chip

chip: $(OBJECTS)
	$(LD) -o $@ $^

test: test_func.o $(OBJECTS)
	$(LD) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o chip test 
