inline int read() {
	char ch = getchar(); int res = 0, flag = 1;
	while(ch > '9' || ch < '0') {if(ch == '-') flag = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0') {res = res*10 + ch-'0'; ch = getchar();}
	return (res * flag);
}

template<typename Temp> inline void read(Temp &x)
{
	Temp res = 0, flg = 1; char chr = getchar();
	while(! isdigit(chr)) {if(chr == '-') flg = -1; chr = getchar();} 
	while(isdigit(chr)) {res = res * 10 + chr - '0'; chr = getchar();}
	x = (res * flg);
}