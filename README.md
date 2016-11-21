# tweet-graph

This project analyse the social netwok of a user by: 

    # Plot conections:
        Plot a map with all the conections of user 
            (acording to certain level)

                [1]
                / \
            [2]     [3]
           / \      / \
        [4]  [5]  [6] [5]

    # Most Valuable conection: 
        Find the friends with more conections
    
    # Balance network
        Propouse a solution of conections to add in order to
        balance the three of user`

    # Shortest path <user a> <user b>
        Find the shortest path between 2 users ( if exist )

INSTRUCTIONS


1) Gather user information from tweeter API

    python main.py --user vm_rod25

2) Generate a graph newtwork: 

    python graph_generator.py

    ( Take into consideration that you need to have 
    just the csv that you want to plot )

        
    You can watch the graph with: 

        open graph.pdf

    The DOT code will be plotted in: 

        graph.dot

[BUDILING]

    You can build the C code that will analyse the information 

    $ make

Then you can execute the main as : 

    ./main -p : Print graph network 

    ./main -v : Verbose 

    ./main -s : Sort the users by number of friends



