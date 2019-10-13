.RECIPEPREFIX +=
CC = g++
CFLAGS = -Wall -lm -lrt -lwiringPi -lpthread

PROG = bin/*
OBJS = obj/*

default:
    mkdir -p bin obj
    $(CC) $(CFLAGS) -c src/CurrentTime.c -o obj/CurrentTime
    $(CC) $(CFLAGS) -c src/main.c -o obj/Main
    $(CC) $(CFLAGS) obj/CurrentTime obj/Main -o bin/Main	

run:
    sudo ./bin/Main

clean:
    rm $(PROG) $(OBJS)
