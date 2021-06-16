CC     = g++
CXXFLAGS = -Wall -Wextra -pedantic

SRCDIR = .
SRC    = test.cpp
INC    = algoritmos.h cronometro.h

OBJ    = test.o

OUT = test

${OUT} : ${OBJ}
	${CC} -o ${OUT} ${CXXFLAGS} ${OBJ}

test.o : algoritmos.h cronometro.h

.PHONY: clean
clean:
	${RM} ${RMFLAGS} ${OBJ} ${OUT}
