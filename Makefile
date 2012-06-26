CC=gcc
CFLAGS=-g -ansi -Wall
LDFLAGS=-lSDL -lIL -lILUT -lGL -lGLU -lm

# sometimes required
WHOLEARCHIVE=-WL,-whole-archive -lGL -lSDL -lILUT

SJDIR=sojourner
LUAVERSION=5.1

SRCDIR=$(SJDIR)/src
OBJDIR=$(SJDIR)/obj
RELDIR=release
SRCRELDIR=src-release
LIBDIR=$(SJDIR)/lib

RELEASE=sojourner.tgz
SRCRELEASE=sojourner-src.tgz

LIBSRC=$(wildcard $(SRCDIR)/*.c)
SRC=$(LIBSRC) $(wildcard $(SRCDIR)/deps/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
LIB=$(patsubst $(SRCDIR)%.c, $(LIBDIR)%.so, $(LIBSRC))

LUA=$(wildcard *.lua) $(wildcard $(LIBDIR)/*.lua)
LUAC=$(patsubst %.lua, %.luac, $(LUA))

RSRC=*.png

.PHONY: all clean objdirs luac release src-release game sj

all: objdirs $(OBJ) $(LIB)

game:
	lua$(LUAVERSION) ./$(SJDIR)/launcher

sj:
	./$(SJDIR)/sj

release: clean all luac
	mkdir -p $(RELDIR)
	mkdir -p $(RELDIR)/$(LIBDIR)
	cp $(LIBDIR)/*.so $(LIBDIR)/*.luac $(RELDIR)/$(LIBDIR)
	cp *.luac $(RSRC) $(RELDIR)
	tar zcf $(RELEASE) $(RELDIR)
	
src-release: clean
	mkdir -p $(SRCRELDIR)
	mkdir -p $(SRCRELDIR)/$(LIBDIR)
	cp $(LIBDIR)/*.lua $(SRCRELDIR)/$(LIBDIR)
	cp *.lua $(RSRC) Makefile $(SRCRELDIR)
	cp -r $(SRCDIR) $(SRCRELDIR)/$(SRCDIR)
	tar zcf $(SRCRELEASE) $(SRCRELDIR)

%.so: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -shared $(WHOLEARCHIVE)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CC) $(CFLAGS) $< -o $@ -c -fPIC

objdirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/deps
	
luac: $(LUAC)
	
%.luac: %.lua
	luac$(LUAVERSION) -o $@ $<

clean:
	rm -rf $(OBJDIR) $(RELDIR) $(SRCRELDIR) $(RELEASE) $(SRCRELEASE) $(LIBDIR)/*.so $(LUAC)

