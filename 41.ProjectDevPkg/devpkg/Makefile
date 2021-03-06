SRC_DIR=./src
LCTHW_DIR=$(SRC_DIR)/lcthw
BUILD_DIR=./build
TESTS_DIR=./tests

PREFIX?=/usr/local
CC=gcc
INCLUDES=-I$(SRC_DIR) -I$(PREFIX)/apr/include/apr-1 
CFLAGS=-g -std=c99 -O2 -Wall -Wextra -Werror -Wno-unused-function \
		  -Wno-unused-parameter -Wno-address -rdynamic -DNDEBUG -Du_char="unsigned char"\
		  $(INCLUDES) $(OPTFLAGS)

LIBS=-L$(PREFIX)/apr/lib -lapr-1 -pthread -laprutil-1 $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TARGET=$(BUILD_DIR)/devpkg

all: clean target

target: build $(TARGET) ctags_install

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

install: all
	install -d$(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

ctags_install:
	$(CC) -M $(INCLUDES) $(SOURCES) > .includes
	ctags_with_dep.sh .includes

build:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) || true
	rm $(OBJECTS) || true
	rm $(TARGET) || true
