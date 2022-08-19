#
#  Compilation flags
#
CFLAGS= -Wall -pedantic -o

image_processing: obj/main.o obj/options.o obj/filters.o obj/files.o inc/structures.h
	gcc ${CFLAGS} image_processing obj/main.o obj/options.o obj/filters.o obj/files.o

obj/main.o: inc/structures.h
	gcc -c ${CFLAGS} obj/main.o src/main.c

obj/options.o: inc/options_prototypes.h inc/structures.h
	gcc -c ${CFLAGS} obj/options.o src/options.c

obj/filters.o: inc/filters_prototypes.h inc/structures.h
	gcc -c ${CFLAGS} obj/filters.o src/filters.c

obj/files.o: inc/files_prototypes.h inc/structures.h
	gcc -c ${CFLAGS} obj/files.o src/files.c

clean:
	rm -f obj/*.o image_processing