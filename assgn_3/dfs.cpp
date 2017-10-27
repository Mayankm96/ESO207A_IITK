#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

enum Color { WHITE, GREY, BLACK };

// structure Vertex for DFS
struct Vertex{
  int id;      // vertex number allocated
  int color;  // visit status
  int d;       // discovery time
  int f;       // finishing time
};

// Compare the struct Vertex on the basis of their finishing times
int compare(const void *s1, const void *s2){
      struct Vertex *v1 = (struct Vertex *)s1;
      struct Vertex *v2 = (struct Vertex *)s2;
      if (v1->f < v2->f)
        return 1;
      else if (v1->f == v2->f)
            return 0;
          else
            return -1;
}

// Returns the distinct elements present in the array
int* arrayDistinct(int arr[], int n1, int n2)
{
    int * des = new int [n2];
    int k = 0;
    // Pick all elements one by one
    for (int i = 0; i < n1; i++)
    {
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

    protected:
      // Explore the graph starting from a source node s
      void dfsExplore(int s, Vertex U[], int &t){
        cout<<"In :"<<s<<endl;
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
      }

      // Sorting the vertices according to finishing time
      Vertex * sortVertex(Vertex U[]){
        qsort(U, V_, sizeof(struct Vertex), compare);
        return U;
      }

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
        Vertex * depthFirstSearch(){
          // initialization
          int i, t = 0;
          Vertex * U = new Vertex [V_];
          for (i = 0; i < V_; i ++){
            U[i].id = i;
            U[i].color = WHITE;
          }
          // iterate over all edges
          for (i = 0 ; i< V_; i++){
            if ( U[i].color == WHITE){
              dfsExplore(U[i].id, U, t);
            }
          }
          return U;
        }

        Graph stronglyConnectedGraph(){
          // Carry out dfs on trnaspose of G
          Graph G_rev = this->reverseGraph();
          Vertex * U = G_rev.depthFirstSearch();
          U = sortVertex(U);
          // for (int lol = 0 ; lol< V_; lol ++){
          //   cout << U[lol].id << "-> " << U[lol].f<<endl;
          // }
          // initialization
          int i, t = 0;
          for (i = 0; i < V_; i ++){
            U[i].color = WHITE;
          }
          int parent = 0, numSCC = 0;
          int * SCC = new int [V_];

          printGraph();
          // iterate over all edges and perform dfs
          for (i = 0 ; i< V_; i++){
            if ( U[i].color == WHITE) {
              cout << "node: " << U[i].id << endl;
              this->dfsExplore(U[i].id, U, t);
              parent = U[i].id;
              SCC[parent] = U[i].id;
              numSCC ++;
            }
            else {
              SCC[U[i].id] = parent;
              int tmp = parent;
              parent = min(parent, U[i].id);
              if (tmp != parent)
                for (i = 0 ; i< V_; i++){
                  if ( SCC[i] == tmp) {
                    SCC[i] = parent;
                  }
                }
            }
            cout << U[i].id << " status: " << U[i].color <<endl;
          }

          // int * eSCC = arrayDistinct(SCC, V_, numSCC);
          // sort(eSCC, eSCC + numSCC);

        //   for( int l = 0; l < V_; l++){
        //       cout << l << ": " << SCC[l] << endl;
        //   }
        //   for (int k = 0; k < numSCC; k++){
        //     // cout << "PARENT" << k << ": " << eSCC[k] << endl;
        //     for( int l = 0; l < V_; l++){
        //       if(SCC[l] == eSCC[k])
        //         // cout << l << ": " << k << endl;
        //         SCC[l] = k;
        //     }
        //   }
        //
          Graph G_scc(numSCC);
        //   int v;
        //   vector<int>::iterator j;
        //   for (v = 0; v < V_; ++v){
        //       for (j = AdjList_[v].begin(); j != AdjList_[v].end(); ++j){
        //         if (SCC[v]!=SCC[*j]){
        //           G_scc.addEdge(SCC[v], SCC[*j]);
        //         }
        //       }
        //   }
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
