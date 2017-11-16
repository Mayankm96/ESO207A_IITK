#include <iostream>
#include <stdio.h>
#include <climits>
#include <vector>
#include <utility>

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
    std::vector<llint>  Q_;   // queue
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
      swap(location_[Q_.at(a)],location_[Q_.at(b)]);

      // swapping in heap
      swap(Q_.at(a), Q_.at(b));
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

        if (left < Q_.size() && nodes[Q_.at(left)].distance < nodes[Q_.at(minindex)].distance)
          minindex = left;
        if (right < Q_.size() && nodes[Q_.at(right)].distance < nodes[Q_.at(minindex)].distance)
          minindex = right;

        if (minindex != i){
          exchange(i, minindex);
          minHeapify(minindex);
        }
    }

  public:
    MinPriorityQueue(llint V){
      // Q_.resize(V);
      location_ = new llint [V];
      size_ = V;
    }

    // checks if heap is empty or not
    bool isEmpty(){
      if(Q_.size()==0)
        return 1;
      else
        return 0;
    }
    // a special function to make queue for Dijkstra's Algorithm
    void makeDijQueue(llint V){
      Q_.resize(V);
      llint i;
      for (i = 0; i< V; i++){
				Q_[i] = i;
				location_[i] = i;
			}

			for (i = (V/2)-1; i >= 0; i--){
				minHeapify(i);
			}
    }

    // insert a new element into the heap
    void insert(llint id){
      if (Q_.size() < size_){
        Q_.push_back(id);
        location_[id] = Q_.size()-1;

        //heapify
        llint i = Q_.size()-1;
        llint parent = parentNode(i);
        while (i > 0 && (nodes[Q_.at(parent)].distance > nodes[Q_.at(i)].distance)){
          exchange(parent, i);
          i = parent;
          parent = parentNode(i);
        }
      }
    }

    // change the key for a node with id in the heap
    void changeKey(llint id, llint key){
      llint index = searchID(id);

      //heapify
      llint i = index;
      llint parent = parentNode(i);
      while (i > 0 && (nodes[Q_.at(parent)].distance > nodes[Q_.at(i)].distance)){
        exchange(parent, i);
        i = parent;
        parent = parentNode(i);
      }
      if (DEBUG)
        cout << "CHANGEKEY DONE, now top at: " << Q_.at(0) + 1 << endl;

    }

    // delete the smallest element present in the queue
    llint deleteMin(){
      llint min = Q_[0];
      // excahnge topmost element in queue with the last one
      exchange(0, Q_.size()-1);
      // delete vertex from the queue
      Q_.pop_back();
      location_[min] = -1;
      // reorder the heap
      minHeapify(0);

      if (DEBUG)
        cout << "DELETION DONE, now top at: " << Q_.at(0) + 1 << endl;
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

class Graph {
    private:
        llint V_;
        std::vector<Edge> * AdjList_;

    protected:
      // perform the initialization of source for Dijkstra's algorithm
      void initSingleSource(llint source){
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

          Q.makeDijQueue(V_);
          // for(llint i = 0; i < V_; i++){
          //   Q.insert(i);
          // }

          while (! Q.isEmpty()){
            llint u = Q.deleteMin();
            vector<Edge>::iterator i;
            for (i = AdjList_[u].begin(); i != AdjList_[u].end(); ++i){
                llint v = i-> destination;
                llint w = i-> weight;
                if (DEBUG)
                  cout << "Considering: "<< u+1 << "->" << v+1 << endl;
                // check for relax edge conditions
                if ( Q.isInHeap(v) && nodes[u].distance!=LLONG_MAX && (nodes[v].distance > (nodes[u].distance + w))){
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
  nodes = new Vertex [N];

  // add edges to the graph
  llint i, deg, des, j, w;
  for(llint src = 0; src < N; src++){
    i = src + 1;
    deg = (i*C[1] + i*i*D[1]) % Degree;
    for (j = 1; j <= deg; j++){
      des = (i*C[0] + j*D[0]) % N;
      w = (i*W[0] + j*W[1] ) % W[3];
      G.addEdge(src, des, w);
    }
  }

  G.dijkstraSingleSource(S-1);

  // print output
  for(llint j = 0; j < N; j++){
    // not reachable nodes
    if(nodes[j].distance == LLONG_MAX)
      nodes[j].distance = -1;
    cout << j + 1 << " " << nodes[j].distance << endl;
  }
  return 0;
}
