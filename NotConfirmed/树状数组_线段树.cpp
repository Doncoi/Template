//树状数组**************************************************************************************************************************************
int a[maxn], tree[maxn]
5
void add(int k,int num) {  
    while(k<=n) {  
        tree[k]+=num;  
        k+=k&-k;                  //k += lowbit(k)]
    }  
}  

int read(int k) {                 //1~k的区间和  
    int sum=0;  
    while(k) {  
        sum+=tree[k];  
        k-=k&-k;  
    }  
    return sum;
}

//线段树*******************************************************************************************************************************************
#include <algorithm>

#define INF 0x3f3f3f3
#define mid (this->l + this->r >> 1)

struct Node{
    int l, r; // [l, r)
    Node *lc, *rc;                    //两个指向node类型的指针
 .   int sum, max, min;                        
    int lazy;
    
    Node(int l, int r){              
        this->l = l, this->r = r;     //this -> l == node[pre].l
        sum = lazy = max = 0;
        min = INF;
    }
    
    void addTag(int delta){           //延迟标记，不查询不下放
        lazy += delta;                
        sum += delta * (r - l);
    }

    void pushDown(){                  //标记下放
        if(lazy){                     
            lc->addTag(lazy);          
            rc->addTag(lazy);
            
            lazy = 0;
        }
    }

    void update(){                    //由子区间更新
        sum = lc->sum + rc->sum;      
        max = std :: max(lc->max, rc->max);
        min = std :: min(lc->min, rc->min);
    }
    
    void build(){                     //构造
        if(r - l == 1){
            sum = a[l];
        } 
        else{
            lc = new Node(l, mid), lc->build();
            rc = new Node(mid, r), rc->build();
            
            update();
        }
    }
    
    void modify(int index, int delta){          //单点修改
        if(r - l == 1){
            sum += delta;
        } else {
            if(index < mid) lc->modify(index, delta);
            else rc->modify(index, delta);
            
            update();
        }
    }

    void modify(int l, int r, int delta){      //区间修改
        if(l == this->l && r == this->r) addTag(delta);
        else{
            if(l < mid) lc->modify(l, std::min(mid, r), delta);
            if(r > mid) rc->modify(std::max(mid, l), r, delta);
            
            update();
        }
    }

    int query(int index){                      //单点查询
        if(r - l == 1){
            return sum;
        } else{
            pushDown();
            if(index < mid) return lc->query(index);
            else return rc->query(index);
        }
    }
    
    int query(int l, int r){                  //区间查询
        if(l == this->l && r == this->r) return sum;
        else{
            pushDown();
            int ans = 0;
            if(l < mid) ans += lc->query(l, std::min(mid, r));
            if(r > mid) ans += rc->query(std::max(mid, l), r);
            return ans;
        }
    }
};