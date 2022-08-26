#include <bits/stdc++.h>
using namespace std;

#define ll long long int

const ll INF = 1e10;

// creating the graph class
class Graph
{
public:
    ll weight;
    ll vertex;
    Graph()
    {
        weight = INF;
        vertex = 0;
    }
    Graph(ll w, ll v)
    {
        weight = w;
        vertex = v;
    }
};

// function to swap the vertices
void swap_vertice(Graph *a, Graph *b)
{
    Graph temp = *a;
    *a = *b;
    *b = temp;
}

// creating the heap
class Heap
{
private:
    Graph arr[200005];
    ll heap_size = 0;

public:
    Heap()
    {
        heap_size = 0;
    }
    void insert(Graph x)
    {
        arr[heap_size] = x;
        ll temp = heap_size;
        for (;;)
        {
            // checking if weight of parent is greater than weight of child
            if (arr[temp / 2].weight > arr[temp].weight)
            {
                swap_vertice(&arr[temp], &arr[temp / 2]);
                temp = temp / 2;
            }
            else
            {
                break;
            }
        }
        heap_size++;
    }

    bool isEmpty()
    {
        if (heap_size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // extracting the minimum value from the heap
    Graph extract_min()
    {
        if (heap_size == 0)
        {
            return {-1, -1};
        }
        heap_size--;
        Graph minimum = arr[0];
        swap_vertice(&arr[0], &arr[heap_size]);

        ll i = 0;
        for (;;)
        {

            if ((2 * i + 1) <= heap_size - 1)
            {
                if (arr[i].weight > arr[2 * i + 1].weight && arr[i].weight > arr[2 * i].weight)
                {
                    if (arr[2 * i].weight < arr[2 * i + 1].weight)
                    {
                        swap_vertice(&arr[i], &arr[2 * i]);
                        i = 2 * i;
                    }
                    else
                    {
                        swap_vertice(&arr[i], &arr[2 * i + 1]);
                        i = 2 * i + 1;
                    }
                }
                else if (arr[i].weight > arr[2 * i + 1].weight)
                {
                    swap_vertice(&arr[i], &arr[2 * i + 1]);
                    i = 2 * i + 1;
                }
                else if (arr[i].weight > arr[2 * i].weight)
                {
                    swap_vertice(&arr[i], &arr[2 * i]);
                    i = 2 * i;
                }
                else
                {
                    break;
                }
            }
            else if (2 * i <= heap_size - 1)
            {
                if (arr[i].weight > arr[2 * i].weight)
                {
                    swap_vertice(&arr[i], &arr[2 * i]);
                    i = 2 * i;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        return minimum;
    }
};

ll Minimum_Spanning_Tree[100005];
ll key[100005];
ll parent[100005];

vector<Graph> vec[100005];

// we'll be taking a parent array and a key array
// we will take two sets and keep on adding the visited edges to the mst set
// we'll update the key of a vertice by taking the minimum of the adjacent vertice of the parent
// Time complexity is O(V2)
void prims_mst_without_heap()
{
    time_t beginning_time, ending_time;
    time(&beginning_time);
    ios_base::sync_with_stdio(false);

    FILE *fileinput = fopen("input.txt", "r");
    FILE *fileoutput = fopen("output.txt", "w");

    memset(Minimum_Spanning_Tree, 0, sizeof(Minimum_Spanning_Tree));
    memset(parent, -1, sizeof(parent));
    for (ll i = 1; i <= 100002; i++)
    { // initialising the key as infinity
        key[i] = INF;
    }

    ll vertex, edge, x, y, z, i, j;
    fscanf(fileinput, "%lld %lld", &vertex, &edge);
    for (i = 1; i <= edge; i++)
    {
        fscanf(fileinput, "%lld %lld %lld", &x, &y, &z);
        vec[x].push_back({z, y});
        vec[y].push_back({z, x});
    }

    key[1] = 0;

    for (ll k = 1; k <= vertex; k++)
    {
        ll temp_key = INF;
        ll temp_vertice = 0;
        for (j = 1; j <= vertex; j++)
        {
            if (key[j] < temp_key && Minimum_Spanning_Tree[j] == 0)
            {
                temp_key = key[j];
                temp_vertice = j;
            }
        }

        Minimum_Spanning_Tree[temp_vertice] = 1;

        for (i = 0; i < vec[temp_vertice].size(); i++)
        {
            Graph temp_Graph = vec[temp_vertice][i];
            if (Minimum_Spanning_Tree[temp_Graph.vertex] == 0 && key[temp_Graph.vertex] > temp_Graph.weight)
            {
                key[temp_Graph.vertex] = temp_Graph.weight;
                parent[temp_Graph.vertex] = temp_vertice;
            }
        }
    }

    ll minimum_sum = 0;
    for (i = 1; i <= vertex; i++)
    {
        if (Minimum_Spanning_Tree[i] == 0)
        {
            fprintf(fileoutput, "NO MINIMUM SPANNING TREE POSSIBLE\n");
            return;
        }
        else
        {
            minimum_sum += key[i];
        }
    }

    fprintf(fileoutput, "The minimum sum is : %lld\n", minimum_sum);

    time(&ending_time);
    double time_taken = double(ending_time - beginning_time);
    fprintf(fileoutput, "The total time taken is: %lf\n", time_taken);

    fclose(fileinput);
    fclose(fileoutput);
}

Heap minHeap;

// here outer loop runs O(V) times
// Inner loop extract min and decrease key all operation take O(logn) time
// total time complexity is O(Vlog(E))
void prims_mst_min_heap()
{
    time_t beginning_time, ending_time;
    time(&beginning_time);
    ios_base::sync_with_stdio(false);

    FILE *fileinput = fopen("input.txt", "r");
    FILE *fileoutput = fopen("output.txt", "w");

    memset(Minimum_Spanning_Tree, 0, sizeof(Minimum_Spanning_Tree));
    memset(parent, -1, sizeof(parent));
    for (ll i = 1; i <= 100002; i++)
    {
        key[i] = INF;
    }

    ll vertex, edge, x, y, z, i, j;
    fscanf(fileinput, "%lld %lld", &vertex, &edge);
    for (i = 1; i <= edge; i++)
    {
        fscanf(fileinput, "%lld %lld %lld", &x, &y, &z);
        vec[x].push_back({z, y});
        vec[y].push_back({z, x});
    }

    key[1] = 0;
    minHeap.insert({key[1], 1});
    Minimum_Spanning_Tree[1] = 1;

    for (; !minHeap.isEmpty();)
    {
        Graph temp = minHeap.extract_min();
        Minimum_Spanning_Tree[temp.vertex] = 1;
        for (ll i = 0; i < vec[temp.vertex].size(); i++)
        {
            Graph a = vec[temp.vertex][i];
            if (Minimum_Spanning_Tree[a.vertex] == 0 && key[a.vertex] > a.weight)
            {
                key[a.vertex] = a.weight;
                parent[a.vertex] = temp.vertex;
                minHeap.insert(a);
            }
        }
    }

    ll minimum_sum = 0;

    for (i = 1; i <= vertex; i++)
    {
        if (Minimum_Spanning_Tree[i] == 0)
        {
            fprintf(fileoutput, "MST NOT POSSIBLE\n");
            return;
        }
        minimum_sum += key[i];
    }

    fprintf(fileoutput, "The minimum sum is : %lld\n", minimum_sum);

    time(&ending_time);
    double time_taken = double(ending_time - beginning_time);
    fprintf(fileoutput, "The total time taken is: %lf\n", time_taken);

    fclose(fileinput);
    fclose(fileoutput);
}

int main()
{
    int x = 1;
    printf("ENTER 1 FOR PRIM'S ALGORITHM WITHOUT DATASTRUCTURE(NAIVE APPROACH)\nENTER 2 FOR PRIM'S ALGORITHM USING MINHEAP(EFFICIENT):");
    scanf("%d", &x);
    if (x == 1)
    {
        prims_mst_without_heap();
    }
    else if (x == 2)
    {
        prims_mst_min_heap();
    }

    return 0;
}

// effecient approach takes 0 to 1 second
// naive approach takes 22 to 24 seconds