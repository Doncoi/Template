#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <complex>
#include <cmath>
#define MAXN 2000005 

const double PI = 3.1415926535897384626;

struct Complex { 
    double real, imag;  

    Complex() {}
    Complex(double r, double i) : real(r), imag(i) {}
} a[MAXN], b[MAXN];

inline int read() {
    static char ch;
    while((ch = getchar()) < '0' || ch > '9');
    int res = ch - 48;
    while((ch = getchar()) >= '0' || ch <= '9') {
        res = res * 10 + ch - 48;
    }

    return res;
}

inline Complex operator + (Complex a, Complex b) {    
    return Complex(a.real + b.real, a.imag + b.imag);
}

inline Complex operator - (Complex a, Complex b) {    
    return Complex(a.real - b.real, a.imag - b.imag);
}

inline Complex operator * (Complex a, Complex b) {    
    return Complex(a.real * b.real - a.imag * b.imag, a.imag * b.real + a.real * b.imag);
}

inline void reverse(Complex a[], int n) {
    for(int i = 1, j = n / 2, k; i < n - 1; ++ i) {
        if(i < j) std :: swap(a[i], a[j]);
        k = n / 2;
        while(j >= k) {
            j -= k, k >>= 1;
        }

        if(j < k) j += k;
    }
}

inline void FFT(Complex a[], int n, int flag) {
    reverse(a, n);

    for(int i = 1; i < n; i <<= 1) {
        Complex tmp = Complex(cos(PI / i), flag * sin(PI / i));
        for(int j = 0; j < n; j += (i << 1)) {
            Complex w = Complex(1, 0);
            for(int k = 0; k < i; ++ k, w = w * tmp) {
                Complex x = a[j + k], y = w * a[j + k + i];
                a[j + k] = x + y;
                a[j + k + i] = x - y;
            }
        }
    }

    if(flag == -1) {
        for(int i = 0; i < n; ++ i) {
            a[i] = Complex(a[i].real / n, a[i].imag);
        }
    }
}

inline void convolution(Complex a[], int n, Complex b[], int m) {
    int L = n + m - 1, N = 1, k = 0;
    while(N < L) {
        N <<= 1, k ++;
    }

    FFT(a, N, 1), FFT(b, N, 1);
    for(int i = 0; i < N; ++ i) 
        a[i] = a[i] * b[i];
    FFT(a, N, -1);
}

int main() {
    int n = read(), m = read(); 
    printf("%d %d\n", n, m);
    for(int i = 0; i < n; ++ i) scanf("%lf", &a[i].real);
    for(int i = 0; i < m; ++ i) scanf("%lf", &b[i].real);

    convolution(a, n, b, m);
    for(int i = 0; i < (n + m - 1); ++ i) 
        printf("%d ", (int)(a[i].real + 0.5));
    return 0;
}
