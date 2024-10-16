#include<bits/stdc++.h>
using namespace std;

class comparetor{
    public:
    bool operator () ( pair<int,int> node1, pair<int,int> node2){
        return node1.second > node2.second;
    }
};

vector<vector<pair<int,int>>> graph (1000);//pair<nodeID, weight>
vector<vector<int>> revGraph(1000);//revGraph[a][b] --> the node a is pointed to BY b

vector<int> dist(1000, INT_MIN); //longest distance yet to each node from root
bool visited[1000];
vector<int> parent (1000, -1);

//helper to add a node to graph and revGraph
void addNode(int u, int v, int weight){
    graph[u].push_back({v,weight}); //the actual graph where u points to v
    revGraph[v].push_back(u); //revGraph maintains a list of incoming neighbors of v i.e peope pointin TO v
}

//helper to retrive certain pair correponding to a certain edge
pair<int,int> getEdge(int u, int v){
    for(auto child : graph[u]){
        if(child.first == v){
            return child;
        }
    }
    return {-1,-1};
}

//topological sorting of graph
stack<int> s;
bool topoVisited[1000];
void topoSort(int v){
    for(auto child : graph[v]){
        if(topoVisited[child.first]){
            continue;
        }
        topoVisited[v] = 1;
        topoSort(child.first);
    }
    s.push(v);
}

//critical path
int longestPath(int v){
    while(!s.empty()){
        int current = s.top();
        s.pop();
        if(revGraph[current].empty()){//no incoming neighbours
            dist[current]=0;
        }else{
            int nodeDistance = INT_MIN;
            int incomingNode = INT_MIN;
            for(auto incoming: revGraph[current] ){
                if(dist[incoming] + getEdge(incoming, current).second > nodeDistance){
                    nodeDistance = dist[incoming] + getEdge(incoming,current).second;
                    incomingNode = incoming;
                }
            }
            parent[current] = incomingNode;
            dist[current] = nodeDistance;
        }
    }
    return dist[v];
}

//to print the critical path itself
vector<int> getCriticalPath(){
    //get v with larget dist
    vector<int> result;
    int v = max_element(dist.begin(),dist.end()) - dist.begin();

    while(parent[v] != -1){
        result.push_back(v);
        v = parent[v];
    }
    result.push_back(v);//to place root of path as well
    reverse(result.begin(), result.end());
    return result;

}

int main(){


    char status = 'c';
    int startID;

    cout<<"enter the ID of the start task"<<'\n';
    cin>>startID;

    cout<<"enter the tasks in the following format <taskID> <Dependency> <duration of dependency>"<<'\n';
    cout<<"after entering the last task in your list press f, if you want to input another task input any other alphbetcial character"<<'\n';

    while(status != 'f'){
        // cout<<"enter a task in the following format: <taskID> <Dependency> <duration of dependency>"<< '\n';
        int taskID, taskDep, depDuration;
        cin>>taskID>>taskDep>>depDuration;

        addNode(taskDep, taskID, depDuration);
        // cout<<"if you are done type f else type any other character";
        cin>>status;
    }

    // cout<<"enter final task ID"<<'\n';
    int finalID;
    cin>>finalID;


    topoSort(startID);
    int pathLength = longestPath(finalID);
    cout<<"length of critical path: "<<pathLength<<'\n';
    cout<<"Critical Path: ";
    auto path = getCriticalPath();
    for(auto elem : path){
        cout<<elem<<' ';
    }
    cout<<'\n';



}
