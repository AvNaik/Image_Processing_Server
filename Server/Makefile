Ci = gcc
CFLAGS = -O2 -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: s

s: s.c csapp.o image_helper.o q.o
	$(CC) $(CFLAGS) -o s s.c csapp.o image_helper.o q.o $(LIB)

q.o: q.c
	$(CC) $(CFLAGS) -c q.c

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

image_helper.o: image_helper.c
	$(CC) $(CFLAGS) -c image_helper.c

clean:
	rm -f *.o s *~

