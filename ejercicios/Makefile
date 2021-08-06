CC = clang++

INC_DIR 	= ../TAD/
OBJ_DIR  	= ./obj
BUILD_DIR 	= ./build

INC = $(INC_DIR)/lista_enla_cab.h
SRC = tad_escalonada.cpp
OBJ = $(OBJ_DIR)/tad_escalonada.o

CXXFLAGS = -I${INC_DIR} -std=c++11 -Wall -Werror -pedantic-errors \
		   -Wextra -Wconversion -Wformat -Wparentheses  

TARGET = ${BUILD_DIR}/tad_escalonada

.PHONY : all

all: ${TARGET}

${TARGET} : ${OBJ}
	mkdir -p ${BUILD_DIR}
	${CC} -g -o $@ $^ ${CXXFLAGS} 

${OBJ_DIR}/%.o : %.cpp 
	mkdir -p ${OBJ_DIR}
	${CC} -g -c -o $@ $< ${CXXFLAGS}
	
.PHONY : clean

clean:
	${RM} ${RMFLAGS} ${BUILD_DIR}/* ${OBJ_DIR}/*.o 
