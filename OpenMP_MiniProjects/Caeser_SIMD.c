#include <stdio.h>
#include <string.h>
#include <omp.h>

#define N 100  // Maximum number of characters

// Encrypt function (short name: enc)
void enc(char *t, int s) {
#pragma omp simd
    for (int i = 0; i < N; i++) {
        if (t[i] >= 'A' && t[i] <= 'Z') {
            t[i] = ((t[i] - 'A' + s) % 26) + 'A';
        }
    }
}

// Decrypt function (short name: dec)
void dec(char *t, int s) {
#pragma omp simd
    for (int i = 0; i < N; i++) {
        if (t[i] >= 'A' && t[i] <= 'Z') {
            t[i] = ((t[i] - 'A' - s + 26) % 26) + 'A';
        }
    }
}

int main() {
    char text[N];
    int c, s;

    // Get user input
    printf("Enter text (only uppercase letters, max 100 characters):\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline

    printf("Enter shift amount: ");
    scanf("%d", &s);

    printf("Choose operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &c);

    double start = omp_get_wtime();  // Start timing

    switch (c) {
        case 1:
            enc(text, s);
        printf("Encrypted text: %s\n", text);
        break;
        case 2:
            dec(text, s);
        printf("Decrypted text: %s\n", text);
        break;
        default:
            printf("Invalid choice!\n");
        return 1;
    }

    double end = omp_get_wtime();  // End timing

    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
