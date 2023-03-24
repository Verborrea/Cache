#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define BLOCKS 10

void fillMatrix(int *M[MAX], bool zero = false)
{
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			M[i][j] = (zero ? 0 : rand()%10+1);
		}
	}
}

void print(int *M[MAX])
{
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			std::cout << M[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void multiply(int *A[MAX], int *B[MAX], int *C[MAX])
{
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < MAX; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void blocks(int *A[MAX], int *B[MAX], int *C[MAX], int b)
{
	for (int ii = 0; ii < MAX; ii+=b) {
		for (int jj = 0; jj < MAX; jj+=b) {
			for (int kk = 0; kk < MAX; kk+=b) {
				for (int i = ii; i < ii + b; i++) {
					for (int j = jj; j < jj + b; j++) {
						for (int k = kk; k < kk + b; k++) {
							C[i][j] += A[i][k] * B[k][j];
						}
					}
				}
			}
		}
	}
}

int main()
{
	srand (time(NULL));

	int **A = new int*[MAX];
	int **B = new int*[MAX];
	int **C = new int*[MAX];

	for (int i = 0; i < MAX; i++) {
		A[i] = new int[MAX];
		B[i] = new int[MAX];
		C[i] = new int[MAX];
	}

	fillMatrix(A);
	fillMatrix(B);
	fillMatrix(C, true);

	auto start = std::chrono::steady_clock::now();
	multiply(A,B,C);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
	std::cout << "Classic time: " << elapsed_seconds.count() << "ms\n";

	fillMatrix(C, true); 	//Resetear la matriz C

	auto start = std::chrono::steady_clock::now();
	blocks(A,B,C,BLOCKS);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> elapsed_seconds = end-start;
	std::cout << "Blocks time: " << elapsed_seconds.count() << "ms\n";

	for (int i = 0; i < MAX; ++i) {
		delete [] A[i];
		delete [] B[i];
		delete [] C[i];
	}
	delete [] A;
	delete [] B;
	delete [] C;

	return 0;
}