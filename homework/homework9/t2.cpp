template <class Type>
void datalist<Type>::count_sort()
{
    // initList是待排序表，resultList是结果表
    int i, j;
    int *c = new datalist<Type>; // c是存放计数排序结果的临时表
    for (i = 0; i < CurrentSize; i++)
        Vector[i].count = 0; //初始化，计数值都为0
    for (i = 0; i < CurrentSize - 1; i++)
        for (j = i + 1; j < CurrentSize; j++)
            if (Vector[j].key < Vector[i].key)
                Vector[i].count++;
            else
                Vector[j].count++;    //统计
    for (i = 0; i < CurrentSize; i++) //在c->Vector[ ]中各就各位
        c->Vector[Vector[i].count] = Vector[i];
    for (i = 0; i < CurrentSize; i++)
        Vector[i] = c->Vector[i]; //结果复制回当前表对象中
    delete c;
}