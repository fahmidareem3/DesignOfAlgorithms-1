#include<bits/stdc++.h>
using namespace std;
void topological_sortBfs(vector<int>adj[], int v){
   vector<int>isvisited(v,0);
   vector<int>indegree(v,0);
   for(int i = 0; i < v; i++){
       for(int x: adj[i]){
           indegree[x]++;
       }
   }
   queue<int>q;
   for(int i = 0; i < v; i++){
       if(indegree[i] == 0){
           q.push(i);
       }
   }
   while(q.empty() == false){
       int u = q.front();
       cout<<u<<" ";
       q.pop();
       for(int x: adj[u]){
           if(--indegree[x] == 0){
               q.push(x);
           }
       }
 
 
   }
 
}
void addEdge(vector<int>adj[], int u, int v){
   adj[u].push_back(v);
  
}
int main(){
   int v, e;
   cin >> v >> e;
   vector<int>adj[v];
   for(int i = 1; i <= e; i++){
       int a, b;
       cin >> a >> b;
       addEdge(adj,a,b);
   }
  topological_sortBfs(adj,v);
}
