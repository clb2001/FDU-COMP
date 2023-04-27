int ack(int m, int n)
{
    if (m == 0)
    {
        return n + 1;
    }
    else if (n == 0)
    {
        return ack(m - 1, 1);
    }
    else
    {
        return ack(m - 1, ack(m, n - 1));
    }
}

//栈实现
int akm(int m, int n)
{
    stack<int> st;
    int tmp;
    while (true)
    {
        while (m > 0)
        {
            if (n == 0)
            {
                m--;
                n = 1;
            }
            else
            {
                st.push(m - 1);
                n--;
            }
        }
        tmp = n + 1;
        if (st.empty())
            break;
        else
        {
            m = st.top();
            n = tmp;
        }
        st.pop();
    }

    return tmp;
}