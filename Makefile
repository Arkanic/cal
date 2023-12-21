all: cal

%.o: %.c
	gcc -c $<

cal: main.o icstree.o
	gcc -o cal main.o icstree.o

treetest: treetest.o icstree.o
	gcc -o treetest treetest.o icstree.o


.PHONY: clean
clean:
	rm treetest.o icstree.o main.o cal treetest
