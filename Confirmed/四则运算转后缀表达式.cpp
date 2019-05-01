int len, minn, maxn;
int pre, tmp, top_1, top_2;
int stack_1[MAXN], stack_2[MAXN];
std :: string s;

int read()
{
    int res = 0, flg = 1; char chr = getchar();
    while(chr < '0' || chr > '9') {if(chr == '-') flg = -1; chr = getchar();}
    while(chr <= '9' && chr >= '0') {res = res*10 + chr-'0'; chr = getchar();}
    return (res * flg);
}

int main()
{
	while(std :: cin >> s)
	{
		len = s.length(), top_1 = top_2 = 0;
		pre = 0, minn = 1, maxn = 1;

		while(pre < len)
		{
			if(s[pre] <= '9' && s[pre] >= '0')
			{	
				tmp = 0;
				while(s[pre] <= '9' && s[pre] >= '0' && pre < len)
				{
					tmp = tmp * 10 + s[pre ++] - '0';
				}

				stack_1[++ top_1] = tmp;
			}
			else if(s[pre] == '+' || s[pre] == '-' || s[pre] == '*' || s[pre] == 'd')
			{
				bool flag = true;
				while(flag)
				{
					if(top_2 == 0 ||  stack_2[top_2] == '(')
					{
						stack_2[++ top_2] = s[pre ++] * -1;
						flag = false;
					}
					else if(stack_2[top_2] == 'd' && s[pre] != 'd')
					{
						stack_2[++ top_2] = s[pre ++] * -1;
						flag = false;
					}
					else if(stack_2[top_2] == '*' && (s[pre] == '+' || s[pre] == '-'))
					{
						stack_2[++ top_2] = s[pre ++] * -1;
						flag = false;
					}
					else 
					{
						stack_1[++ top_1] = stack_2[top_2 --] * -1;
					}
				}
			} 	
			else if(s[pre] == '(')
			{
				stack_2[++ top_2] = s[pre ++] * -1;
			}
			else if(s[pre] == ')')
			{
				while(top_2 && stack_2[top_2] != '(')
				{
 					stack_1[++ top_1] = stack_2[top_2 --] * -1;
				}
				++ pre;
			}
		}

		while(top_2 && stack_2[top_2] != '(')
		{
 			stack_1[++ top_1] = stack_2[top_2 --] * -1;
		}

		/*
		for(int i = 1; i <= top_1; ++ i)
		{
			if(stack_1[i] >= 0) std :: cout << stack_1[i];
			else std :: cout << char(char(stack_1[i] * -1));
		}
		*/

		std :: cout << std :: endl;
	}
}