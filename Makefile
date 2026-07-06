.PHONY: all run test defconf

CC ?= gcc

SRCS = 
INCS_DIR = 

LDFLAGS ?= -lSDL3 -lm
CFLAGS ?= -Wall -O2

all: defconf build run

defconf:
	@echo "Default config is create"

build:
	@echo "Binary: [path]"

run:
	@echo "Running..."

test:
	@echo "Testing..."
