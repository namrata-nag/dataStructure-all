/**
 * Implement Dijkstra's algorithm.
Your graph must have at least 10 vertices and 20 edges.
Print out the graph - list of vertices and edges(pair of vertices)
Run dijkstra's algorithm.
Print the tree that results - list of vertices in the tree (same as above) and list of edges that make up the tree.
You may use heap library. That is the only library you an use.
Submit the code and screen shots of execution results
*/

/**
 * a -> c, b, d
 * b-> f
 * c-> f, e
 * d -> c
 * e -> d, h, i
 * f -> h, g
 * g -> b, a
 * h -> e, b, d
 * i -> h
 * j -> c, g
 * k -> j, d
 *
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include <limits>
#include <queue>

using namespace std;
#define INF std::numeric_limits<int>::max()

class Edge
{
public:
    int key;
    int weight;
};

class Graph
{
    int V; // number of vertex
    list<Edge *> adjacentList[11]; // array of list storing each edge

public:
    Graph(int V); // constructor
    void addVertex(int vertex, int edges[], int edge_count);
    void printGraph(Graph *adjList); // print graph
    void dijkstra(int src);
};

Graph::Graph(int v)
{
    this->V = v; // number of vertex
}
void Graph::addVertex(int s, int edges[], int edge_count)
{

    for (int i = 0; i < edge_count; i++)
    {
        Edge *newNode = new Edge();
        newNode->key = edges[i] - 1;
        int weight = 1 + rand() % 10;
        newNode->weight = weight;
        adjacentList[s].push_back(newNode);
    }

}

void Graph::printGraph(Graph *adjList)
{
 
    for (int i = 0; i< 11; i++ )
    {
        cout << "Vertex " << i << " :  ";
        for (list<Edge *>::iterator listIt = adjacentList[i].begin(); listIt != adjacentList[i].end(); listIt++)
        {
            Edge *temp = *listIt;
            cout << " (" << temp->key << ", " << temp->weight << ")"
                 << "  ";
        }
        cout << endl;
      
    }
}

// print the shortest path from src
void printTree(int tress[], int index, int src){
     if(index == src){
        return;
     }
     printTree(tress, tress[index], src);
     cout <<tress[index] << " --> " ;
}

void Graph::dijkstra(int src)
{
    vector<int> dist(V, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, src)); // priority queue
    int tress[11];
    tress[src] = src;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

            for (list<Edge *>::iterator listIt = adjacentList[u].begin(); listIt != adjacentList[u].end(); listIt++)
            {
                Edge *temp = *listIt;
                int v = temp->key;
                int weight = temp->weight;
                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                    tress[v] = u;
                    
                }
            }
    }

    cout << "Shortest distances from vertex " << src << " to all other vertices:" << endl;
    for (int i = 0; i < V; i++)
    {
        if (dist[i] != INF)
        {
            cout << "To vertex " << i << " total weight: " << dist[i] << " path: ";
            printTree(tress, i, src);
            cout  << i << endl;
        }
        else
        {
            cout << "Vertex " << i << " : No path" << endl;
        }
    }
} 

int main()
{
    int matrix[11][11] = {{2, 3, 4}, {6, 11}, {6, 5}, {3, 11}, {4, 8, 9}, {8, 7}, {2, 1}, {5, 2, 4}, {8}, {3, 7}, {10, 4}};
    int edge_count[] = {
        3,
        2,
        2,
        2,
        3,
        2,
        2,
        3,
        1,
        2,
        2,
    };

    Graph *gra = new Graph(11);
    for (int i = 0; i < 11; i++)
    {
        gra->addVertex(i, matrix[i], edge_count[i]);
    }

    gra->printGraph(gra);

    for (int i = 0; i < 11; i++)
    {
        gra->dijkstra(i);
        cout << endl;
    }

    return 0;
}
