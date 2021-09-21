CC = gcc
CFLAGS = -g -Wall
TARGET ?= spcp

INCDIRS := inc
SRCDIRS := src
OUTDIR := out
OBJDIR := obj

INCLUDES := $(patsubst %, -I %,$(INCDIRS))
CFILES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

CFILENODIR := $(notdir $(CFILES))

COBJS := $(patsubst %, $(OBJDIR)/%,$(CFILENODIR:.c=.o))
OBJS := $(COBJS)

OUTFILE := $(OUTDIR)/$(TARGET)

VPATH := $(SRCDIRS)

$(OUTFILE) : $(OBJDIR) $(OBJS) 
	$(CC) -o $@ $(OBJS)

$(OBJS) : $(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR):
	mkdir obj out

.PHONY:clean
clean:
	rm $(OBJS) $(OUTFILE)