//写法1
//next记录最长公共前缀后缀
//匹配时匹配i和pre + 1
int n, m;
int next[MAXN];
char s[MAXN], p[MAXN];

//void getNext(string p)
void getNext(char *p)
{
	int pre = 0;
	for(int i = 2; i <= m; ++ i) {
		while(pre > 0 && B[pre + 1] != B[i]) pre = next[pre];
		if(B[pre + 1] == B[i]) ++ pre;
		next[i] = pre;
	}
}

//void KMP(string s, string p)
void KMP(char *s, char *p)
{
	int pre = 0;
	for(int i = 1; i <= n; ++ i) {
		//失配会导致模式串按照next数组不断回溯
		while(pre > 0 && B[pre + 1] != A[i]) pre = next[pre];
		//匹配成功，模式串移动一位
		if(B[pre + 1] == A[i]) ++ pre;
		if(pre == m) {
			cout << i - m + 1 << endl;
			pre = next[pre];
		}
	}
}

//注意输入时第一位置空，下标从1开始记
cin >> s + 1 >> p + 1;
n = strlen(s + 1), m = strlen(p + 1);

//写法2
//next数组直接记录转移坐标
//匹配时匹配i和pre
int n, m;
int next[MAXN];
string s, p;

void getNext(string p)
//void getNext(char *p)
{
	next[0] = -1;
	int i = 0, j = -1;
	while(i < m)
	{
		if(j == -1 || p[i] == p[j])
			next[++ i] = ++ j;
		else
			j = next[j];
	}
}

void KMP(string s, string p)
//void KMP(char *s, char *p)
{
	int i = 0, j = 0;
	while(i < n)
	{
		if(j == -1 || s[i] == p[j])
			++ i, ++ j;
		else
			j = next[j];
		if(j == m)
		{
			cout << i - m + 1 << endl;
			j = next[j];
		}
	}
}

//下标从0开始记
cin >> s >> p;
n = s.length(), m = p.length();