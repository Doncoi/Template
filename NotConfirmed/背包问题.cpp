void ZeroOnePack(int cost,int value) {   //01背包
    for(int i=v;i>=cost;i--)
        f[i]=max(f[i],f[i-cost]+value);
}

void CompletePack(int cost ,int value) {  //完全背包

    for(int i=cost;i<=v;i++)
        f[i]=max(f[i],f[i-cost]+value);
}

void MultiPack(int cost ,int value,int amount) {   //多重背包
    // if(v<=cost*amount) {
    //     CompletePack(cost,value);
    //     return;
    // }
    else {
        int k=1;
        while(k<amount) {
            ZeroOnePack(k*cost,k*value);
            amount-=k;
            k*=2;
        }
        ZeroOnePack(amount*cost,amount*value);
    }
}
