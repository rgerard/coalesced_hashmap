CC=g++
CFLAGS=-Wall
LIBS=-lcppunit

lib: CoalescedHashMap.o

test-lib: lib CoalescedHashMapTest.o TestRunner.o

test: test-lib
	$(CC) $(CFLAGS) $(LIBS) *.o -o test

clean:
	rm -f main main.o hello_fn.o