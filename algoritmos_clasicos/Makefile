CC        = g++
CXXFLAGS += -Wall -Wextra -pedantic

debug = 0
optimiza = 0

ifeq ($(debug),1)
	CXXFLAGS += -g
endif

ifeq ($(optimiza),2)
	CXXFLAGS += -O2
endif

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
