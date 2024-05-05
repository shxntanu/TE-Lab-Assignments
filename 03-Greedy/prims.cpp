/*
Author - Shantanu Wable
*/

#include<bits/stdc++.h>
using namespace std;
const int max = INT_MAX;

class Graph {
    
    int **adjMatix;
    int vertexCount;
    int edgeCount;
    map<string, int> cities;
    map<int, string> inv_cities;
    
    void add( string city1, string city2, int dist ) {
        adjMatix[cities[city1]][cities[city2]] = dist;
        adjMatix[cities[city2]][cities[city1]] = dist;
    }
    
    // minimum_key() method for finding the vertex that has minimum key-value and that is not added in MST yet
    int minimum_key(int key[], bool mst[])
    {
        int minimum  = INT_MAX, min,i;
          
        // iterate over all vertices to find the vertex with minimum key-value
        for (i = 0; i < vertexCount; i++)
            if (mst[i] == 0 && key[i] < minimum ) {
                minimum = key[i];
                min = i;
            }
        return min;
    }

    public:

    Graph(){
        cout<<"Enter number of Vertices: ";
        cin>>vertexCount;
        cout<<"Enter number of edges: ";
        cin>>edgeCount;
        
        adjMatix = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            adjMatix[ i ] = new int[ vertexCount ];
            for(int j=0; j<vertexCount; j++)
                adjMatix[i][j] = 0;
        }

        cout<<"Add cities in order: "<<endl;
        for(int i = 0; i < vertexCount; i++) {
            string city;
            cin>>city;
            cities.insert(pair<string, int>(city, i));
            inv_cities.insert(pair<int, string>(i, city));
        }
        
//        for(auto i: cities) {
//            cout << i.first << " \t\t " << i.second << endl;
//        }
        
        cout<<"Add the "<<edgeCount<<" edges"<<endl;
        
        for(int i=0; i<edgeCount; i++) {
            string u,v;
            int d;
            cout<<"City 1: ";
            cin>>u;
            cout<<"City 2: ";
            cin>>v;
            cout<<"Distance: ";
            cin>>d;
            add(u, v, d);
        }
        
//        for(int i=0; i<vertexCount; i++) {
//            for(int j=0; j<vertexCount; j++) {
//                cout<<adjMatix[i][j]<<" ";
//            }
//            cout<<endl;
//        }
    }
    
    void prim(Graph g) {
        int n = g.vertexCount;
        
        // create parent[] array of size equal to total number of vertices for storing the MST
        // purpose of the array is to store parent vertex of successive vertices so as to form a tree
        int parent[n];
        
        // create key[] array for selecting an edge having minimum weight
        int key[n];
        
        // create mst[] array for seeing if a vertex has been added to MST or not
        bool mst[n];
        
        // initialise key values to some maximum value
        // initialise mst values to 0 to indicate no vertex has been added to mst initially
        for (int i = 0; i < n; i++)
        {
            key[i] = INT_MAX;
            mst[i] = 0;
        }
        
        // we select the first vertex as the starting point for the algorithm
        // edge weight of first vertex only = 0
        key[0] = 0;
        // since first vertex itself is the parent, it doesn't have a parent, so we set a garbage value
        parent[0] = -1;
        
        for (int count = 0; count < n-1; count++)
        {
            // select the vertex having minimum key and that is not added in the MST yet from the set of vertices
            // and set its flag to 1 to indicate that it has been added to MST
            int min_edge_vertex = minimum_key(key, mst);
            mst[min_edge_vertex] = 1;
            
            for (int vertex = 0; vertex < n; vertex++)
            {
                /*
                 Now we find all adjacent vertices from the current (min_egde_vertex) vertex
                 and perform 3 condition check to update the neighbour vertex's parent and distance:
                    - Edge exists between the vertices
                    - Neighbouring vertex has not been already visited
                    - Distance / weight from the current vertex is lesser than distance from any previous vertex
                 */
                if (g.adjMatix[min_edge_vertex][vertex] && mst[vertex] == 0 && g.adjMatix[min_edge_vertex][vertex] <  key[vertex])
                {
                    // update parent and weights of neighbouring vertices which satify the conditions above
                    parent[vertex]  = min_edge_vertex;
                    key[vertex] = g.adjMatix[min_edge_vertex][vertex];
                }
            }
         }
        
        cout<<"MST of given graph is: \n"<<endl;
        cout<<"\nEdge \t Weight\n";
        for(int i=1; i<n; i++) {
            cout<<inv_cities[parent[i]]<<" <-> "<<inv_cities[i]<<" \t "<<g.adjMatix[i][parent[i]]<<endl;
        }
    }
};

int main() {
    
    Graph g;
    g.prim(g);
    
    return 0;
}
