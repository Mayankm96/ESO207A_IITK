#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// structure Vertex for Dijkstra's Algorithm
struct Vertex{
  long long int distance;       // distance
  int parent;                   // predecessor
};

struct Edge{
  int destination;              // destination node's ID
  long long int weight;         // edge weight
};

// Global variables to store nodes information
Vertex * nodes;
Edge * edges;

class MinPriorityQueue{
  private:
    int * Q_;
    int end_;
    int size_;

  protected:
    void exchange(int a, int b){
      int tmp = Q_[a];
      Q_[a] = Q_[b];
      Q_[b] = tmp;
    }

    int searchID(int id){
      int index;
      for (index = 0; index <= end_; index ++){
        if (Q_[index] == id)
          break;
      }
      return index;
    }

  public:
    MinPriorityQueue(int V){
      Q_ = new int [V];
      size_ = V;
      end_ = -1;
    }

    bool isEmpty(){
      if(end_ == -1)
        return 1;
      else
        return 0;
    }

    void insert(int id){
      end_ = end_ + 1;

      if (end_ > size_){
        return;
      }

      Q_[end_] = id;
      //heapify
      int i = end_;
      int parent = i/2;
      while (i > 0 && (nodes[Q_[parent]].distance > nodes[Q_[i]].distance)){
        exchange(parent, i);
        i = parent;
        parent = i/2;
      }
    }

    void changeKey(int id, long long int key){
      int index = searchID(id);

      if (nodes[Q_[index]].distance < key){
        cout << "ERROR!";
        return;
      }
      nodes[Q_[index]].distance = key;

      //heapify
      int i = index;
      int parent = i/2;
      while (i > 0 && (nodes[Q_[parent]].distance > nodes[Q_[i]].distance)){
        exchange(parent, i);
        i = parent;
        parent = i/2;
      }
      // cout << "CHANGEKEY DONE, now top at: " << Q_[0] + 1 << endl;

    }

    void minHeapify(int i){
        int minindex = i;
        int left = 2*i;
        int right = 2*i + 1;

        if (left <= end_ && nodes[Q_[left]].distance < nodes[Q_[i]].distance)
          minindex = left;
        if (right <= end_ && nodes[Q_[right]].distance < nodes[Q_[i]].distance)
          minindex = right;

        if (minindex != i){
          exchange(i, minindex);
          minHeapify(minindex);
        }
    }

    int deleteMin(){
      int min = Q_[0];
      Q_[0] = Q_[end_];
      end_ = end_ - 1;
      minHeapify(0);
      // cout << "DELETION DONE, now top at: " << Q_[0] + 1 << endl;
      return min;
    }

    int top(){
      return Q_[0];
    }
};

class Graph
{
    private:
        int V_;
        std::vector<Edge> * AdjList_;

    protected:

      // checks if the edge pre-exists in graph or not
      bool isNewEdge(int src, int des){
        vector<Edge>::iterator i;
        for (i = AdjList_[src].begin(); i != AdjList_[src].end(); ++i){
            if ( i->destination == des){
              return false;
            }
        }
        return true;
      }

    public:
        Graph(int V){
            V_ = V;
            AdjList_ = new std::vector<Edge> [V];
            // cout << "Graph initiated successfully!" << endl;
        }

        // Adding Edge to Graph
        void addEdge(int src, int dest, long long int w){
            if (isNewEdge(src, dest)){
              Edge e;
              e.destination = dest;
              e.weight = w;
              AdjList_[src].push_back(e);
              // cout << "added edge from " << src + 1 << "->" << dest + 1 << " with weight: " << w << endl;
            }
        }

        void initSingleSource(int source){
            nodes = new Vertex [V_];
            int i = 0;
            for(i = 0; i < V_; i++){
              nodes[i].distance = INT_MAX;
              nodes[i].parent = -1;
            }
            nodes[source].distance = 0;
        }

        void dijkstraSingleSource(int source){
          initSingleSource(source);
          MinPriorityQueue Q(V_);
          for(int i = 0; i < V_; i++){
            Q.insert(i);
          }
          while (! Q.isEmpty()){
            int u = Q.deleteMin();
            vector<Edge>::iterator i;
            for (i = AdjList_[u].begin(); i != AdjList_[u].end(); ++i){
                int v = i-> destination;
                long long int w = i-> weight;
                // cout << "Considering: "<< u+1 << "->" << v+1 << endl;
                if (nodes[v].distance > nodes[u].distance + w){
                  // cout << "Your connection is changing: " << u+1 << " -> " << v+1 << endl;
                  nodes[v].distance = nodes[u].distance + w;
                  nodes[v].parent = u;
                  Q.changeKey(v, nodes[u].distance + w);
                }
            }
          }
        }

};

int main(){

  int N, S, Degree;
  long long int C[2], D[2], W[3];
  cin >> N;          // Number of vertices in graph
  cin >> S;          // Source Vertex
  cin >> Degree;     // Max degree in graph
  cin >> C[0] >> C[1] >> D[0] >> D[1] >> W[0] >> W[1] >> W[2];

  //initialize graph
  Graph G(N);

  for(int src = 0; src < N; src++){
    int i = src + 1;
    int deg = (i*C[1] + i*i*D[1]) % Degree;
    for (int j = 1; j <= deg; j++){
      int des = (i*C[0] + j*D[0]) % N;
      long long int w = (i*W[0] + j*W[1] ) % W[3];
      G.addEdge(src, des, w);
    }
  }

  G.dijkstraSingleSource(S-1);

  for(int i = 0; i < N; i++){
    if(nodes[i].distance == INT_MAX)
      nodes[i].distance = -1;
    cout << i + 1 << " " << nodes[i].distance << endl;
  }
  return 0;
}
