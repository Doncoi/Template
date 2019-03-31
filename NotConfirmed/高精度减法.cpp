#include <cstring>
#include <iostream>
#include <algorithm>
#define MAXN 505
 
int lena, lenb;
char c[MAXN];
int a[MAXN], b[MAXN];

int judge() {
    if(lena > lenb) return 1;
    else if(lena < lenb) return 0;
    else {
        for(int i = lena;i >= 1;i --) {
            if(a[i] > b[i]) return 1;
            else if(a[i] < b[i]) return 0;
            else continue;
        }
    }
    return -1;
}

int main() {	
	memset(a, 0, sizeof(a));    memset(b, 0, sizeof(b));
	
	std :: cin >> c;
	lena = strlen(c);  
    for(int i = lena;i >= 1;i --) 
    	a[(lena - i) + 1] = c[i - 1] - '0';
    	
    std :: cin >> c;
	lenb = strlen(c);
    for(int i = lenb;i >= 1;i --) 
    	b[(lenb) - i + 1] = c[i - 1] - '0';
    
    int len = std :: max(lena, lenb);

    if(judge() == 1) {           //a > b
        for(int i = 1;i <= len;i ++) {
            a[i] -= b[i];
            if(a[i] < 0) {
                a[i + 1] --;
                a[i] += 10;
            }
        }

        if(a[len] == 0) len --;
        for(int i = len;i >= 1;i --)
            std ::cout << a[i];
    }
    else if(judge() == 0){
        for(int i = 1;i <= len;i ++) {
            b[i] -= a[i];
            if(b[i] < 0) {
                b[i + 1] --;
                b[i] += 10;
            }
        }

        if(b[len] == 0) len --;
        std :: cout << "-";
        for(int i = len;i >= 1;i --)
            std ::cout << b[i];
    }
    else std :: cout << "0";
}