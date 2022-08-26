#include <bits/stdc++.h>
using namespace std;

#define ll long long int
ll parent[100005];
ll ranking[100005];
ll visited[100005];

// making the graph with weight,vertex 1 and vertex 2
class Graph
{
public:
    ll weight;
    ll v1;
    ll v2;
    Graph()
    {
        weight = 0;
        v1 = 0;
        v2 = 0;
    }
    Graph(ll weight, ll v1, ll v2)
    {
        this->weight = weight;
        this->v1 = v1;
        this->v2 = v2;
    }
};

// comparing the weight of the edges to sort them
bool compare(Graph a, Graph b)
{
    return a.weight < b.weight;
}

vector<Graph> Minimum_Spanning_Tree;
vector<Graph> input_graph;
vector<ll> vec[100005];

// initialising the parent of each vertex as itself
// initialising the rank of each vertex as 1
void initialise(ll vertex)
{
    for (ll i = 1; i <= vertex; i++)
    {
        parent[i] = i;
        ranking[i] = 1;
    }
}

// the finding of the parent of each vertex without path compression
// Naive approach with time complexity O(n)
ll find_parent(ll x)
{
    if (parent[x] == x)
    {
        return x;
    }
    else
    {
        return find_parent(parent[x]);
    }
}

// union without using rank
// time complexity O(n)
bool union_naive_approach(ll x, ll y)
{
    ll a = find_parent(x);
    ll b = find_parent(y);

    if (a != b)
    {
        parent[b] = a;
        return true;
    }
    else
    {
        return false;
    }
}
// efficient approach to find the parent of each vertex
// almost constant time approach
ll find_parent_path_compressed(ll x)
{
    if (parent[x] == x)
    {
        return x;
    }
    else
    { // here we're updating the parent too but in naive approach we don't update
        return parent[x] = find_parent_path_compressed(parent[x]);
    }
}

// efficient approach we're making the smaller ranked vertice child of the higher ranked
// almost constant time approach
bool union_by_rank(ll x, ll y)
{
    ll a = find_parent_path_compressed(x);
    ll b = find_parent_path_compressed(y);

    if (a != b)
    {
        if (ranking[a] > ranking[b])
        {
            parent[b] = a;
        }
        else if (ranking[a] == ranking[b])
        {
            parent[b] = a;
            // increasing the rank only if the rank of the vertices are the same
            ranking[a]++;
        }
        else
        {
            parent[a] = b;
        }
        return true;
    }
    else
    {
        return false;
    }
}
// function to check if the whole graph is connected or not
void DFS(ll s, ll *component_count)
{
    visited[s] = 1;
    (*component_count)++;

    for (ll i = 0; i < vec[s].size(); i++)
    {
        ll temp = vec[s][i];
        if (visited[temp] == 0)
        {
            DFS(temp, component_count);
        }
    }
}

//---Kruskal's Algorithm
// We'll traverse each edge with the sorted weight
// Then we'll add the edge to the mst if the edge doesn't form a cycle
// time complexity(O(ELOGE) + O(E) + O(E))
void kruskalMstFind_without_pathcompression_and_rank()
{
    // taking the time
    time_t beginning_time, ending_time;

    time(&beginning_time);

    ios_base::sync_with_stdio(false);

    FILE *fileinput = fopen("input.txt", "r");
    FILE *fileoutput = fopen("output.txt", "w");

    ll x, y, z, i, vertex, edge;
    fscanf(fileinput, "%lld %lld\n", &vertex, &edge);
    initialise(vertex);

    for (i = 1; i <= edge; i++)
    {
        fscanf(fileinput, "%lld %lld %lld", &x, &y, &z);
        input_graph.push_back({z, x, y});
    }

    sort(input_graph.begin(), input_graph.end(), compare);

    for (i = 0; i < input_graph.size(); i++)
    {
        Graph temp = input_graph[i];

        // if union is possible that means there's no cycle
        if (union_naive_approach(temp.v1, temp.v2))
        {
            Minimum_Spanning_Tree.push_back(temp);
            vec[temp.v1].push_back(temp.v2);
            vec[temp.v2].push_back(temp.v1);
        }
    }

    memset(visited, 0, sizeof(visited));
    ll component_count = 0;
    DFS(1, &component_count);

    // checking if the graph is connected
    if (component_count == vertex)
    {
        // keeping track of the minimum_spanning_val
        ll minimum_spanning_val = 0;
        for (i = 0; i < Minimum_Spanning_Tree.size(); i++)
        {
            minimum_spanning_val += Minimum_Spanning_Tree[i].weight;
        }
        fprintf(fileoutput, "The minimum sum is : %lld\n", minimum_spanning_val);
    }
    else
    {
        fprintf(fileoutput, "DISCONNECTED GRAPH. THERE WON'T BE A MST\n");
    }

    time(&ending_time);
    double time_taken = double(ending_time - beginning_time);
    fprintf(fileoutput, "The total time taken is: %lf\n", time_taken);

    fclose(fileinput);
    fclose(fileoutput);
}

// efficient approach with time and space complexity
// using path compression and union by rank
// time complexity(O(ELOGE) + O(E) + Constant)
void kruskalMstFind_with_pathcompression_and_rank()
{
    time_t beginning_time, ending_time;
    time(&beginning_time);
    ios_base::sync_with_stdio(false);

    FILE *fileinput = fopen("input.txt", "r");
    FILE *fileoutput = fopen("output.txt", "w");

    ll x, y, z, i, vertex, edge;
    fscanf(fileinput, "%lld %lld\n", &vertex, &edge);
    initialise(vertex);

    for (i = 1; i <= edge; i++)
    {
        fscanf(fileinput, "%lld %lld %lld", &x, &y, &z);
        input_graph.push_back({z, x, y});
    }

    sort(input_graph.begin(), input_graph.end(), compare);

    for (i = 0; i < input_graph.size(); i++)
    {
        Graph temp = input_graph[i];
        // using union by rank
        if (union_by_rank(temp.v1, temp.v2))
        {
            Minimum_Spanning_Tree.push_back(temp);
            vec[temp.v1].push_back(temp.v2);
            vec[temp.v2].push_back(temp.v1);
        }
    }

    memset(visited, 0, sizeof(visited));
    ll component_count = 0;
    DFS(1, &component_count);

    if (component_count == vertex)
    {
        ll minimum_spanning_val = 0;
        for (i = 0; i < Minimum_Spanning_Tree.size(); i++)
        {
            minimum_spanning_val += Minimum_Spanning_Tree[i].weight;
        }
        fprintf(fileoutput, "The minimum sum is: %lld\n", minimum_spanning_val);
    }
    else
    {
        fprintf(fileoutput, "MST IS NOT POSSIBLE\n");
    }

    time(&ending_time);
    double time_taken = double(ending_time - beginning_time);
    fprintf(fileoutput, "The total time taken is: %lf\n", time_taken);

    fclose(fileinput);
    fclose(fileoutput);
}

int main()
{
    int x;
    printf("Enter 1 for finding Mst sum using Kruskal without path compression and rank(Naive Approach).\nEnter 2 for finding Mst sum using Kruskal with path compression and rank(Efficient Approach) :");
    scanf("%d", &x);
    if (x == 1)
    {
        kruskalMstFind_without_pathcompression_and_rank();
    }
    else if (x == 2)
    {
        kruskalMstFind_with_pathcompression_and_rank();
    }
}

// the first process take 4 to 5 seconds
// the second process takes 0 to 1 seconds