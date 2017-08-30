#include <iostream>
#include <stdio.h>
#include <math.h>

#define PI (double)acos(-1.0)
using namespace std;

struct complex{
	double real;
	double imag;
};

//Multiply two complex numbers
complex c_multiply(complex a, complex b){
	complex c;
	c.real = a.real*b.real - a.imag*b.imag;
	c.imag = a.real*b.imag + a.imag*b.real;
	return c;
}

//Add two complex numbers
complex c_add(complex a, complex b){
	complex c;
	c.real = a.real + b.real;
	c.imag = a.imag + b.imag;
	return c;
}

//Divide complex number by scalar
complex s_divide(complex a, float n){
	complex c;
	c.real = a.real/n;
	c.imag = a.imag/n;
	return c;
}

//Subtract two complex numbers
complex c_subtract(complex a, complex b){
	complex c;
	c.real = a.real - b.real;
	c.imag = a.imag - b.imag;
	return c;
}

complex * recursive_FFT(complex * C, int n){
	complex w, w_n;
	w.real = 1;
	w.imag = 0;
	w_n.real = cos(2.0*PI/n);
	w_n.imag = sin(2.0*PI/n);
	if (n==1)
		return C;

	//define vectors corresponding to odd and even pairs
	//NOTE: n is a power of 2
	complex * C_odd = new complex[n/2];
	complex * C_even = new complex[n/2];
	for(int i=0; i<n/2; i++){
		C_even[i] = C[2*i];
		C_odd[i] = C[2*i+1];
	}

	//Perform divide step
	complex * Y_odd = recursive_FFT(C_odd, n/2);
	complex * Y_even = recursive_FFT(C_even, n/2);

	//Perform conquer step
	complex * Y = new complex[n];
	for(int k=0; k<n/2; k++){
		Y[k] = c_add(Y_even[k], c_multiply(w, Y_odd[k]));
		Y[k+n/2] = c_subtract(Y_even[k], c_multiply(w, Y_odd[k]));

		w = c_multiply(w, w_n);
	}
	return Y;
}

complex * recursive_invFFT(complex * Y, int n){
	complex w, w_n;
	w.real = 1;
	w.imag = 0;
	w_n.real = cos(2*PI/n);
	w_n.imag = -1.0*sin(2*PI/n);

	if (n==1)
		return Y;

	//define vectors corresponding to odd and even pairs
	//NOTE: n is a power of 2
	complex * Y_odd = new complex[n/2];
	complex * Y_even = new complex[n/2];
	for(int i=0; i<n/2; i++){
		Y_even[i] = Y[2*i];
		Y_odd[i] = Y[2*i+1];
	}

	//Perform divide step
	complex * C_odd = recursive_invFFT(Y_odd, n/2);
	complex * C_even = recursive_invFFT(Y_even, n/2);

	//Perform conquer step
	complex * C = new complex[n];
	for(int k=0; k<n/2; k++){
		C[k] = c_add(C_even[k], c_multiply(w, C_odd[k]));
		C[k+n/2] = c_subtract(C_even[k], c_multiply(w, C_odd[k]));

		w = c_multiply(w, w_n);
	}
	return C;
}

int main() {
	// input 0 or 1 from user
	int num;
	cin >> num;
	while(num--){
		int input;
		cin>>input;

		if (input==0) { // perform FFT operation
			// take degree of polynomial n
			int n;
			cin>>n;

			complex * C = new complex[n];

			for(int i=0; i<n; i++){
				cin>>C[i].real;
				cin>>C[i].imag;
			}
			complex * Y = recursive_FFT(C, n);

			//cout << n << " ";
			for(int i=0; i<n; i++){
				printf("%.6lf %.6lf\n", Y[i].real, Y[i].imag);
			}
		}
		else if (input==1) { //perform inverse FFT operation
				int n;
				cin>>n;

				complex * Y = new complex[n];

				for(int i=0; i<n; i++){
					cin>>Y[i].real;
					cin>>Y[i].imag;
				}
				complex * C = recursive_invFFT(Y, n);

				//cout << n << " ";
				for(int i=0; i<n; i++){
					C[i] = s_divide(C[i], n);
					printf("%.6lf %.6lf\n", C[i].real, C[i].imag);
				}
			}
	}
	return 0;
}
