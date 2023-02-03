OBJECT_FILES = src/main.o src/queries_handler.o src/data.o src/drivers.o src/query1.o src/query2.o src/query3.o src/cities.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/parser.o src/rides.o src/users.o src/rides_services.o src/dates.o src/interactmode.o src/interactquery1.o src/interactquery2.o src/interactquery3.o src/interactquery4.o src/interactquery5.o src/interactquery6.o src/interactquery7.o src/interactquery8.o src/interactquery9.o src/catalogs.o
OBJECT_FILES2 = tests/main_testes.o tests/compare_outputs.o tests/queries_handler_testes.o src/data.o src/drivers.o src/query1.o src/query2.o src/query3.o src/cities.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/parser.o src/rides.o src/users.o src/rides_services.o src/dates.o src/catalogs.o

CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0)
LIBS = -lm $(shell pkg-config --libs glib-2.0) -lncurses


CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0) 
LIBS = -lm $(shell pkg-config --libs glib-2.0)

TARGET = programa-principal
TARGET2 = programa-testes

all: programa-principal programa-testes

$(TARGET): $(OBJECT_FILES)
	@mkdir -p Resultados
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@ -lncurses

$(TARGET2): $(OBJECT_FILES2)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

tests/%.o: tests/%.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

# $^ prerrequisitos 
# $< primeiro prerrequisito
# $@ nome correspondente


run: $(TARGET)
	./programa-principal

run-programa-principal: $(TARGET) 
	@./programa-principal $(arg1) $(arg2) 

run-programa-testes: $(TARGET) $(TARGET2) 
	@valgrind /usr/bin/time -f "%M" ./programa-testes $(arg1) $(arg2) $(arg3)
#	@cowsay Done! 



clean:
	@rm -rf programa-principal programa-testes src/*.o tests/*.o Resultados 
