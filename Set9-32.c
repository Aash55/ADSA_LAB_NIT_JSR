#include <stdio.h>
#include <string.h>

void computeLPS(char pat[], int m, int lps[]) {
    int len = 0;
    lps[0] = 0;

    for (int i = 1; i < m; ) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else if (len != 0)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
}

void KMP(char pat[], char txt[]) {
    int m = strlen(pat), n = strlen(txt);
    int lps[m], i = 0, j = 0;

    computeLPS(pat, m, lps);

    while (i < n) {
        if (pat[j] == txt[i]) { i++; j++; }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && pat[j] != txt[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    KMP(pattern, text);
    return 0;
}