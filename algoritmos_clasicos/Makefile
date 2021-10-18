CC        = clang++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic

debug 	 = 0
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

all: ${OUT}

${OUT} : ${OBJ}
	${CC} ${CXXFLAGS} -o ${OUT} $^

test.o : test.cpp ${INC}
	${CC} ${CXXFLAGS} -c -o test.o $<

.PHONY: clean
clean:
	${RM} ${RMFLAGS} ${OBJ} ${OUT}
