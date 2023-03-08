# Makefile générique
# --------------------- Zone modifiable --------------------------

# Compilateur
CC= gcc

# Source C destiné à fournir l'exécutable (ou les exécutables)
MAINSRCS= test_main.c
# MAINSRCS= $(wildcard test_regles*.c)

# Ci-dessous, tous les fichiers *.c à l'exception du ou des précédents, sont 
# des librairies avec entêtes *.h
LIBSRCS= $(filter-out $(MAINSRCS),$(wildcard *.c ../plateau.c ../regles.c ../ihm.c))

# CPPFLAGS : options propres au préprocesseur
# CFLAGS : options propres au compilateur C
# LDFLAGS : options propres à l'éditeur de liens
# LDLIBS : librairies à intégrer à l'édition de liens

#CPPFLAGS=
CPPFLAGS= -DDEBUG
CFLAGS= --coverage
LDFLAGS= -fprofile-arcs -ftest-coverage 
LDLIBS= -fprofile-arcs -ftest-coverage 

# --------------------- Zone non modifiable --------------------------

EXECS = $(patsubst %.c,%,$(MAINSRCS))
MAINOBJS=$(patsubst %.c,%.o,$(MAINSRCS))
LIBHS=$(LIBSRCS:.c=.h)
LIBOBJS=$(LIBSRCS:.c=.o)

# Règles

.PHONY: clean 
.PHONY: run
.PHONY: all
.PHONY: gcov
	
all: $(EXECS) run gcov clean 

$(MAINOBJS) : %.o :%.c $(LIBHS) $(COMMONHS) $(MAINHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

$(LIBOBJS) : %.o :%.c %.h $(COMMONHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<
	
$(EXECS) : % : %.o $(LIBOBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o test_main



clean: 
	rm *.o *.gcda *.gcno

run: test_main 
	-./test_main

gcov: test_main.c
	gcov test_main.c

