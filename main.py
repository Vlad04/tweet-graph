import sys
import os
import argparse
import csv

LIMIT = 3
if __name__ == "__main__":

    user_friends = []
    count = 0 

    parser = argparse.ArgumentParser()
    parser.add_argument('--username',  type=str,dest="username",help='Username')
    parser.add_argument('--deep',  type=int,dest="deep",help='Deep')
    args = parser.parse_args()

    os.system("python get_friends.py %s" % (args.username))

    if args.deep:
        LIMIT = args.deep

    filename = args.username + ".csv"
    with open(filename, 'rb') as f:
        reader = csv.reader(f)
        for row in reader:
            user_friends.append(row[1])
    try:
        for friend in user_friends:
            if count < LIMIT:
                os.system("python get_friends.py %s" % (friend))
                count = count + 1
            else:
                pass
    except:
        pass

    os.system("python graph_generator.py")
