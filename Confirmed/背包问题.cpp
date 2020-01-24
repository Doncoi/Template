//01背包 每种物品只有一件
for (int i = 1; i <= N; i++) {    //对于第i个物品
    for (int v = 0; v <= V; v++) {    //枚举容积
        F[i][v] = F[i - 1][v];    //不选择第i件物品
        //如果容积足够且选择第i件物品更优
        if (v - C[i] >= 0 && F[i][v] < F[i - 1][v - C[i]] + W[i])   
            F[i][v] = F[i - 1][v - C[i]] + W[i];
    }
}

for(int v = 0; v <= V; ++ v)
    ans = max(ans, f[N][v]);



//01背包优化
void ZeroOnePack(int cost,int value) {  
    for(int i = v; i >= cost; i --)
        f[i] = max(f[i], f[i - cost] + value);
}

for(int i = 1; i <= n; ++ i) 
    ZeroOnePack(cost[i], value[i]);


//完全背包 每种物品不限制数量
void CompletePack(int cost, int value) {  //完全背包
    for(int i = cost; i <= v; i ++)
        f[i] = max(f[i], f[i - cost] + value);
}

for(int i = 1; i <= n; ++ i)
    CompletePack(cost[i], value[i]);

//多重背包 每种物品限制为一定数量
void MultiPack(int cost ,int value, int amount) { 
    //无法用尽所有物品，当作不限制数量处理
    if(v <= cost * amount) {
         CompletePack(cost,value);
         return;
    } else {
        //将k件该物品看作一件超级物品，做01背包
        //二进制拆分，使得枚举出的若干个k可以组成1~amount-1的任意正整数
        int k = 1;
        while(k < amount) {
            ZeroOnePack(k * cost, k * value);
            amount -= k;
            k *= 2;
        }
        //不要忘记处理全部放入的情况
        ZeroOnePack(amount * cost, amount * value);
    }
}