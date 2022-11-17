OBJECT_FILES = $(wildcard src/%.o)

CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` -O3 -Iincludes
LDFLAGS = `pkg-config --libs glib-2.0`

all: $(OBJECT_FILES)
	mkdir -p Resultados
	${CC} src/main.c $(OBJECT_FILES) $(CFLAGS) -o programa-principal $(LDFLAGS)

src/%.o: src/%.c
	${CC} -c $^ $(CFLAGS) -o $@ $(LDFLAGS)

# $^ prerrequisitos 
# $@ nome correspondente


run: all
	./progama-principal

clean:
	rm -rf programa-principal src/*.o Resultados


#IDEIAS:
#No futuro talvez fazer um BUILDDIR
#.PHONY: yh   Usa-se para dizer que yh não é um ficheiro