consumer_key = 'u19jYx0ypr6ZZTuZeHB6fL0bY'
consumer_secret = 'lxzZeFZqn5d5qevrqy80oMsn7D9IdarWDL7qbKOWGxKRy8fdeo'
access_token = '358872669-OPquuinXCBmQkAtHZb9CRQ3VPeQhez9zhXnYqt7s'
access_token_secret = '7OddI4d3oRMu07fOL3q3oiqHsK9vBievDgsWFp8c1FLbn'

import csv
import tweepy

data = []
value = []

def write_DB():
    with open('no-related-db.csv', 'w') as fp:
        writer = csv.DictWriter(fp, fieldnames = ["kind_of_node","name","related","hashtag","device","cc_users"])
        writer.writeheader()

        a = csv.writer(fp, delimiter=',')
        a.writerows(data)

def get_friends(user):
    for friend in user.friends():
        value= ["pepople",friend.screen_name,user_name,"NULL","NULL","NULL"]
        data.append(value)

if __name__ == "__main__":

    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)

    api = tweepy.API(auth)

    user = api.get_user('vm_rod25')
    user_name = user.screen_name
    
    get_friends(user)

    stuff = api.user_timeline(screen_name = user_name, count = 100,include_rts = True)
    for tweet in stuff:
        tweet_id = str(tweet.id)
        #in_reply_to_status_id = str(tweet.in_reply_to_status_id)

        tmp = str(tweet.in_reply_to_user_id)
        if tmp:
            in_reply_to_user_id = api.get_user(tmp).screen_name
        device = str(tweet.source)
        if "Web" in device: 
            device = "web"
        if "Android" in device:
            device = "android"
        contributors = str(tweet.contributors)
        hashtags = str(tweet.entities.get('hashtags'))

        string = tweet_id + "," + in_reply_to_user_id + "," + device + "," + contributors + "," + hashtags
   
        print string
    write_DB()
    
    #print (api.get_user(122200230).screen_name)

