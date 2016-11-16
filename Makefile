all:
	gcc main.c -o main

clean:
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
	rm -rf main
