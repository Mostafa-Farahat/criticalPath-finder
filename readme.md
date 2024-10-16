# Finding the critical path
- The critical path in an activity network diagaram is the path that determines the overall time of the project
- Because a newtork diagaram is a Directed Acyclic Graph (DAG) the problem of finding the critical path boiles down to finding the longest path in the graph
- This problem on general graphs is generally not easy to solve but on DAGs it can be solved on linear time

## The algorithm
1. Firstly we obtain a topological sorting of the graph
1. we maintain an array that stores the longest distance ending at vertex `v`, this array is initilized as negative infinity i.e `INT_MIN`
1. secondly, we go over the graph in topological oredring and update the distance at each vertex `v` by doing the following
    1. iterating over the incoming neighbours `u` of the node `v` (the incoming neighbors are stored in a reversed adjacency list `revGraph`)
    1. update the maximmum distance at `v` with `max(Distance[u] + weight(u,v))` where `weight(u,v)` is the value of the weight of the edge going from u to v
    1. if the node `v` has no incoming nodes, then `dist[v]` is set to zero
1. after updating the value of `dis[v]` we record the parent of `v` in order to later reconstruct the critical path itself
1. the critical path is constructed by following the parents of each node starting with the node having the largets distance value
 
## Program input
- The program identifies each node with a unique number
- if mulitple starting nodes exist such as in example 2, a dummy start node with duration(weight) of 0 is added to the program and treated as the single point of start

## input format
- The program first takes a start node, then takes 3 numbers which are the `nodeID`, `dependency`, `dependency duration`
- The program takes one edge at a time
- after an edge is inputed the program waits to for either `f` which means the entire graph has been inputed or any other alphabetical charecter that indicate more tasks will be added
- when the program recives `f` it asks the user for the ID of the ending task and starts executing the algorithm described above

## how to compile
simply compile `criticalPath.cpp` with whatever compiler is available on your machine and link it with the standard libraray (the code has no other dependencies other than the stadard c++ library)

# Clarification
- The nodes in `graph of example2.png` have been mapped to the follwoing numbers in the input
    - s = 1
    - A = 2
    - B = 3
    - C = 4
    - D = 5
    - F = 6
    - E = 7
    - G = 9
    - I = 8
    - J = 11
    - H = 10
    - F = 12