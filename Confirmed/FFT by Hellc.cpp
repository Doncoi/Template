#include <cstdio>
#include <complex>
#include <cmath>

namespace io{
    const int INSIZE = 1 << 15, OTSIZE = 1 << 20;
    char inBuf[INSIZE], otBuf[OTSIZE], *S, *T, ch;
    int now;

    inline void init(){
        S = T = NULL;
        now = 0;
    }

    inline int getchar(){
        if(S == T) S = inBuf, T = inBuf + fread(inBuf, 1, INSIZE, stdin);
        if(S == T) return EOF;
        return *S++;
    }

    template<typename Int>
    inline void readint(Int &x){
        Int f = 1;
        for(ch = getchar(); '0' > ch || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
        for(x = 0; '0' <= ch && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
        x *= f;
    }

    inline void flush(){
        if(now) fwrite(otBuf, 1, now, stdout), now = 0;
    }

    inline void putchar(char ch){
        otBuf[now++] = ch;
        if(now == OTSIZE) flush();
    }

    inline void putint(int x){
        if(x < 0) putchar('-'), putint(-x);
        else{
            if(x > 9) putint(x / 10);
            putchar(x % 10 + '0');
        }
    }

    inline void close(){
        flush();
    }
}

const int MAX_N = 100000 + 1;
const int MAX_EX_N = 262144;
const double PI = acos(-1);

typedef std::complex<double> Complex;

namespace FFT{
    int n, logn;
    Complex omega[MAX_EX_N], omegaInv[MAX_EX_N];
    int rev[MAX_EX_N];

    inline void initOmega(){
        for(int i = 0; i < n; i++){
            omega[i] = Complex(cos(2 * PI / n * i), sin(2 * PI / n * i));    //指数(2π * i / n)
            omegaInv[i] = std::conj(omega[i]);
        }
    }

    inline void initRev(){
        for(int i = 0; i < n; i++){
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logn - 1));    //预处理rev数组，根据此数组来调整原数组
        }
    }

    inline void init(int n, int logn) {    //初始化总成
        FFT::n = n, FFT::logn = logn;
        initOmega();
        initRev();
    }

    inline void fft(Complex a[], Complex omega[]){
        static Complex aux[MAX_EX_N];
        for(int i = 0; i < n; i++) aux[ rev[i] ] = a[i];
        std::copy(aux, aux + n, a);

        for(int k = 2; k <= n; k <<= 1){
            int m = k >> 1;
            for(Complex *y = a; y != a + n; y += k){
                for(int i = 0; i < m; i++){
                    Complex u = y[i], v = y[m + i] * omega[n / k * i];
                    y[i] = u + v, y[m + i] = u - v;
                }
            }
        }
    }

    inline void dft(Complex a[]){
        fft(a, omega);
    }

    inline void idft(Complex a[]){
        fft(a, omegaInv);
        for(int i = 0; i < n; i++) a[i] /= n;
    }
}

void mul(int x[], int nX, int y[], int nY, int ans[]){
    static Complex a[MAX_EX_N], b[MAX_EX_N], c[MAX_EX_N];

    for(int i = 0; i < nX; i++) a[i] = Complex(x[i]);
    for(int i = 0; i < nY; i++) b[i] = Complex(y[i]);

    int n = 1, logn = 0;
    while(n < nX + nY - 1) n <<= 1, logn++;

    FFT::init(n, logn);

    FFT::dft(a);
    FFT::dft(b);
    for(int i = 0; i < n; i++) c[i] = a[i] * b[i];
    FFT::idft(c);

    for(int i = 0; i < nX + nY - 1; i++) ans[i] = int(c[i].real() + 0.5);
}

int x[MAX_N], y[MAX_N], nX, nY, ans[2 * MAX_N - 1];

int main(){
    io::init();

    io::readint(nX), io::readint(nY), nX++, nY++;
    for(int i = 0; i < nX; i++) io::readint(x[i]);
    for(int i = 0; i < nY; i++) io::readint(y[i]);

    mul(x, nX, y, nY, ans);

    int len = nX + nY - 1;
    for(int i = 0; i < len; i++) io::putint(ans[i]), io::putchar(i != len - 1 ? ' ' : '\n');

    io::close();
    return 0;
}
