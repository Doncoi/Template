#include <cstdio>
#include <cstdlib>
#include <cstring>
#define Mod 10000

struct matrix {
    int v[3][3];
    int m, l;
};

matrix get_mul(matrix a,matrix b) {
    matrix c;
    c.m = a.m; c.l = b.l;
    for(int i = 1; i <= c.m; ++ i)
      for(int j = 1; j <= c.l; ++ j) {
          c.v[i][j] = 0;
          for(int k = 1; k <= a.l; ++ k)
              c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j]) % Mod;
      }
    return c;
}

int main() {
    int n;
    while(scanf("%d", &n) && n != -1) {
        if(n == 0) {printf("0\n");continue;}
        matrix a, b, c;
        a.m = a.l = 2, a.v[1][1] = 1, a.v[1][2] = 1, a.v[2][1] = 1, a.v[2][2] = 0;
        b.m = b.l = 2, b.v[1][1] = 1, b.v[1][2] = 0, b.v[2][1] = 0, b.v[2][2] = 1;
        c.m = 2, c.l = 1, c.v[1][1] = 1, c.v[2][1] = 0;
        n --;
        while(n) {
            if(n & 1) b = get_mul(a, b);
            a = get_mul(a, a);
            n >>= 1;
        }
        b = get_mul(b, c);
        printf("%d\n", b.v[1][1]);
    }
    return 0;
}