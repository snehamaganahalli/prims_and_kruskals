#include <bits/stdc++.h>
using namespace std;

/* Maximum Number of vertices in the graph. */
#define N 10
int graph_adj[10][10];
int n;
int prims_or_kruskal; // 0 for prims and 1 for kruskal

/*
   A utility function to find the vertex with
   minimum key value, from the set of vertices
   not yet included in MST
*/
int min_key(int key[], bool mst_set[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (mst_set[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

/*
   A utility function to print the
   constructed MST stored in parent[]
*/
void print_mst(int parent[], int graph[][N])
{
   int mst_sum = 0;
    cout<<"Edge \t\tWeight\n";
    for (int i = 1; i < n; i++) {
        cout<<parent[i]<<" --- "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
        mst_sum = mst_sum + graph[i][parent[i]];
    }
    cout <<endl << "MST cost is: "<< mst_sum <<endl;
    cout<<endl;
}

/* Function to construct and print MST for
   a graph represented using adjacency
   matrix representation
*/
void prims_mst(int graph[][N])
{
    // Array to store constructed MST
    int parent[n];

    // Key values used to pick minimum weight edge in cut
    int key[n];

    // To represent set of vertices included in MST
    bool mst_set[n];

    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mst_set[i] = false;

    /* Always include first 1st vertex in MST.
       Make key 0 so that this vertex is picked as first vertex.
    */
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have n vertices
    for (int count = 0; count < n - 1; count++)
    {
        /* Pick the minimum key vertex from the
           set of vertices not yet included in MST
        */
        int u = min_key(key, mst_set);

        // Add the picked vertex to the MST Set
        mst_set[u] = true;

        /* Update key value and parent index of
           the adjacent vertices of the picked vertex.
           Consider only those vertices which are not
           yet included in MST
        */
        for (int v = 0; v < n; v++)

            /* graph[u][v] is non zero only for adjacent vertices of m
               mst_set[v] is false for vertices not yet included in MST
               Update the key only if graph[u][v] is smaller than key[v]
            */
            if (graph[u][v] && mst_set[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // print the constructed MST
    print_mst(parent, graph);
}

/* weighted_union data structure
   path compression + rank by weighted_union
*/
class weighted_union {
    int* parent;
    int* rank;

public:
    weighted_union(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }
    // union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

class Graph {
    vector<vector<int> > edgelist;
    int V;

public:
    void add_edge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y });
    }

    void kruskals_mst()
    {
        // 1. Sort all edges
        sort(edgelist.begin(), edgelist.end());

        // Initialize the union
        weighted_union s(n);
        int result = 0;
        cout << "Following are the edges in the "
                "constructed MST"
             << endl;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // take that edge in MST if it does form a cycle
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                result += w;
                cout << x << " --- " << y << "  " << w
                     << endl;
            }
        }
        cout << "Minimum Cost Spanning Tree: " << result << endl;
    }
};

int main()
{

    while (1){
    cout << endl<<"Enter 0 for prims and 1 for kruskal"<<endl;
    cin >> prims_or_kruskal;
    if (prims_or_kruskal !=0 && prims_or_kruskal!=1) {
        cout << "Invalid Selection!! \n Enter 0 for prims and 1 for kruskal";
        continue;
    }
    cout << "Enter number of vertices \n";
    cin >> n;

    Graph g;
    cout <<endl<<"Enter adjacency matrix \n";
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j< n; j++) {
            cout << "graph_adj["<<i<<"]"<<"["<<j<<"]  ";
            cin >> graph_adj[i][j];
            if (graph_adj[j][i] == 0)
                graph_adj[j][i] = graph_adj[i][j];
            if(graph_adj[i][i] !=0) {
               cout << "graph[i][i] should be always equal to 0";
               exit(0);
            }
            if ((graph_adj[i][j] != graph_adj[j][i])) {
                cout << "Prims and Kruskal works only on undirected graph!!!. graph[i][j] should be equal to graph[j][i]";
                exit(0);
            }
            if (prims_or_kruskal && graph_adj[i][j] != 0)
                g.add_edge(i, j, graph_adj[i][j]);
        }
        cout<<endl;
    }

   if(prims_or_kruskal == 0)
       prims_mst(graph_adj);
   else
      g.kruskals_mst();
  }
  return 0;
}
