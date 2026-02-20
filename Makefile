FLAGS = -Iincludes -Wall -Wextra

build:
	gcc src/*.c -o gsh $(FLAGS)
debug:
	gcc src/*.c -o gsh_debug $(FLAGS) -g
run:
	./gsh
clean:
	rm gsh gsh_debug
