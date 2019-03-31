#include <cstdio>
#include <cstring>

const int MAXN = 1e9;
const long long MOD = 1e9 + 7;

struct Matrix {
    long long a[2][2];

    Matrix(const bool unit = false) {
        memset(a, 0, sizeof(a));
        if (unit) for (int i = 0; i < 2; i++) a[i][i] = 1;
    }

    long long &operator()(const int i, const int j = 0) 
        { return a[i][j]; }
        
    const long long &operator()(const int i, const int j = 0) 
        const { return a[i][j]; }
};

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix res(false);
    for (int i = 0; i < 2; i++) 
        for (int j = 0; j < 2; j++) 
            for (int k = 0; k < 2; k++) 
                (res(i, j) += a(i, k) * b(k, j)) %= MOD;
    return res;
}

Matrix pow(Matrix a, int n) {
    Matrix res(true);
    for (; n; n >>= 1, a = a * a) if (n & 1) res = res * a;
    return res;
}

int main() {
    int n;
    scanf("%d", &n);

    if (n == 0) puts("1");
    else if (n == 1) puts("3");
    else {
        Matrix init(false);
        init(0) = 1;
        init(1) = 3;

        Matrix shift(false);
        shift(0, 0) = 0;
        shift(0, 1) = 1;
        shift(1, 0) = 1;
        shift(1, 1) = 2;

        Matrix res = pow(shift, n - 1) * init;
        printf("%lld\n", res(1));
    }

    return 0;
}
