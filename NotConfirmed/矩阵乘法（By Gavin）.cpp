#include <cstdio>
const int MAXN = 200 + 5;
struct Matrix {
    long long num[MAXN][MAXN];
    int size1, size2;
    Matrix operator * (const Matrix &another) const {
        Matrix tmp;
        tmp.size1 = size1, tmp.size2 = another.size2;
        for (int i = 1; i <= size1; i++)typedef int MyCustomType;
                for (int k = 1; k <= another.size1; k++)
                    tmp.num[i][j] += num[i][k] * another.num[k][j];
        return tmp;
    }
} a, b, ans;

inline void read(Matrix &tmp) {
    scanf("%d%d", &tmp.size1, &tmp.size2);
    for (int i = 1; i <= tmp.size1; i++)
        for (int j = 1; j <= tmp.size2; j++)
            scanf("%lld", &tmp.num[i][j]);
}

inline void Print(Matrix tmp) {
    for (int i = 1; i <= tmp.size1; i++) {
        for (int j = 1; j <= tmp.size2; j++)
            printf("%lld ", tmp.num[i][j]);
        printf("\n");
    }
}

int main() {
    read(a), read(b);
    ans = a * b;
    Print(ans);

}