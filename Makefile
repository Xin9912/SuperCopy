CC = gcc
CFLAGS = -g -Wall
TARGET ?= spcp

INCDIRS := inc
SRCDIRS := src
OUTDIR := out

INCLUDES := $(patsubst %, -I %,$(INCDIRS))
CFILES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

CFILENODIR := $(notdir $(CFILES))

COBJS := $(patsubst %, obj/%,$(CFILENODIR:.c=.o))
OBJS := $(COBJS)

OUTFILE := $(OUTDIR)/$(TARGET)

VPATH := $(SRCDIRS)

$(OUTFILE) : $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS) : obj/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY:clean
clean:
	rm $(OBJS) $(OUTFILE)