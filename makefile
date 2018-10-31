CC=gcc
CFLAGS=-g -I.
DEPS = ds.h util.h basicc.h adt.h tree.h
OBJ = ds.o \
      adt.o\
      heaps.o \
      lists.o \
      test.o    \
      tree.o\
      util.o\
      basicc.o\
      dp.o\
      arrays.o\
      graphs.o\
      union_find.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean: 
	rm -rf $(OBJ) 
	rm -rf test
	rm -rf core*

tags:
	ctags -f tags -R .
