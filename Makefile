all:
	gcc main.c -o main

clean:
	rm -rf main
	rm -rf *.log

distclean:
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
