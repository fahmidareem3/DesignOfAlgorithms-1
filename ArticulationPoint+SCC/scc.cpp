#include <bits/stdc++.h>
using namespace std;

/*  Kosharaju's Algorithm
    1. Order the vertices in decreasing order of finish times in DFS or simply get the topological sort 
    2. Reverse all edges
    3. Do DFS of the reversal graph in the order obtained in step 1. For every vertex, print all reachable vertices
       as one strongly connected component
*/

class Graph {
    int V;
    list<int>*adj;

    void topologicalSort(int v,vector<bool> &visited,stack<int> &st);
    void DFS(int v,vector<bool>&visited);
public:
    Graph(int V);
    void addEdge(int v,int w);
    void printSCCs();
    Graph getTranspose();
     

};

Graph::Graph(int V){
    this -> V = V;
    adj = new list<int>[V];
}

void Graph::DFS(int v,vector<bool> &visited){
    visited[v]= true;
    cout<<v<<" ";

    for(auto i :adj[v])
        if(!visited[i])
            DFS(i,visited);
}

Graph Graph::getTranspose(){
    Graph g(V);
    for(int v = 0 ; v < V ; v++){
        for(auto i: adj[v])
            g.adj[i].push_back(v);
    }
    return g;
}

void Graph::addEdge(int v,int w){
    adj[v].push_back(w);
}

void Graph::topologicalSort(int v,vector<bool>&visited,stack<int>&st){
    visited[v] = true;
    for(auto i:adj[v])
        if(!visited[i])
            topologicalSort(i,visited,st);
    st.push(v);
}

void Graph::printSCCs() 
{ 

    // 1. Order the vertices in decreasing order of finish times in DFS or simply get the topological sort 
	stack<int> s; 
    vector<bool>visited(V,false);

	for(int i = 0; i < V; i++) 
		if(visited[i] == false) 
			topologicalSort(i, visited, s); 

    //  2. Reverse all edges
	Graph gr = getTranspose(); 


    // 3. Do DFS of the reversal graph in the order obtained in step 1. For every vertex, print all reachable vertices
    //    as one strongly connected component
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	while (s.empty() == false) 
	{ 
		int v = s.top(); 
		s.pop(); 
 
		if (visited[v] == false) 
		{ 
			gr.DFS(v, visited); 
			cout << endl; 
		} 
	} 
} 

int main(){
    Graph g(5); 
	g.addEdge(1, 0); 
	g.addEdge(0, 2); 
	g.addEdge(2, 1); 
	g.addEdge(0, 3); 
	g.addEdge(3, 4); 

	cout << "Following are strongly connected components in given graph \n"; 
	g.printSCCs(); 
}