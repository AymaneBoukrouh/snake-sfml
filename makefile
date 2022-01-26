CC=g++

SRCDIR=src
INCDIR=include
OBJDIR=obj
BINDIR=bin

OPTS=-O2
CFLAGS=-Wall -Wextra $(OPTS) -I$(INCDIR)
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

CFILES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CFILES))

BINARY=bin/main

all: $(BINDIR) $(OBJDIR) $(BINARY) 

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(SFMLFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $(SFMLFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CC) $(CFLAGS) $(SFMLFLAGS) -c -o $@ $<

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)