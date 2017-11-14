#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// structure Vertex for Dijkstra's Algorithm
struct Vertex{
  int d;            // distance
  int parent;       // predecessor
};

struct Edge{
  int des;         // destination node's ID
  float weight;     // edge weight
};

// Global class to sotre the nodes information
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

  public:
    MinPriorityQueue(int i){
      Q_ = new int [i];
      size_ = i;
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

      if (end_ < size_){
        Q_[end_] = id;
      }
      //heapify
    }

    void min_heapify(int i){
        int minindex = i;
        int left = 2*i;
        int right = 2*i + 1;
        if (left <= end_ && nodes[Q_[left]].d < nodes[Q_[i]].d)
          minindex = left;
        if (right <= end_ && nodes[Q_[right]].d < nodes[Q_[i]].d)
          minindex = right;
        if (minindex != i){
          exchange(i, minindex);
          min_heapify(minindex);
        }
    }

    int extract_min(){
      int min = Q_[0];
      Q_[0] = Q_[end_];
      end_ = end_ - 1;
      min_heapify(0);
      return min;
    }
};
