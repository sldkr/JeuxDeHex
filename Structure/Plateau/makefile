NAME=Plateau
FLAG= -Wall #-std=c99 -ansi

F_BIN=./
F_EXEC=./


COORDONNEE=../Coordonnee/Coordonnee
LISTE=../Liste/Liste


all: structure.o test_structure.o
	make structure.o -C ../Coordonnee
	make structure.o -C ../Liste
	gcc -o TEST_${NAME} ${COORDONNEE}.o ${LISTE}.o ${F_BIN}${NAME}.o ${F_BIN}test_${NAME}.o ${FLAG}


structure.o: ${NAME}.h ${COORDONNEE}.h ${LISTE}.h

	gcc -o ${F_BIN}${NAME}.o -c ${NAME}.c ${FLAG}

test_structure.o: ${NAME}.h
	gcc -o ${F_BIN}test_${NAME}.o -c test_${NAME}.c ${FLAG}

clean:
	rm -f ${F_BIN}*.o
	rm -f ${F_EXEC}TEST_${NAME}

run: all
	valgrind ${F_EXEC}TEST_${NAME}
	make clean
