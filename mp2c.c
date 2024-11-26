#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Declare the external assembly function
extern float asm_dot_product(const float *A, const float *B, int n);

// Function to compute dot product in C
float c_dot_product(const float *A, const float *B, int n) {
    float sdot = 0.0f;
    int i;
    for (i = 0; i < n; i++) {
        sdot += A[i] * B[i];
    }
    return sdot;
}

// Function to initialize vectors with random values
void generate_random_vector(float *vec, int n) {
	int i;
    for ( i = 0; i < n; i++) {
        vec[i] = (float)rand() / RAND_MAX; // Random float in [0, 1)
        
        // Optional: Print each element of the vector (useful for debugging)
        // printf("Vector A[%d]: %f\n", i, vec[i]); 
    }
}

int main() {
    int iterations = 20; // Number of repetitions for timing

    // Prompt user for input
    int n_exp;
    printf("Enter the exponent for vector size (n = 2^n): ");
    scanf("%d", &n_exp);

    int n = 1 << n_exp; // Compute vector size as 2^n
    printf("\nTesting vector size n = 2^%d (%d elements):\n", n_exp, n);

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Allocate memory for vectors
    float *A = (float *)_aligned_malloc(n * sizeof(float), 32);
    float *B = (float *)_aligned_malloc(n * sizeof(float), 32);
    if (!A || !B) {
        printf("Memory allocation failed. Exiting.\n");
        return EXIT_FAILURE;
    }

    // Initialize vectors with random values
    generate_random_vector(A, n);
    generate_random_vector(B, n);

    clock_t start, end;
    float c_result = 0.0f, asm_result = 0.0f;
	int i;
    // Time the C kernel
    start = clock();
    for ( i = 0; i < iterations; i++) {
        c_result = c_dot_product(A, B, n);
    }
    end = clock();
    double c_time = (double)(end - start) / CLOCKS_PER_SEC / iterations;
    printf("C Kernel Avg Time: %lf sec\n", c_time);

    // Time the assembly kernel
    start = clock();
    for ( i = 0; i < iterations; i++) {
        asm_result = asm_dot_product(A, B, n);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC / iterations;
    printf("Assembly Kernel Avg Time: %lf sec\n", asm_time);

    // Display the dot product results
    printf("C Kernel Result: %f\n", c_result);
    printf("Assembly Kernel Result: %f\n", asm_result);

    // Verify correctness
    if (fabs(c_result - asm_result) < 1e-5) {
        printf("Results match!\n");
    } else {
        printf("Results do NOT match!\n");
    }

    // Free allocated memory
    _aligned_free(A);
    _aligned_free(B);

    return 0;
}

