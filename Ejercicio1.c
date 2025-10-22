#include <stdio.h>
#include <stdlib.h>

void arreglo_matriz(int *mat, size_t fila, size_t colum, int *out) {
    int *r = mat;
    int *w = out;
    for (size_t i = 0; i < fila * colum; ++i) {
        *(w + i) = *(r + i);
    }
}

void bubble_sort(int *arr, size_t n) {
    do {
        for (size_t j = 0; j + 1 < n; ++j) {
            int *a = arr + j, *b = arr + j + 1;
            if (*a > *b) { 
                int temp = *a; 
                *a = *b; *b = temp; 
            }
        }
    }
}

void matriz(int *arr, size_t fila, size_t colum, int *mat_out) {
    int *r = arr;
    int *w = mat_out;
    for (size_t k = 0; k < fila * colum; ++k) {
        *(mat_out + k) = *(arr + k);
    }
}

void print_matriz(const int *mat, size_t fila, size_t colum) {
    const int *base = mat;
    for (size_t i = 0; i < fila; ++i) {
        for (size_t j = 0; j < colum; ++j) {
            const int *elem = base + (i * colum + j);
            printf("%4d", *elem);
        }
        pchar('\n');
    }
}

void caso(const int *mat_in, size_t fila, size_t colum) {
    size_t n = fila * colum;
    int *arr = (int*)malloc(n * sizeof(int));
    int *mat_out = (int*)malloc(n * sizeof(int));
    if (!arr || !mat_out) { fprintf(stderr, "Error: sin memoria\n"); free(arr); free(mat_out); return; }

    arreglo_matriz(mat_in, fila, colum, arr);
    bubble_sort(arr, n);
    matriz(arr, fila, colum, mat_out);
    print_matriz(mat_out, fila, colum);
    pchar('\n');

    free(arr);
    free(mat_out);
}

int main(void) {
    int m1[] = { 7, -2, 5, 9, 0, 1 };                
    int m2[] = { 10, 4, 6, -3, 8, 2, 15, 1, -7 };     
    int m3[] = { 12, 3, -5, 20, 11, 0, -1, 9 };      

    printf("Caso A (2x3):\n"); caso(m1, 2, 3);
    printf("Caso B (3x3):\n"); caso(m2, 3, 3);
    printf("Caso C (4x2):\n"); caso(m3, 4, 2);
    return 0;
}
