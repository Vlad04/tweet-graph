import os
import csv

if __name__ == "__main__":

    directory =  os.getcwd()

    string = ""
    string += "digraph G {\n"

    try:
        for root,dirs,files in os.walk(directory):
            for file_name in files:
                if file_name.endswith(".csv"):
                    f=open(file_name, 'r')
                    reader = csv.reader(f)
                    for row in reader:
                        print row
                        string += "%s -> %s ;\n" % (row[0],row[1])
                    f.close()
    except:
        pass


    string += "}"

    filename = "graph.dot"
    FILE = open(filename, "w")
    FILE.write(string)
    FILE.close()

    os.system("dot -Tpdf graph.dot -o graph.pdf")
