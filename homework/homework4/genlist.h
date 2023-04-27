class GenList; // GenList 类的前视声明
class GenListNode
{ //广义表结点类定义
    friend class Genlist;

private:
    int mark, utype;    // utype ＝0 / 1 / 2, mark 是访问标记, 未访问为 0
    GenListNode *tlink; //指向同一层下一结点的指针
    union
    {                       //联合
        char listname;      // utype = 0, 表头结点情形：存放表名
        char atom;          // utype = 1, 存放原子结点的数据
        GenListNode *hlink; // utype = 2, 存放指向子表的指针
    } value;

public:
    GenListNode(int tp, char info) : mark(0), utype(tp), tlink(NULL) //表头或原子结点构造函数
    {
        if (utype == 0)
            value.listname = info;
        else
            value.atom = info;
    }
    GenListNode(GenListNode *hp) //子表构造函数
        : mark(0), utype(2), value.hlink(hp)
    {
    }
    char Info(GenListNode *elem) //返回表元素 elem 的值
    {
        return (utype == 0) ? elem->value.listname : elem->value.atom;
    }
};

class GenList
{ //广义表类定义
private:
    GenListNode *first;             //广义表头指针
    void traverse(GenListNode *ls); //广义表遍历
    void Remove(GenListNode *ls);   //将以 ls 为表头结点的广义表结构释放
public:
    Genlist(char &value); //构造函数, value 是指定的停止建表标志数据
    ~GenList();           //析构函数
    void traverse();      //遍历广义表
}