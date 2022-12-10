OBJECT_FILES = src/main.o src/parser.o src/drivers.o src/query1.o src/query2.o src/query3.o src/query4.o src/rides.o src/users.o src/dates.o

CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O3 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0)
TARGET = programa-principal

$(TARGET): $(OBJECT_FILES)
	@mkdir -p Resultados
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

# $^ prerrequisitos 
# $@ nome correspondente

run: $(TARGET)
	./programa-principal

clean:
	rm -rf programa-principal src/*.o Resultados


#IDEIAS:
#No futuro talvez fazer um BUILDDIR
#.PHONY: yh   Usa-se para dizer que yh não é um ficheiro