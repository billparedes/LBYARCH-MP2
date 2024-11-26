#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Declare the external assembly function
extern float asm_dot_product(float *A, float *B, int n);

// Function to compute dot product in C
float c_dot_product(float *A, float *B, int n) 
{
    float sdot = 0.0f;
    int i;
    for (i = 0; i < n; i++) 
	{
        sdot += A[i] * B[i];
    }
    return sdot;
}

// Function to initialize vectors with random values
void generate_random_vector(float *vec, int n) 
{
	int i;
    for ( i = 0; i < n; i++) 
	{
        vec[i] = (float)rand() / RAND_MAX; // Random float in [0, 1)
        
        // Printing of values in the vector
        // printf("Vector [%d]: %f\n", i, vec[i]); 
    }
}

int main() 
{
	// number of times to be repeated for calculation of average time
    int iterations = 20;
	 
    // user input
    int nSize;
    printf("Enter the exponent for vector size (n = 2^n): ");
    scanf("%d", &nSize);


	// computation of vector size as 2^n 
    int n = 1 << nSize; 
    printf("\n Vector size n = 2^%d (%d elements):\n", nSize, n);


    // Seed the random number generator
    srand((unsigned int)time(NULL));


    // Allocate memory for vectors
    float *A = (float *) malloc(n * sizeof(float));
    float *B = (float *) malloc(n * sizeof(float));


    // Initialize vectors with random values
    generate_random_vector(A, n);
    generate_random_vector(B, n);


    clock_t start, end;
    float c_result = 0.0f, asm_result = 0.0f;
	int i;
	
    // Time the C kernel
    start = clock();
    for ( i = 0; i < iterations; i++)
	{
        c_result = c_dot_product(A, B, n);
    }
    end = clock();
    double c_time = (double)(end - start) / CLOCKS_PER_SEC / iterations;
    printf("C Kernel Avg Time (in seconds): %f \n", c_time);


    // Time the assembly kernel
    start = clock();
    for ( i = 0; i < iterations; i++) 
	{
        asm_result = asm_dot_product(A, B, n);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC / iterations;
    printf("Assembly Kernel Avg Time (in seconds): %f\n", asm_time);

    // Display the dot product results
    printf("C Kernel Result: %f\n", c_result);
    printf("Assembly Kernel Result: %f\n", asm_result);

    // Verify correctness
    if (fabs(c_result - asm_result) < 1e-5) 
	{
        printf("The C Kernel and Assembly Kernel are the same\n");
    } 
	else 
	{
        printf("The C Kernel and Assembly Kernel are NOT the same\n");
    }

    // Free allocated memory
    free(A);
    free(B);

    return 0;
}
