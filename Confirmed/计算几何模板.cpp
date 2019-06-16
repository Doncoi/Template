//判断点是否在线段上
inline bool int dot(const point &lhs, const point &rhs) {
	innt det = (u - p) * (v - p);
	if(det) {
		return false;
	}

	int Dot = dot(u - p, v - p);
	return Dot <= 0;
}

//点与多边形的位置关系判断
struct polygon() {
	int n;
	point p[MAXN];
	void init(int _n) {
		n = _n;
		for(int i= 0; i < n; ++ i) {
			scanf("%d%d", &p[i].x, &p[i].y);
		}

		p[n] = p[0];
		if(Area() < 0) {
			std :: reverse(p, p + n);
		}
	}

	inline Area() const {
		int res = 0;
		for(int i= 0; i < n; ++ i) {
			res += p[i] = p[i + 1];
		}
		
		return rs; 
	}

	bool inner(cnost point &q) {
		int cnt = 0;
		for(int i = 0; i < n; ++ i) {
			if(check(p[i], p[i + 1], q)) {
				return true;
			}

			int d1 = p[i].y - q.y, d2 = p[i + 1].y - q.y;
			int det = (p[i] -q) * (p[i + 1] -q);

			if((det >= 0 && d1 < 0 && d2 >= 0) || (det <= 0 && d1 >= 0 && d2 < 0)) {
				++ cnt;
			}

			return cnt & 1;     //若交点个数为奇数，则可知该点在多边形内部
		}
	}
} P;

//Graham扫描
struct point 
{
    int x, y;
    point() {}

    point(int _x, int _y) : x(_x), y(_y) {}

    friend inline point operator - (const point &lhs, const point &rhs) 
    {
        return point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend inline int operator * (const point &lhs, const point &rhs) 
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    inline int norm() const 
    {
        return x * x + y * y;
    }
} p[MAXN], q[MAXN];

inline bool cmp(int u, int v) 
{
    int det = (p[u] - p[1]) * (p[v] - p[1]);
    if(det) 
    {
        return det > 0;
    }

    return (p[u] - p[1]).norm() < (p[v] - p[1]).norm();
}

void Graham() 
{
    int id = 1;              //寻找位于最左下角的极点
    for(int i = 2; i <= n; ++ i) 
    {
        if(p[i].x < p[id].x || (p[i].x == p[id].x && p[i].y < p[id].y)) 
        {
            id = i;
        } 
    }
    if(id != 1) {
        std :: swap(p[1], p[id]);
    }

    static int pre[MAXN];             //使用辅助数组储存点的下标并排序
    for(int i = 1; i <= n; ++ i) 
    {
        pre[i] = i;
    }
    std :: sort(pre + 2, pre + n + 1, cmp);  //第一位为我们找到的极点，不参与排序

    q[++ m] = p[1];
    for(int i = 2; i <= n; ++ i) 
    {
        int j = pre[i];
        while(m >= 2 && (p[j] - q[m -1]) * (q[m] - q[m - 1]) >= 0) 
        { //判断拐向
            -- m;  //若发生拐向，则出现了凹边，是当前点出队
        }

        q[++ m] = p[j];
    }
}

//多边形面积计算
int Area() 
{
    int res =  0;
    q[m + 1] = q[1];
    for(int  i = 1; i <= m; ++ i) 
    {   //多点向量叉积
        res += q[i] * q[i + 1];
    }

    return res / 2;
}