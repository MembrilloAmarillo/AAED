CC     = clang++
CFLAGS = -Wall -Wextra -pedantic

SRCDIR = .
SRC    = test.cpp
INC    = algoritmos.h cronometro.h

OBJ    = test.o

OUT = test

.SUFFIXES: .c .o
.c.o:
	${CC} -c $< ${CLFAGS} $(CPPFLAGS} -o $@

${OUT} : ${OBJ}
	${CC} -o ${OUT} ${CFLAGS} ${CPPFLAGS} ${OBJ}

.PHONY: clean
clean:
	${RM} ${RMFLAGS} ${OBJ} ${OUT}
