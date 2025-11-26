#include <stdio.h>
#include <string.h>

#define d 256        // number of characters in input alphabet
#define q 101        // a prime for hashing

void rabinKarp(char pat[], char txt[]) {
    int m = strlen(pat), n = strlen(txt);
    int h = 1, p = 0, t = 0;

    // h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide over text
    for (int i = 0; i <= n - m; i++) {

        if (p == t) { // hash match
            int j=0;
            while (j < m && txt[i+j] == pat[j]) j++;
            if (j == m) printf("Pattern found at index %d\n", i);
        }

        if (i < n - m) { // next hash
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}

int main() {
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";
    rabinKarp(pattern, text);
    return 0;
}