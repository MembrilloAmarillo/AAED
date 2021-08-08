CC = clang++

INC_DIR 	= ../TAD/
OBJ_DIR  	= ./obj
BUILD_DIR 	= ./build

escalonada = 0
consultorio = 0

ifeq (${escalonada}, 1)
	INC = $(INC_DIR)/lista_enla_cab.h
	SRC = tad_escalonada.cpp
	OBJ = $(OBJ_DIR)/tad_escalonada.o
	TARGET = ${BUILD_DIR}/tad_escalonada
endif

ifeq (${consultorio}, 1)
	INC = $(INC_DIR)/lista_enla_cab.h ${INC_DIR}/cola.h
	SRC = tad_consultorio.cpp
	OBJ = $(OBJ_DIR)/tad_consultorio.o
	TARGET = ${BUILD_DIR}/tad_consultorio
endif

CXXFLAGS = -I${INC_DIR} -std=c++11 -Wall -Werror -pedantic-errors \
		   -Wextra -Wconversion -Wformat -Wparentheses  


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
