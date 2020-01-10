void findBMstr(string& str)
{
    int *p = new int[str.size() + 1];
    memset(p, 0, sizeof(p));

    int mx = 0, id = 0;
    for(int i = 1; i <= str.size(); ++ i)
    {
    	//利用已有值优化
        if(mx > i) p[i] = (p[2*id - i] < (mx - i) ? p[2*id - i] : (mx - i));
        else p[i] = 1;
        //暴力匹配
        while(str[i - p[i]] == str[i + p[i]]) p[i]++;
        //更新mx与id
        if(i + p[i] > mx)
            mx = i + p[i], id = i;
    }

    int max = 0, ii;
    for(int i = 1; i < str.size(); i++)
    {
        if(p[i] > max)
        {
            ii = i;
            max = p[i];
        }
    }

    max--;

    int start = ii - max ;
    int end = ii + max;
    for(int i = start; i <= end; i++)
    {
        if(str[i] != '#')
        {
            cout << str[i];
        }
    }
    cout << endl;

    delete  p;
}
