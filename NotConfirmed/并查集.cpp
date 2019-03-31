//并查集*******************************************************************************************************************************************
    //压缩路径（优化）
int find (int x) {    //最常被调用的函数，其实质是递推寻找两元素的根节点
　　if (father[x] != x) father[x] = find (father[x]); //如果i参与过合并
　　return father[x];                                 //则递推寻找其集合内的根节点
}
    //合并
void unionn(int x,int y) {
　　x = find(x);y = find(y);   //将X，y集合内的根节点赋值给x，y
　　father[y] = x;             //y集合内的根节点成为x集合内根节点的儿子，
}                              //y集合内所有元素加入x集合，完成合并
    //搜索与判断
bool  judge(int x,int y) {
    x = find(x);
    y = find(y);               //每个集合内都有唯一且确定的根节点$.$
    if  (x == y)  return true; //如果两元素所在集合的根节点相同，则其在同一个集合内没错~.~
          else return false;   //或者当我什么都没说|—.—|
}

int main() {
　　    cin >> n >> m;
　　    for (i = 1; i <= n; i++) //建立新的集合,第i个成员是i
　　        father[i] = i;       //父指针为i自己，即每个元素都是一个集合   
　　    for (i = 1; i <= m; i++) {//归并操作     
　　        scanf(“%d%d”,&x,&y);  //x和y是亲戚
　　        int r1 = find(x);    
　　        int r2 = find(y);
　　        if (r1 != r2) unionn(r1,r2);//x和y不是同一人则合并两集合
　　    }    
　　    cin >> q;
　　    for (i = 1; i <= q; i++) {
　　        scanf("%d%d",&x,&y);
　　        judge(x,y);
　　    }
　　    return 0;
}
