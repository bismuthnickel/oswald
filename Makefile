BINARIES := $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all

all: $(BINARIES)

%: %.c
	gcc $< -o $@
	sudo mv $@ /usr/local/bin/$@