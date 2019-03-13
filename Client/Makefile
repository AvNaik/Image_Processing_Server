CC = gcc
CFLAGS = -O2 -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: c

c: c.c csapp.o image_helper.o
	$(CC) $(CFLAGS) -o c c.c csapp.o image_helper.o $(LIB)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

image_helper.o: image_helper.c
	$(CC) $(CFLAGS) -c image_helper.c

clean:
	rm -f *.o c *~

