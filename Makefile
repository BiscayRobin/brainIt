MAKEFLAGS	+= -j

TARGET		= brainIt

ifeq ($(shell $(CC) -v 2>&1 | grep -c "clang version"), 1)
COMPILER := clang
else
COMPILER := gcc
endif
export COMPILER

CC			= $(COMPILER)
CCFLAGS		= -std=c17 -ggdb -Wall -Wextra -pedantic -Os -O2

SRCDIR		= src
OBJDIR		= obj
BINDIR		= bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INSTALLDIR = /usr/local/bin

RM = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $(CCFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: install
install: $(BINDIR)/$(TARGET)
	cp $(BINDIR)/$(TARGET) $(INSTALLDIR)/

.PHONY: uninstall
uninstall:
	$(RM) $(INSTALLDIR)/$(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJECTS)

.PHONY: remove
remove: clean
	$(RM) $(BINDIR)/$(TARGET)
