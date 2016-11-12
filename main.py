import sys
import os
import argparse
import csv

if __name__ == "__main__":

    sys.stderr = open('/dev/null', 'w')
    user_friends = []

    parser = argparse.ArgumentParser()
    parser.add_argument('--username',  type=str,dest="username",help='Username')
    parser.add_argument('--deep',  type=int,dest="deep",help='Deep')
    args = parser.parse_args()

    os.system("python get_friends.py %s" % (args.username))

    filename = args.username + ".csv"
    with open(filename, 'rb') as f:
        reader = csv.reader(f)
        for row in reader:
            user_friends.append(row[1])
    try:
        for friend in user_friends:
            os.system("python get_friends.py %s" % (friend))
    except:
        pass
