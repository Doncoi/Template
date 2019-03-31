void quick_sort(int l, int r)
{
	if(l > r) return;
	int i, j, t, tmp;

	tmp = a[l], i = l, j = r;
	while(i != j)
	{
		while(a[j] >= tmp && i < j) -- j;
		while(a[i] <= tmp && i < j) ++ i;

		if(i < j)
		{
			t = a[i], a[i] = a[j], a[j] = t;
		}
	}

	a[l] = a[i], a[i] = tmp;

	quick_sort(l, i - 1);
	quick_sort(i + 1, r);
}
