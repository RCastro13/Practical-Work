all: run

run: main arq1.txt
	./main
	python fractal.py

main: main.c
	gcc -o main main.c

clean:
	rm -f main arq1.txt