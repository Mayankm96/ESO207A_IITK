# ESO207A_IITK

## Implement Fast Fourier Transformation (FFT) and its inverse

### Problem:
To implement the recursive FFT algorithm and FFT inverse algorithm.
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

