CFLAGS	= -Wall -Wpedantic -Werror -g -std=c99
CC		= gcc

TESTDIR = tests/
OBJDIR	= obj/

LIBSRCS = $(wildcard *.c)
LIBOBJS = $(addprefix $(OBJDIR), $(LIBSRCS:.c=.o))
LIBHS	= $(LIBSRCS:.c=.h)
TESTSRCS = $(addprefix $(TESTDIR), $(addprefix test_, $(LIBSRCS))) 
TESTTARGETS = $(basename $(TESTSRCS))

all: $(TESTTARGETS)

$(TESTTARGETS): $(TESTSRCS) $(LIBOBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBOBJS): $(LIBSRCS) $(LIBHS)
	$(CC) $(CFLAGS) -c $(LIBSRCS) -o $@

$(LIBOBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)


clean:
	rm -rf $(OBJDIR) $(basename $(TESTSRCS))
