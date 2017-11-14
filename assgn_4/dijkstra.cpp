#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

#define DEBUG false
typedef long long int llint;

using namespace std;

// structure Vertex for Dijkstra's Algorithm
struct Vertex{
  llint distance;       // distance
  llint parent;         // predecessor
};

// structure Edge to store the weighted graph edges
struct Edge{
  llint destination;    // destination node's ID
  llint weight;         // edge weight
};

// Global variables to store nodes information
Vertex * nodes;

class MinPriorityQueue{
  private:
    llint * Q_;   // queue
    llint end_;   // last element present in the queue
    llint size_;  // initialized size of queue

  protected:
    llint * location_;  // location of a node id in queue

    llint leftNode(llint i){
      return 2*i + 1;
    }

    llint rightNode(llint i){
      return 2*i + 2;
    }

    llint parentNode(llint i){
      return (i-1)/2;
    }

    // perform exchange between two array indices
    void exchange(llint a, llint b){
      // modifying location
      location_[Q_[a]] = b;
      location_[Q_[b]] = a;

      // swapping in heap
      llint tmp = Q_[a];
      Q_[a] = Q_[b];
      Q_[b] = tmp;
    }

    // returns the index of a node id in the queue
    llint searchID(llint id){
      return location_[id];
    }

    // performs the min heapify method
    void minHeapify(llint i){
        llint minindex = i;
        llint left = leftNode(i);
        llint right = rightNode(i);

        if (left <= end_ && nodes[Q_[left]].distance < nodes[Q_[i]].distance)
          minindex = left;
        if (right <= end_ && nodes[Q_[right]].distance < nodes[Q_[i]].distance)
          minindex = right;

        if (minindex != i){
          exchange(i, minindex);
          minHeapify(minindex);
        }
    }

  public:
    MinPriorityQueue(llint V){
      Q_ = new llint [V];
      location_ = new llint [V];
      size_ = V;
      end_ = -1;
    }

    // checks if heap is empty or not
    bool isEmpty(){
      if(end_ == -1)
        return 1;
      else
        return 0;
    }

    // insert a new element into the heap
    void insert(llint id){
      end_ = end_ + 1;

      if (end_ >= size_){
        return;
      }

      Q_[end_] = id;
      location_[id] = end_;

      //heapify
      llint i = end_;
      llint parent = parentNode(i);
      while (i > 0 && (nodes[Q_[parent]].distance > nodes[Q_[i]].distance)){
        exchange(parent, i);
        i = parent;
        parent = parentNode(i);
      }
    }

    // change the key for a node with id in the heap
    void changeKey(llint id, llint key){
      llint index = searchID(id);

      //heapify
      llint i = index;
      llint parent = parentNode(i);
      while (i > 0 && (nodes[Q_[parent]].distance > nodes[Q_[i]].distance)){
        exchange(parent, i);
        i = parent;
        parent = parentNode(i);
      }
      if (DEBUG)
        cout << "CHANGEKEY DONE, now top at: " << Q_[0] + 1 << endl;

    }

    // delete the smallest element present in the queue
    llint deleteMin(){
      llint min = Q_[0];
      Q_[0] = Q_[end_];
      end_ = end_ - 1;
      minHeapify(0);
      location_[min] = -1;
      if (DEBUG)
        cout << "DELETION DONE, now top at: " << Q_[0] + 1 << endl;
      return min;
    }

    // check if a given node id is present in the heap or not
    bool isInHeap(llint id){
      if(location_[id] == -1)
        return false;
      else
        return true;
    }
};

class Graph
{
    private:
        llint V_;
        std::vector<Edge> * AdjList_;

    protected:
      // perform the initialization of source for Dijkstra's algorithm
      void initSingleSource(llint source){
        nodes = new Vertex [V_];
        llint i = 0;
        for(i = 0; i < V_; i++){
          nodes[i].distance = LLONG_MAX;
          nodes[i].parent = -1;
        }
        nodes[source].distance = 0;
      }

    public:
        Graph(llint V){
            V_ = V;
            AdjList_ = new std::vector<Edge> [V];
            if (DEBUG)
              cout << "Graph initiated successfully!" << endl;
        }

        // Adding Edge to Graph
        void addEdge(llint src, llint dest, llint w){
            Edge e;
            e.destination = dest;
            e.weight = w;
            AdjList_[src].push_back(e);
            if (DEBUG)
              cout << "added edge from " << src + 1 << "->" << dest + 1 << " with weight: " << w << endl;
        }

        // perfrom Dijkstra's Algorithm for shortest path searches
        void dijkstraSingleSource(llint source){
          // singe source initialization
          initSingleSource(source);

          // initialize min priority queue
          MinPriorityQueue Q(V_);
          for(llint i = 0; i < V_; i++){
            Q.insert(i);
          }

          while (! Q.isEmpty()){
            llint u = Q.deleteMin();
            vector<Edge>::iterator i;
            for (i = AdjList_[u].begin(); i != AdjList_[u].end(); ++i){
                llint v = i-> destination;
                llint w = i-> weight;
                if (DEBUG)
                  cout << "Considering: "<< u+1 << "->" << v+1 << endl;
                // check for relax edge conditions
                if (nodes[v].distance > nodes[u].distance + w && Q.isInHeap(v) && nodes[u].distance!=LLONG_MAX){
                  if (DEBUG)
                    cout << "Your connection is changing: " << u+1 << " -> " << v+1 << endl;
                  nodes[v].distance = nodes[u].distance + w;
                  nodes[v].parent = u;
                  Q.changeKey(v, nodes[u].distance + w);
                }
            }
          }
        }

};

int main(){

  llint N, S, Degree;
  llint C[2], D[2], W[3];
  cin >> N;          // Number of vertices in graph
  cin >> S;          // Source Vertex
  cin >> Degree;     // Max degree in graph
  cin >> C[0] >> C[1] >> D[0] >> D[1] >> W[0] >> W[1] >> W[2];

  //initialize graph
  Graph G(N);

  // add edges to the graph
  for(llint src = 0; src < N; src++){
    llint i = src + 1;
    llint deg = (i*C[1] + i*i*D[1]) % Degree;
    for (llint j = 1; j <= deg; j++){
      llint des = (i*C[0] + j*D[0]) % N;
      llint w = (i*W[0] + j*W[1] ) % W[3];
      G.addEdge(src, des, w);
    }
  }

  G.dijkstraSingleSource(S-1);

  // print output
  for(llint i = 0; i < N; i++){
    // not reachable nodes
    if(nodes[i].distance == LLONG_MAX)
      nodes[i].distance = -1;
    cout << i + 1 << " " << nodes[i].distance << endl;
  }
  return 0;
}
