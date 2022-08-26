#include<bits/stdc++.h>
#define INF INT_MAX
using namespace std;
 
class AdjListNode
{
   int v;
   int weight;
   public:
   AdjListNode(int v, int weight){
       this-> v = v;
       this-> weight = weight;
   }
   int getV(){return v;}
   int getWeight(){return weight;}
};
class Graph
{
   int v;
   list<AdjListNode>*adj;
   void topologicalSortUtil(int v, bool visited[], stack<int>&st);
   public:
   Graph(int v);
   void addEdge(int u, int v, int weight);
   void shortestPath(int s);
};
Graph::Graph(int v){
   this->v = v;
   adj = new list<AdjListNode>[v];
}
void Graph::addEdge(int u, int v, int weight){
   AdjListNode node(v,weight);
   adj[u].push_back(node);
}
void Graph::topologicalSortUtil(int v, bool visited[], stack<int>&st){
   visited[v] = true;
   list<AdjListNode>::iterator i;
   for(i = adj[v].begin(); i != adj[v].end(); i++){
       AdjListNode node = *i;
       if(!visited[node.getV()]){
           topologicalSortUtil(node.getV(), visited,st);
       }
   }
   st.push(v);
}
 
void Graph::shortestPath(int s){
   stack<int>st;
   int dist[v];
   bool visited[v];
   for(int i = 0; i < v; i++){
       visited[i] = false;
       dist[i] = INF;
   }
   for(int i = 0; i < v; i++){
       if(visited[i] == false){
           topologicalSortUtil(i,visited,st);
       }
   }
   dist[s] = 0;
   while(st.empty() == false){
       int u = st.top();
       st.pop();
       list<AdjListNode>::iterator i;
       if(dist[u] != INF){
           for(i = adj[u].begin(); i != adj[u].end(); i++){
               if(dist[i->getV()] > dist[u] + i->getWeight())
               {
                   dist[i->getV()] = dist[u] + i->getWeight();
               }
 
 
           }
       }
   }
   for(int i = 0; i < v; i++){
       if(dist[i] != INF){
           cout<<dist[i]<<" ";
       }
       else cout<<"INF"<<" ";
   }
}
int main(){
   Graph g(6);
   g.addEdge(0, 1, 2);
   g.addEdge(0, 4, 1);
   g.addEdge(1, 2, 3);
   g.addEdge(4, 2, 2);
   g.addEdge(4, 5, 4);
   g.addEdge(2, 3, 6);
   g.addEdge(5, 3, 1);
 
   int s = 0;
   cout << "Following are shortest distances from source " << s <<" \n";
   g.shortestPath(s);
}
