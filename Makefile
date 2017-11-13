all:
	gcc main.c -o main
	#for /f %a in ('dir /home/vladimir/tweet-graph *.csv') do for /f "tokens=*" %b in (%a) do echo %b,%a >> all.csv
    
	csvtojson all.csv > converted.json
    firebase-import --database_url https://basesdedatos-b5c80.firebaseio.com --path / --json test.json
clean:
	rm -rf main
	rm -rf *.log

distclean:
	rm -rf *.csv
	rm -rf *.dot
	rm -rf *.pdf
