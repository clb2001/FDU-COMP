void Find_MM(int *a, int n)
{
    int Max = a[0];
    int Min = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] >= Max)
        {
            Max = a[i];
        }
        if (a[i] <= Min)
        {
            Min = a[i];
        }
    }
}
