#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


extern float asm_dot_product(const float *A, const float *B, int n);


float c_dot_product(const float *A, const float *B, int n) {
    float sdot = 0.0f;
    int i;
    for (i = 0; i < n; i++) {
        sdot += A[i] * B[i];
    }
    return sdot;
}

int main() {
    int n; 

    
    printf("Enter the size of the vectors (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid vector size. Exiting.\n");
        return EXIT_FAILURE;
    }

    
    float *A = (float *)_aligned_malloc(n * sizeof(float), 32);
    float *B = (float *)_aligned_malloc(n * sizeof(float), 32);
    if (!A || !B) {
        printf("Memory allocation failed. Exiting.\n");
        return EXIT_FAILURE;
    }

    
    printf("Enter %d elements for vector A:\n", n);
    int i;
    for (i = 0; i < n; i++) {
        if (scanf("%f", &A[i]) != 1) {
            printf("Invalid input for vector A. Exiting.\n");
            _aligned_free(A);
            _aligned_free(B);
            return EXIT_FAILURE;
        }
    }

   
    printf("Enter %d elements for vector B:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%f", &B[i]) != 1) {
            printf("Invalid input for vector B. Exiting.\n");
            _aligned_free(A);
            _aligned_free(B);
            return EXIT_FAILURE;
        }
    }

    
    clock_t start, end;
    float c_result, asm_result;

    start = clock();
    c_result = c_dot_product(A, B, n);
    end = clock();
    double c_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("C Kernel Result: %f | Time: %lf sec\n", c_result, c_time);

    
    start = clock();
    asm_result = asm_dot_product(A, B, n);
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Assembly Kernel Result: %f | Time: %lf sec\n", asm_result, asm_time);

    
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
