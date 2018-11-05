CC = gcc
CFLAGS =
LINKFLAGS = -lm -lpthread
OUTFILE = space_battle
OBJS = space_battle.o entities.o
SRCS = space_battle.c ./lib/entities.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS) $(LINKFLAGS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) $(LINKFLAGS)

clean:
	rm -rf *.o
