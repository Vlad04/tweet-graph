consumer_key = 'u19jYx0ypr6ZZTuZeHB6fL0bY'
consumer_secret = 'lxzZeFZqn5d5qevrqy80oMsn7D9IdarWDL7qbKOWGxKRy8fdeo'
access_token = '358872669-OPquuinXCBmQkAtHZb9CRQ3VPeQhez9zhXnYqt7s'
access_token_secret = '7OddI4d3oRMu07fOL3q3oiqHsK9vBievDgsWFp8c1FLbn'

import csv
import tweepy
import sys

friends = []


def get_friends(name):
    user = api.get_user(name)
    user_name = user.screen_name
    friends = []
    for friend in user.friends():
        friends.append(friend.screen_name)
    return user_name,friends

if __name__ == "__main__":

    user = sys.argv[1]

    string = ""
    string += "digraph G {\n"

    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)

    api = tweepy.API(auth)
    #print api.rate_limit_status()

    tweepy.Cursor(api.friends, count = 200)

    user_name,friends = get_friends(user)

    for friend in friends:
        string += "%s -> %s \n" % (user_name,friend)
        
    string += "}"

    print string

    filename = user + ".dot"
    FILE = open(filename, "w")
    FILE.write(string)
    FILE.close()

    filename = user + ".csv"
    with open(filename, "wb") as f:
        writer = csv.writer(f)
        for friend in friends:
            tmp = []
            tmp.append(user_name)
            tmp.append(friend)
            writer.writerow(tmp)



