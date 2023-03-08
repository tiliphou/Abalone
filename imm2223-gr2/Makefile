# Makefile générique
# --------------------- Zone modifiable --------------------------

# Compilateur
CC= gcc

# Source C destiné à fournir l'exécutable (ou les exécutables)
MAINSRCS= abalone.c
# MAINSRCS= $(wildcard test_regles*.c)

# Ci-dessous, tous les fichiers *.c à l'exception du ou des précédents, sont 
# des librairies avec entêtes *.h
LIBSRCS= $(filter-out $(MAINSRCS), $(wildcard *.c))

# CPPFLAGS : options propres au préprocesseur
# CFLAGS : options propres au compilateur C
# LDFLAGS : options propres à l'éditeur de liens
# LDLIBS : librairies à intégrer à l'édition de liens

#CPPFLAGS=
CPPFLAGS= -DDEBUG
CFLAGS=`pkg-config --cflags gtk+-3.0` 
LDFLAGS= `pkg-config --libs gtk+-3.0` -lpthread
LDLIBS=  `pkg-config --libs gtk+-3.0` -lpthread

# --------------------- Zone non modifiable --------------------------

EXECS = $(patsubst %.c,%,$(MAINSRCS))
MAINOBJS=$(patsubst %.c,%.o,$(MAINSRCS))
LIBHS=$(LIBSRCS:.c=.h)
LIBOBJS=$(LIBSRCS:.c=.o)

# Règles

.PHONY: clean
.PHONY: test
	
all: $(EXECS) clean

$(MAINOBJS) : %.o :%.c $(LIBHS) $(COMMONHS) $(MAINHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

$(LIBOBJS) : %.o :%.c %.h $(COMMONHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<
	
$(EXECS) : % : %.o $(LIBOBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean: 
	rm *.o

tests:
	make -C test 
	rm *.o *.gcda *.gcno
docs:
	make -C doc 
	