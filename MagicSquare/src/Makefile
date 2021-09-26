CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

acc: $(OBJS)
	$(CC) -o ../result/res $(OBJS) $(LDFLAGS)

$(OBJS): magicsquare.h

clean:
	rm -f *.o *~ tmp* res

.PHONY: clean
