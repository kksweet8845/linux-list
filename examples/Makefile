CC = gcc
CFLAGS = -I./include
CFLAGS += -Wall -W -Og -g

M/ = merge-sort/

merge-sort.o: $(M/)merge-sort.c $(M/)merge-sort.h
	$(CC) $(CFLAGS) -c $(M/)merge-sort.c $(M/)merge-sort.h

quick-sort.o: quick-sort.c quick-sort.h
	$(CC) $(CFLAGS) -c quick-sort.c quick-sort.h

insert-sort.o: insert-sort.c insert-sort.h
	$(CC) $(CFLAGS) -c insert-sort.c insert-sort.h

run: run.c merge-sort.o quick-sort.o insert-sort.o
	$(CC) $(CFLAGS) -o run run.c merge-sort.o quick-sort.o insert-sort.o

test-merge: merge-sort.o
	$(CC) $(CFLAGS) -o test-merge.out $(M/)unit-test/test-merge.c merge-sort.o

test-part: merge-sort.o
	$(CC) $(CFLAGS) -o test-part.out $(M/)unit-test/test-partition.c merge-sort.o

ana-merge: merge-sort.o
	$(CC) $(CFLAGS) -o ana-merge.out $(M/)ana-merge.c merge-sort.o

clean:
	rm *.o
	rm *.out