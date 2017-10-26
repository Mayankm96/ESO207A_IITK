#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

// Class Graph
class Graph
{
    private:
        int V_;
        std::vector<int> * AdjList_;

    public:
        Graph(int V){
            V_ = V;
            AdjList_ = new std::vector<int> [V];
            cout << "Graph initiated successfully!" << endl;
        }

        // Adding Edge to Graph
        void addEdge(int src, int dest){
            AdjList_[src].push_back(dest);
            cout << "added edge from " << src << "->" << dest << endl;
        }

        // Print the graph
        void printGraph(){
            int v;
            vector<int>::iterator i;
            cout << V_ << endl;
            for (v = 0; v < V_; ++v){
                cout << v << ": ";
                for (i = AdjList_[v].begin(); i != AdjList_[v].end(); ++i){
                    cout << *i << " ";
                }
                cout << "-1"<< endl;
            }
        }

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

  Graph G_rev = G.reverseGraph();
  G.printGraph();
  G_rev.printGraph();

  return 0;
}
