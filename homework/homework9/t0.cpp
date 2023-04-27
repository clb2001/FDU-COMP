template <Type>
    void dataList<Type>::odd - evenSort()
{
    int i, exchange;
    do
    {
        exchange = 0;
        for (i = 1; i < CurrentSize; i += 2) //扫描所有奇数项
            if (Vector[i] > Vector[i + 1])
            {                                   //相邻两项比较, 发生逆序
                exchange = 1;                   //作交换标记
                swap(Vector[i], Vector[i + 1]); //交换
            }
        for (i = 0; i < CurrentSize; i += 2) //扫描所有偶数项
            if (Vector[i] > Vector[i + 1])
            {                                   //相邻两项比较, 发生逆序
                exchange = 1;                   //作交换标记
                swap(Vector[i], Vector[i + 1]); //交换
            }
    } while (exchange != 0);
}