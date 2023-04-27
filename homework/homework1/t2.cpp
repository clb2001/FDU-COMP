void d(ArrayElement x[], int n)
{
    int i = 1;
    count++;
    do
    {
        x[i] += 2;
        count++;
        i += 2;
        count++;
        count++; //针对 while 语句
    } while (i <= n);
    i = 1;
    count++;
    while (i <= (n / 2))
    {
        count++; //针对 while 语句
        x[i] += x[i + 1];
        count++;
        i++;
        count++;
    }
    count++; //针对最后一次 while 语句
}

void d(ArrayElement x[], int n)
{
    int i = 1;
    do
    {
        count += 3;
        i += 2;
    } while (i <= n);
    i = 1;
    while (i <= (n / 2))
    {
        count += 3;
        i++;
    }
    count += 3;
}