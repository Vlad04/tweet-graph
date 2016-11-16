all:
	g++ graph_generator.c -o graph_generator

clean:
	rm -rf graph_generator
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
