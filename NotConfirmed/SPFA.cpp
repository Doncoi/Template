//指针版
void SPFA(){
    for(int i=1; i<=gv; i++)
        Dist[i] = 100000;
    Dist[S] = 0;
    int next = 0, open = 1;
    queue[1] = S;
    Inqueue[S] = true;
    do{
        next++;
        node *tmp = connect[queue[next]];
        Inqueue[queue[next]] = false;
        while(tmp != NULL){
            if( Dist[tmp->key] > Dist[queue[next]] + tmp->w){
                
                Dist[tmp->key] = Dist[queue[next]] + tmp->w;
                Path[tmp->key] = queue[next];
                if( !Inqueue[tmp->key] ){
                    Inqueue[tmp->key] = true;
                    open++;
                    queue[open] = tmp->key;
                }
            }
            tmp = tmp->next;
        }
    }while(next < open);
}



//邻接矩阵版
        Dist[i] = 100000;
        for( int j=1; j<=gv; j++)void SPFA(){
    for( int i=1; i<=gv; i++){

            if( !Graph[i][j] && i!=j) Graph[i][j] = 100000;
    }
    int next = 0, open = 1;
    queue[1] = S;
    Dist[S] = 0;
    do{
        next++;
        int u = queue[next];
        Inqueue[u] = false;
        for(int i=1; i<=gv; i++)
            if ( Dist[i] > Dist[u] + Graph[u][i] ){
                Dist[i] = Dist[u] + Graph[u][i];
                Path[i] = u;
                if( !Inqueue[i] ){
                    Inqueue[i] = true;
                    open++;
                    queue[open] = i;
                }
            }
    }while(next < open);
}