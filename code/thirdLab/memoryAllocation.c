#include <stdio.h>
#include <stdlib.h>

void main() {
    int *a;
    float *b;
    int c[10];
    printf("Address of pointer\n");
    printf("%p\n", &a);
    printf("%p\n", &b);
    printf("\nEffective address\n");
    printf("%p\n", a);
    printf("%p\n", b);
    a = (int *)malloc(10 * sizeof(int));
    printf("\nAfter malloc the pointer a\n");
    printf("%p\n", a);
    printf("%p\n", &a[0]);
    printf("%p\n", &a[9]);
    printf("\nArray c\n");
    printf("%p\n", c);
    printf("%p\n", &c[0]);
    printf("%p\n", &c[9]);
    b = (float *)malloc(10 * sizeof(float));
    printf("\nAfter malloc the pointer b\n");
    printf("%p\n", b);
    printf("%p\n", &b[0]);
    printf("%p\n", &b[9]);
    a = (int *)realloc(a, 1000 * sizeof(int));
    printf("\nAfter realloc the pointer a\n");
    printf("%p\n", a);
    printf("%p\n", &a[0]);
    printf("%p\n", &a[9]);
    printf("%p\n", &a[999]);
    free(a);
    free(b);
}