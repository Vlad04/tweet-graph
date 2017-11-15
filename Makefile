all:
	gcc main.c -o main
upload:
	sed -i -e 's/}{/,/g' database.json
	firebase-import --database_url https://basesdedatos-b5c80.firebaseio.com --path / --json database.json
clean:
	rm -rf main
	rm -rf *.log

distclean:
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
