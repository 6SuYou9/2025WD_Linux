SRCS:=$(wildcard *.c)
EXES:=$(SRCS:%.c=%)
CC=gcc
all:$(EXES)
%:%.c
	$(CC) $< -o $@ -g
.PHONY:all clean rebuild
clean:
	$(RM) $(EXES)
rebuild:clean all
