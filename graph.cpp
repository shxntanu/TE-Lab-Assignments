/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to 
perform BFS. Use the map of the area around the college as the graph. 
Identify the prominent land marks as nodes and perform DFS and BFS on that.
Functions to be implemented:
1. Read graph
2. Display adjacency list
3. DFS
4. BFS
5. indegree & outdegree
6. isConnected
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    string name;
    Node *next;
    Node *down;

    Node( string n = "" ) {
        name = n;
        next = nullptr;
        down = nullptr;
    }
};

class Graph
{
    Node *head = nullptr;

    void add( string NodeA, string NodeB ) {
        // If adjacency list is empty
        if( head == nullptr ) {
            Node *node1 = new Node( NodeA );
            Node *node2 = new Node( NodeB );
            head = node1;
            node1->next = node2;
        }

        else {
            Node *currentNode = head;
            Node *prevNode = nullptr;
            bool found = false;
            while( currentNode != nullptr ) {

                // If NodeA is found
                if( currentNode->name == NodeA ) {
                    found = true;
                    Node *currentListNode = currentNode;
                    while( currentListNode->next != nullptr )
                        currentListNode = currentListNode->next;
                    Node *newNode = new Node( NodeB );
                    currentListNode->next = newNode;
                    break;
                }
                prevNode = currentNode;
                currentNode = currentNode->down;

            }

            // If NodeA is not found
            if(!found) {
                Node *newNode1 = new Node( NodeA );
                Node *newNode2 = new Node( NodeB );
                prevNode->down = newNode1;
                newNode1->next = newNode2;
            }
        }
    }

    public:

    void addNode( string NodeA, string NodeB ) {
        add( NodeA, NodeB );
        add( NodeB, NodeA );
    }

    void print() {
        Node *currentArrayNode = head;
        while( currentArrayNode != nullptr ) {
            Node *currentListNode = currentArrayNode;
            while( currentListNode != nullptr ) {
                cout<< currentListNode->name << " -> ";
                currentListNode = currentListNode->next;
            }
            cout<<endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void printOutDegrees() {
        Node *currentArrayNode = head;
        while(currentArrayNode != nullptr ) {
            Node *currentListNode = currentArrayNode;
            int degree = 0;
            while( currentListNode != nullptr ) {
                degree++;
                currentListNode = currentListNode->next;
            }
            cout<< currentArrayNode->name << " : " << degree<<endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void printInDegrees() {
        Node *currentNode = head;
        while( currentNode != nullptr ) {
            int count = 0;
            Node *temp = head;
            while( temp != nullptr ) {
                Node *neighbour = temp->next;
                while( neighbour != nullptr ) {
                    if( neighbour->name == currentNode->name ) 
                        count++;
                    neighbour = neighbour->next;
                }
                temp = temp->down;
            }
            cout<< currentNode->name << "\t : \t" << count <<endl;
            currentNode = currentNode->down;
        }
    }

    void BFS ( string node ) {
        queue<string> Queue;
        vector<string> visited;
        Queue.push( node );
        visited.push_back( node );
        while( true ) {

            if( !Queue.empty() ) {
                node = Queue.front();
                Queue.pop();
                cout<< node << " ";
            }
            else {
                cout<<endl;
                break;
            }

            Node *currentNode = head;
            bool found = false;
            while ( currentNode != nullptr ) {
                if( currentNode->name == node ) {
                    found = true;
                    Node *currentListNode = currentNode->next;
                    while( currentListNode != nullptr ){    
                        if( find( visited.begin(), visited.end(), currentListNode->name ) == visited.end() ) {
                            visited.push_back( currentListNode->name );
                            Queue.push( currentListNode->name );
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if( !found ) {
                cout<< "Given node not in the graph" <<endl;
                return;
            }
        }
    }

    void DFS ( string node ) {
        stack<string> Stack;
        vector<string> visited;
        Stack.push( node );
        visited.push_back( node );
        while( true ) {
            if( !Stack.empty() ) {
                node = Stack.top();
                Stack.pop();
                cout<< node << " ";
            }
            else {
                cout<<endl;
                break;
            }

            Node *currentNode = head;
            bool found = false;
            while ( currentNode != nullptr ) {
                if( currentNode->name == node ) {
                    found = true;
                    Node *currentListNode = currentNode->next;
                    while( currentListNode != nullptr ) {
                        if( find( visited.begin(), visited.end(), currentListNode->name ) == visited.end() ) {
                            Stack.push( currentListNode->name );
                            visited.push_back( currentListNode->name );
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if( !found ) {
                cout<< "Given node doesn't exist in the graph" <<endl;
                return;
            }
        }
    }
};

int main() {
    Graph g ; 
    g.addNode( "Katraj" , "PICT" ) ;
    g.addNode( "Bharti" , "Katraj" ) ; 
    g.addNode( "Bharti" , "PICT" ) ;
    g.addNode( "Katraj" , "SKNCOE" ) ; 
    g.addNode( "PICT" , "SKNCOE" ) ;
    g.addNode( "SKNCOE" , "Temple" ) ; 
    g.addNode( "Temple" , "Katraj" ) ; 
    g.addNode( "Temple" , "Kondhwa" ) ; 
    g.print() ; 
    g.printInDegrees();
    g.printOutDegrees();
    g.BFS( "Katraj" ) ; 
    g.DFS( "Katraj" ) ;
    return 0;
}
