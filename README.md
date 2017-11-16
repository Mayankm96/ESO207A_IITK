## 1. Implement Fast Fourier Transformation (FFT) and its inverse

### Problem:
To implement the recursive FFT algorithm and FFT inverse algorithm

### Input:
* First input `num`: Number of times the cases would be inputed
* Secont input `input`: 0 means FFT computation, 1 means Inverse FFT computation
* Third input `n`: Degree of polynomial
* Subsequent inputs are complex numbers which are the coordinates of the polynomial (in case of FFT), and coordinate of given DFT (in case of inverse FFT)

### Usage:
```bash
g++ -o fft fft.cpp
./fft.out

# example:
2
0 4 0 0 1.0 0 2.0 0 3.0 0
1 4 6.0 0 -2.0 -2.0 -2.0 0 -2.0 2.0
```
## 2. Implement Basic Caluclator (using stacks)

## 3. Implement Strongly Connected Components (using depth first search)

## 4. Implement Dijkstra's Algorithm (using min priority queue)

### Problem:
To solve the single source shortest path problem for a given directed weighted graph (with no negative weight edges) using Dijkstra’s Algorithm.

### Input:
Input is of form: `N, Source, D, C_1 , C_2 , D_1, D_2,  W_1 , W_2, W_3`, where,
* `N`: Number of nodes in the graph (numbered 1,2...N )
* `D`: Max outdegree of any node
* `Source`: The source node (between 1 and N inclusive)
* `C_1, C_2, D_1, D_2, W_1, W_2, W_3` are some constants

### Usage:
```bash
g++ .o dijk dijkstra.cpp
./dijk

# Test Input
10 6 4 315 567 647 270 15 35 1000
```

__NOTE:__ To view detailed background processing information, change [line 7](https://github.com/Mayankm96/ESO207A_IITK/blob/master/assgn_4/dijkstra.cpp#L7) to
``` C++
#define DEBUG true
```

### Test Cases:

For test input: `10 6 4 315 567 647 270 15 35 1000`, output would be:
```
1 -1
2 -1
3 270
4 -1
5 160
6 0
7 420
8 125
9 -1
10 385
```
