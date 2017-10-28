#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

enum Color { WHITE, GREY, BLACK };

// structure Vertex for DFS
struct Vertex{
  int color;  // visit status
  int d;       // discovery time
  int f;       // finishing time
};

// Returns the distinct elements present in the array
int* arrayDistinct(int arr[], int n1, int n2)
{
    int * des = new int [n2];
    int k = 0;
    // Pick all elements one by one
    for (int i = 0; i < n1; i++){
        // Check if the picked element is already printed
        int j;
        for (j = 0; j < i; j++)
           if (arr[i] == arr[j])
               break;
        // If not printed earlier, then print it
        if (i == j){
          des[k] =  arr[i];
          k++;
        }
    }
    return des;
}

// Class Graph
class Graph
{
    private:
        int V_;
        std::vector<int> * AdjList_;
        std::stack<int> DfsStack_;

    protected:
      // Explore the graph starting from a source node s
      void dfsExplore(int s, Vertex U[], int &t){
        t = t + 1;
        U[s].d = t;
        U[s].color = BLACK;
        vector<int>::iterator i;
        for (i = this->AdjList_[s].begin(); i != this->AdjList_[s].end(); ++i){
            if ( U[*i].color == WHITE){
              dfsExplore(*i, U, t);
            }
        }
        t = t + 1;
        U[s].f = t;
        U[s].color = BLACK;
        DfsStack_.push(s);
      }

    public:
        Graph(int V){
            V_ = V;
            AdjList_ = new std::vector<int> [V];
            // cout << "Graph initiated successfully!" << endl;
        }

        ~Graph(){
            for(int i = 0; i < V_; i++){
              AdjList_[i].clear();
            }
            while (! DfsStack_.empty()){
              DfsStack_.pop();
            }
        }

        // Adding Edge to Graph
        void addEdge(int src, int dest){
            AdjList_[src].push_back(dest);
            // cout << "added edge from " << src << "->" << dest << endl;
        }

        // Print the graph
        void printGraph(){
            int v;
            vector<int>::iterator i;
            cout << V_ << endl;
            for (v = 0; v < V_; ++v){
                // cout << v << ": ";
                std::sort (AdjList_[v].begin(), AdjList_[v].end());
                for (i = AdjList_[v].begin(); i != AdjList_[v].end(); ++i){
                    cout << *i << ' ';
                }
                cout << "-1" << endl;
            }
        }

        // Find transpose of a graph
        Graph reverseGraph(){
          Graph G_rev(this->V_);
          int v;
          vector<int>::iterator i;
          for (v = 0; v<this->V_; v++){
            for (i = this->AdjList_[v].begin(); i != this->AdjList_[v].end(); ++i){
                G_rev.addEdge(*i, v);
            }
          }
          return G_rev;
        }

        // Peform DFS on the entire graph
        void depthFirstSearch(){
          // initialization
          int i, t = 0;
          Vertex * U = new Vertex [V_];
          for (i = 0; i < V_; i ++){
            U[i].color = WHITE;
          }
          // iterate over all edges
          for (i = 0 ; i< V_; i++){
            if ( U[i].color == WHITE){
              dfsExplore(i, U, t);
            }
          }
        }

        Graph stronglyConnectedGraph(){
          // Carry out dfs on trnaspose of G
          Graph G_rev = this->reverseGraph();
          G_rev.depthFirstSearch();
          Vertex * U = new Vertex [V_];

          // initialization
          int i, t = 0;
          for (i = 0; i < V_; i ++){
            U[i].color = WHITE;
          }
          int parent = 0, numSCC = 0;
          // array to keep track of parent in connected component
          int * order = new int [V_];

          // iterate over all edges and perform dfs
          while ( ! G_rev.DfsStack_.empty()){
            int id = G_rev.DfsStack_.top();
            if ( U[id].color == WHITE) {
              this->dfsExplore(id, U, t);
              parent = id;
              order[parent] = id;
              numSCC ++;
            }
            else {
              order[id] = parent;
            }
            G_rev.DfsStack_.pop();
            // cout << "exit " <<id << " status: " << U[id].color <<endl;
          }

          // array to store the labels for connected component
          int * label = arrayDistinct(order, V_, numSCC);
          std::sort(label, label + numSCC);

          for (int k = 0; k < numSCC; k++){
            for( int l = 0; l < V_; l++){
              if(order[l] == label[k])
                order[l] = k;
            }
          }

          Graph G_scc(numSCC);
          int v;
          vector<int>::iterator j;
          for (v = 0; v < V_; ++v){
              for (j = AdjList_[v].begin(); j != AdjList_[v].end(); ++j){
                if (order[v] != order[*j]){
                  G_scc.addEdge(order[v], order[*j]);
                }
              }
          }
          return G_scc;
        }
};

int main(){
  // Number of vertices in graph
  int V;
  cin >> V;
  //initialize graph
  Graph G(V);

  for(int src= 0; src < V; src++){
    int dest;
    cin >> dest;
    while(dest != -1){
      G.addEdge(src, dest);
      cin >> dest;
    }
  }

  Graph G_scc = G.stronglyConnectedGraph();
  G_scc.printGraph();

  return 0;
}
