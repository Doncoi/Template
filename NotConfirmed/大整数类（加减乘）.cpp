#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXN 200 + 5

int read()
{
	int res = 0, flg = 1; char chr = getchar();
	while(!isdigit(chr)) {if(chr == '-') flg = -1; chr = getchar();}
	while(isdigit(chr)) {res = res * 10 + chr - '0'; chr = getchar();}
	return (res * flg);
}

int max(int a, int b)
{
	return (a > b ? a : b);
}

int min(int a, int b)
{
	return (a < b ? a : b);
}

struct highAccuracy
{
	int len, arr[MAXN];
	bool sig;

	highAccuracy() 
	{
		len = 1, sig = 1;
		memset(arr, 0, sizeof(arr));
	}

	int judge(const highAccuracy &x)
	{
		if(len > x.len)
		{
			return 1;
		}
		else if(len < x.len)
		{
			return -1;
		}
		else 
		{
			for(int i = len; i >= 1; -- i)
			{
				//printf("arr : %d A.arr[%d] = %d B.arr[%d] = %d\n", i, i, arr[i], i, x.arr[i]);
				
				if(arr[i] > x.arr[i])
				{
					return 1;
				}
				if(arr[i] < x.arr[i])
				{
					return -1;
				}
			}

			return 0;
		}
	}

	highAccuracy operator = (const int &x)
	{
		if(!x)
		{
			arr[1] = 0, len = 1;
			return *this;
		}

		len = 0; int tmp = x;
		if(tmp < 0)
		{
			tmp *= -1, sig = 0;
		}
		while(tmp)
		{
			arr[++ len] = tmp % 10, tmp /= 10;
		}

		return *this;
	}
	/*
	highAccuracy operator = (const highAccuracy &x)
	{
		sig = x.sig, len = x.len;
		for(int i = 1; i <= len; ++ i)
		{
			arr[i] = x.arr[i];
		}

		return *this;
	}
	*/
	highAccuracy operator + (const int &x) const
	{
		highAccuracy ans = *this;

		ans.arr[1] += x;
		for(int i = 2; i <= ans.len; ++ i)
		{
			ans.arr[i] += ans.arr[i - 1] / 10;
			ans.arr[i - 1] %= 10;
		}
		while(ans.arr[ans.len] > 9)
		{
			ans.arr[len + 1] = ans.arr[ans.len] / 10;
			ans.arr[ans.len] %= 10, ans.len ++;
		}

		return ans;
	}

	highAccuracy operator + (const highAccuracy &x) const
	{
		highAccuracy ans = *this;

		ans.len = max(ans.len, x.len);
		for(int i = 1; i <= ans.len; ++ i)
		{
			ans.arr[i] += x.arr[i];
		}
		for(int i = 2; i <= ans.len; ++ i)
		{
			ans.arr[i] += ans.arr[i - 1] / 10;
			ans.arr[i - 1] %= 10;
		}
		while(ans.arr[ans.len] > 9)
		{
			ans.arr[ans.len + 1] = ans.arr[ans.len] / 10;
			ans.arr[ans.len] %= 10, ans.len ++;
		}

		return ans;
	}

	highAccuracy operator - (const highAccuracy &x) const
	{
		highAccuracy tmp = *this, ans;

		if(tmp.judge(x) == 1)
		{
			//printf("A > B\n");
			ans = *this;
			for(int i = 1; i <= x.len; ++ i)
			{
				ans.arr[i] -= x.arr[i];
				if(ans.arr[i] < 0) 
				{
					ans.arr[i + 1] --, ans.arr[i] += 10;
				}
				
			}
			while(ans.arr[ans.len] == 0)
			{
				ans.len --;
			}
		}
		else if(tmp.judge(x) == -1)
		{
			//printf("A < B\n");
			ans = x, ans.sig = 0;
			for(int i = 1; i <= ans.len; ++ i)
			{
				ans.arr[i] -= arr[i];
				if(ans.arr[i] < 0)
				{
					ans.arr[i + 1] --, ans.arr[i] += 10;
				}
			}
			while(ans.arr[ans.len] == 0)
			{
				ans.len --;
			}
		}
		else
		{
			//printf("A = B\n");
		}

		return ans;
	}

	highAccuracy operator * (const int &x) const
	{
		highAccuracy ans = *this;

		for(int i = 1; i <= ans.len; ++ i)
		{
			ans.arr[i] = ans.arr[i] * x;
			ans.arr[i + 1] += ans.arr[i] / 10, ans.arr[i] %= 10;
		}
		while(ans.arr[ans.len])
		{
			ans.arr[ans.len + 1] = ans.arr[ans.len] / 10;
			ans.arr[ans.len] %= 10, ans.len ++;
		}
		while(!ans.arr[ans.len])
		{
			ans.len --;
		}

		return ans;
	}

	highAccuracy operator * (const highAccuracy &x) const
	{
		highAccuracy ans;
		if(!sig)
		{
			ans.sig = (!x.sig) ? true : false;
		}
		else
		{
			ans.sig = (x.sig) ? true : false;
		}

		for(int i = 1; i <= x.len; ++ i)
		{
			for(int j = 1; j <= len; ++ j)
			{
				ans.arr[i + j - 1] += arr[j] * x.arr[i];
			}
		}
		while(ans.arr[ans.len])
		{
			ans.arr[ans.len + 1] += ans.arr[ans.len] / 10;
			ans.arr[ans.len] %= 10, ans.len ++;
		}
		while(!ans.arr[ans.len])
		{
			ans.len --;
		}

		return ans;
	}

	highAccuracy operator += (const highAccuracy &x)
	{
		*this = *this + x;
		return *this;
	}

	highAccuracy operator -= (const highAccuracy &x)
	{		
		*this = *this - x;
		return *this;
	}

	highAccuracy operator *=(const highAccuracy &x)
	{
		*this = *this * x;
		return *this;
	}

	void print() 
	{
		if(len == 1 && !arr[1] && !sig)
		{
			printf("-");
		}
		for(int i = len; i; -- i)
		{
			putchar(arr[i] + '0');
		}

		return;
	}
};