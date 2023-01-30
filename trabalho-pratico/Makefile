OBJECT_FILES = src/main.o src/queries_handler.o src/data.o src/drivers.o src/drivers_services.o src/query1.o src/query2.o src/query3.o src/cities.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/parser.o src/rides.o src/users.o src/users_services.o src/rides_services.o src/dates.o 
OBJECT_FILES2 = tests/main_testes.o tests/compare_outputs.o tests/queries_handler_testes.o src/data.o src/drivers.o src/drivers_services.o src/query1.o src/query2.o src/query3.o src/cities.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/parser.o src/rides.o src/users.o src/users_services.o src/rides_services.o src/dates.o 


CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O0 -g $(shell pkg-config --cflags glib-2.0) 
LIBS = -lm $(shell pkg-config --libs glib-2.0)
TARGET = programa-principal
TARGET2 = programa-testes

all: programa-principal programa-testes

$(TARGET): $(OBJECT_FILES)
	@mkdir -p Resultados
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(TARGET2): $(OBJECT_FILES2)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

tests/%.o: tests/%.c
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

# $^ prerrequisitos 
# $< primeiro prerrequisito
# $@ nome correspondente


run-programa-principal: $(TARGET) 
	@./programa-principal $(arg1) $(arg2) 


run-programa-testes: $(TARGET) $(TARGET2) 
	@valgrind /usr/bin/time -f "%M" ./programa-testes $(arg1) $(arg2) $(arg3)
#	@cowsay Done! 

#	@valgrind --tool=massif ./programa-testes $(arg1) $(arg2) $(arg3)
#	--tool=massif --> ms_print <ficheiro> | less
#	massif-visualizer massif.out.pid
#	Para ver leaks:  --tool=memcheck --leak-check=yes


clean:
	@rm -rf programa-principal programa-testes src/*.o tests/*.o Resultados 


#IDEIAS:
#No futuro talvez fazer um BUILDDIR
#.PHONY: yh   Usa-se para dizer que yh não é um ficheiro