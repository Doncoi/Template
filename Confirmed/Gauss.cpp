int Fp(int a,int n){
	int res=1;
	a<0?a+=mod:(a>=mod)?a-=mod:0; 
	for(;n;n>>=1,a=(ll)a*a%mod)if(n&1)res=(ll)res*a%mod;
	return res;
}

void swap(int x,int y,int r) {for(int i=0;i<r;i++)swap(a[i][x],a[i][y]);}

//row : 总行数  col : 当前处理的元素
void gauss(int row, int col) {
	int r = 0, c = 0;
	//枚举当前处理的行
	for( ; r < row && c < col; r ++, c ++){
		int pivot = r;
		//找到该col列元素中绝对值最大的那行与当前行交换，减小除法时的误差
		for(int i = r + 1; i < row; i ++)
			if(abs(a[i][c]) > abs(a[pivot][c])) pivot = i;
		//交换
		if(pivot != r) swap(a[pivot], a[r]);

		//说明col列第r行以下全是0了，处理下一列（下一个元素）
		if(!a[r][c]) { r --; continue;}
		//枚举要删除的行
		for(int i = r + 1; i < row; i ++){
			if(!a[i][c]) continue;
			int t1 = a[r][c], t2 = a[i][c];
			for(int j = c; j <= col; j ++){
				a[i][j] = ((ll)a[i][j] * t1 - (ll)a[r][j] * t2) % mod;
				if(a[i][j] < 0) a[i][j] += mod;
			}
		}
	}

	//化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0)
	//对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
	for(int i = r; i < row; i ++) if(a[i][col]) return;
	//在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
	//且出现的行数为自由变元的个数
	for(int i = 0, j; i < col && j < row; i ++){
		if(!a[i][i]) {
			for(j = i + 1; j < col; j ++) if(a[i][j]) break;
			if(j < col) swap(i,j,row);
		}
	}

	//回代每一行的值到上一行，得出解
	for(int i = col - 1; ~i; i --){
		ll t = a[i][col];
		for(int j = i + 1; j < col; j ++)
			t = ((t - a[i][j] * (ll)x[j] % mod) % mod + mod) % mod;
		x[i] = t * Fp(a[i][i], mod - 2) % mod;
	}
}
