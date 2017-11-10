all:
	gcc main.c -o main
	csvtojson 20_Vlad.csv > converted.json
    firebase-import --database_url https://basesdedatos-b5c80.firebaseio.com --path / --json test.json
clean:
	rm -rf main
	rm -rf *.log

distclean:
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
