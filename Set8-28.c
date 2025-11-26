// clique_search.c
// Compile: gcc -O2 -std=c99 clique_search.c -o clique_search
// Run: ./clique_search < input.txt

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int n, e, m;
uint64_t adj[64];
int found = 0;
uint64_t found_mask = 0;

// count bits set
static inline int popcnt(uint64_t x){ return __builtin_popcountll(x); }

// choose pivot from (P|X) that maximizes |P & N(u)|
int choose_pivot(uint64_t P, uint64_t X){
    uint64_t PX = P | X;
    int best = -1, bestcnt = -1;
    while(PX){
        int v = __builtin_ctzll(PX);
        PX &= PX - 1;
        int cnt = popcnt(P & adj[v]);
        if(cnt > bestcnt){ bestcnt = cnt; best = v; }
    }
    return best;
}

// recursive Bron-Kerbosch with pivot; stops when a clique of size m found
void bronk(uint64_t R, uint64_t P, uint64_t X){
    if(found) return;                  // early exit if found
    if(popcnt(R) >= m){                // success
        found = 1; found_mask = R; return;
    }
    if(P == 0) return;                 // no more candidates
    // pruning: if even taking all P cannot reach m, stop
    if(popcnt(R) + popcnt(P) < m) return;

    int u = choose_pivot(P, X);
    uint64_t skip = u>=0 ? (P & ~adj[u]) : P; // vertices in P not adjacent to pivot
    while(skip){
        int v = __builtin_ctzll(skip);
        skip &= skip - 1;
        uint64_t vv = (1ULL<<v);
        bronk(R | vv, P & adj[v], X & adj[v]);
        if(found) return;
        P &= ~vv;
        X |= vv;
        // further pruning: if popcnt(R) + popcnt(P) < m then no need to continue
        if(popcnt(R) + popcnt(P) < m) return;
    }
}

int main(){
    if(scanf("%d %d %d", &n, &e, &m) != 3) return 0;
    if(n <= 0 || m <= 0 || m > n){ printf("Invalid n or m\n"); return 0; }
    if(n > 64){ printf("This program supports n <= 64\n"); return 0; }
    for(int i=0;i<n;i++) adj[i]=0;
    for(int i=0;i<e;i++){
        int a,b; scanf("%d %d", &a, &b); // 1-based input
        if(a<1||a>n||b<1||b>n) continue;
        a--; b--;
        if(a==b) continue;
        adj[a] |= (1ULL<<b);
        adj[b] |= (1ULL<<a);
    }

    // initial sets: R = 0, P = all vertices, X = 0
    uint64_t P = (n==64) ? ~0ULL : ((1ULL<<n)-1);
    bronk(0, P, 0);

    if(found){
        printf("YES: a clique of size %d exists\n", m);
        // print vertex list (1-based)
        int printed = 0;
        for(int i=0;i<n;i++){
            if(found_mask & (1ULL<<i)){
                if(printed) printf(" ");
                printf("%d", i+1);
                printed++;
                if(printed==m) break;
            }
        }
        printf("\n");
    } else {
        printf("NO: no clique of size %d found\n", m);
    }
    return 0;
}
