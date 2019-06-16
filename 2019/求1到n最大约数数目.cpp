#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
long long T, n, ans;
int prime[20] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51};
 
int read()
{
    int res = 0, flg = 1; char chr = getchar();
    while(chr < '0' || chr > '9') {if(chr == '-') res = -1; chr = getchar();}
    while(chr <= '9' && chr >= '0') {res = res * 10 + chr - '0'; chr = getchar();}
    return res * flg;
}

void dfs(int pos, long long num, long long sum, int len)
{
    if (sum > n) return;
    if (sum <= n) ans = std :: max(ans, num);

    for (int i = 1; i <= len; i ++) 
    {
        long long res = std :: pow(prime[pos], i);
        if (sum > n / res) break;
        dfs(pos + 1, num * (i + 1), sum * (res), i);
    }
}

int main()
{
    std :: cin >> T;
    while(T --)
    {
        std :: cin >> n; ans = 0;
        dfs(1, 1, 1, 30);
        std :: cout << ans << std :: endl;
    }
}