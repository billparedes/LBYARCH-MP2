#include <stdio.h>
#include <stdlib.h>

extern float dot_product_asm(float *A, float *B, int n);

float dot_product_c(float *A, float *B, int n) {
    float result = 0.0f;
    int i;
    for (i = 0; i < n; i++) {
        result += A[i] * B[i];
    }
    return result;
}

int main() {
    int n = 20; // Fixed length of 20 elements

    // Dynamically allocate memory for vectors A and B
    float *A = (float *)malloc(4 * sizeof(float));
    float *B = (float *)malloc(4 * sizeof(float));


    // Initialize vectors with values
    int i;
    for (i = 0; i < n; i++) {
        A[i] = (float)(i + 1);
        B[i] = (float)(i + 1);
    }

    // Call the assembly function
    float result_asm = dot_product_asm(A, B, n);

    // Compute the dot product in C (for verification)
    float result_c = dot_product_c(A, B, n);

    // Display results
    printf("Dot product (ASM): %f\n", result_asm);
    printf("Dot product (C): %f\n", result_c);

    // Free the dynamically allocated memory
    free(A);
    free(B);

    return 0;
}

