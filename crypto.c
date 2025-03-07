#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MOD 26

// Function to compute determinant of a 2x2 matrix (extendable for higher sizes)
int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}

// Function to find the modular inverse of a number mod 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) 
            return x;
    }
    return -1;
}

// Function to accept a key matrix (N x N) and convert letters to numbers (A=0, ..., Z=25)
void acceptKeyMatrix(int key[2][2]) {
    int det, detInv;
    char input[3]; // Buffer for single letter input

    while (1) {
        printf("Enter the 2x2 key matrix (letters A-Z or numbers 0-25):\n");

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                scanf("%s", input);

                // Convert letter to number (if letter input)
                if (isalpha(input[0])) {
                    key[i][j] = toupper(input[0]) - 'A'; 
                } else {
                    key[i][j] = atoi(input); // Convert number input to integer
                }

                // Validate range (0-25)
                if (key[i][j] < 0 || key[i][j] >= 26) {
                    printf("Invalid input! Enter letters A-Z or numbers between 0-25.\n");
                    j--; // Re-enter this value
                }
            }
        }

        // Compute determinant
        det = determinant(key);
        det = (det % MOD + MOD) % MOD; // Ensure positive modulo

        // Check if determinant has an inverse mod 26
        detInv = modInverse(det, MOD);
        if (detInv != -1) {
            printf("Key matrix accepted.\n");
            break;
        } else {
            printf("Invalid key matrix! It is not invertible mod 26. Please enter another matrix.\n");
        }
    }
}

int main() {
    int key[2][2];

    // Accept the key matrix
    acceptKeyMatrix(key);

    // Display the accepted matrix
    printf("Accepted Key Matrix (Number Format):\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    return 0;
}
