#------------------------------------------------------------------------
# 	Makefile
#   António Almeida
#	64960
#    almeid@ua.pt
#------------------------------------------------------------------------
#As minhas sources...
SRC=main.c myf.c pcolor.c keypress.c dispf.c entrega1.c entrega2.c
PROG=64960_tpc6
HEADERS=myf.h prototypes.h

#------------------------------------------------------------------------
## Daqui para baixo nao deve ser preciso mexer com frequencia
#------------------------------------------------------------------------
###definicoes (macros)
CC=gcc
CFLAGS=-Wall
OBJ=$(SRC:.c=.o)
LIBS= -lm
INCLUDE=-I.
DOXYFILE=Doxyfile
#for opencv
#CFLAGS+=`pkg-config --cflags opencv`
#LIBS+=`pkg-config --libs opencv`

#------------------------------------------------------------------------
#### Targets
$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

clean:
	rm -f $(PROG)

allclean: clean
	rm -f $(OBJ) *.bak

doc:
	@ if ! [ -f $(DOXYFILE) ] ; then \
		doxygen -g $(DOXYFILE) ; \
		sed -i 's/^PROJECT_NAME.*$$/PROJECT_NAME      = $(PROG)/'       $(DOXYFILE) ;\
		sed -i 's/^GENERATE_LATEX.*$$/GENERATE_LATEX      = NO/'        $(DOXYFILE) ;\
		sed -i 's/^HAVE_DOT.*$$/HAVE_DOT      = YES/'                   $(DOXYFILE) ;\
		sed -i 's/^SOURCE_BROWSER.*$$/SOURCE_BROWSER      = YES/'       $(DOXYFILE) ;\
		doxygen $(DOXYFILE) ; \
	else \
		doxygen $(DOXYFILE); \
	fi

tags: $(SRC) $(HEADERS)
	ctags $(SRC) $(HEADERS)
#------------------------------------------------------------------------
#Generate a list of functions (useful for prototypes)
#notice the $$ to escape the Make interpretation of $
proto prototypes.h: $(SRC)
	@echo "Rebuild prototypes.h"
	@echo /*File generated automatically. Do not edit*/ > prototypes.h
	@ctags -x --c-kinds=f $(SRC) | grep -v main | sed 's/\/\/.*$$//' |\
	sed 's/{.*//' | \
	awk '{for(n=5; n<=NF; n++) printf("%s ", $$n) ; printf(";\n");}' >> prototypes.h

depend:
	@#redirect output to /dev/null due to some bugs in makedepend :-(
	makedepend -Y $(SRC) 2> /dev/null
#------------------------------------------------------------------------
# DO NOT DELETE

main.o: myf.h keypress.h pcolor.h prototypes.h
myf.o: myf.h keypress.h pcolor.h prototypes.h
pcolor.o: pcolor.h
keypress.o: keypress.h
dispf.o: myf.h keypress.h pcolor.h prototypes.h
entrega1.o: myf.h keypress.h pcolor.h prototypes.h
entrega2.o: myf.h keypress.h pcolor.h prototypes.h
