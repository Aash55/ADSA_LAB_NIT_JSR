#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

void badCharShift(char *pat, int m, int badchar[]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < m; i++)
        badchar[(unsigned char)pat[i]] = i;
}

void boyerMoore(char *txt, char *pat) {
    int n = strlen(txt), m = strlen(pat);
    int badchar[NO_OF_CHARS];

    badCharShift(pat, m, badchar);

    int s = 0; // shift position
    while (s <= n - m) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            int shift = j - badchar[(unsigned char)txt[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

int main() {
    char text[] = "ABAAABCD";
    char pattern[] = "ABC";
    boyerMoore(text, pattern);
    return 0;
}