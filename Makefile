all: cal treetest

%.o: %.c
	gcc -c $<

cal: main.o icstree.o ics.o
	gcc -o cal main.o icstree.o ics.o

treetest: treetest.o icstree.o
	gcc -o treetest treetest.o icstree.o



clean:
	rm treetest.o icstree.o main.o cal treetest

.PHONY: clean all