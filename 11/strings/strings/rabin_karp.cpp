#include "rabin_karp.h"




int d = 2048;



void search(char substr[], char text[], int q)
{
    int M = strlen(substr);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for substr
    int t = 0; // hash value for text
    int h = 1;

    
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of substr and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + substr[i]) % q;
        t = (d * t + text[i]) % q;
    }

   
    for (i = 0; i <= N - M; i++) {

       
        if (p == t) {
           
            for (j = 0; j < M; j++) {
                if (text[i + j] != substr[j]) {
                    break;
                }
            }

            // if p == t and substr[0...M-1] = text[i, i+1,
            // ...i+M-1]

            if (j == M)
                cout << "substrtern found at index " << i
                << endl;
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}
