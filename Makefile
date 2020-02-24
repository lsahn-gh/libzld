CC=cc
RM=rm -f

all:
	make -C src
	make -C tools

clean:
	make -C src clean
	make -C tools clean
