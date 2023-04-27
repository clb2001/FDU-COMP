template <class Type>
void inverse(Type A[], int n)
{
    Type tmp;
    for (int i = 0; i <= (n - 1) / 2; i++)
    {
        tmp = A[i];
        A[i] = A[n - i - 1];
        A[n - i - 1] = tmp;
    }
}