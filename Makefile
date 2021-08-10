MAKEFLAGS	+= -j

TARGET		= brainIt

CC			= clang
CCFLAGS		= -std=c17 -ggdb -Wall -Wextra -pedantic -Os -O2

SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(CCFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: remove
remove: clean
	$(RM) $(BINDIR)/$(TARGET)
