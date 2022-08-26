#include<bits/stdc++.h>
using namespace std;
void Dfs(vector<int>adj[], bool isvisited[], int s, stack<int> &st){
   isvisited[s] = true;
   for(int x: adj[s]){
       if(isvisited[x] == false){
           Dfs(adj,isvisited,x,st);
       }
     
   }
   st.push(s);
}
void topological_sort(vector<int>adj[], int v){
    bool isvisited[v];
    for(int i = 0; i < v; i++){
       isvisited[i] = false;
    }
    stack<int>st;
    for(int i = 0; i < v; i++){
       if(isvisited[i] == false){
           Dfs(adj,isvisited,i,st);
       }
    }
    while(st.empty() == false){
       cout<< st.top()<<" ";
       st.pop();
 
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
  topological_sort(adj,v);
}
 
