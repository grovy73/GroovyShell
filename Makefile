build:
	gcc src/*.c -o gsh -Iincludes
run:
	./gsh
clean:
	rm gsh
