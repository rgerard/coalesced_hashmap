CC=g++

CFLAGS=-Wall

LIBS=-lcppunit

test-runner: CoalescedHashMap.o CoalescedHashMapTest.o TestRunner.o
	$(CC) $(CFLAGS) $(LIBS) *.o -o test-runner

test: test-runner
	./test-runner

clean:
	rm -f test *.o
