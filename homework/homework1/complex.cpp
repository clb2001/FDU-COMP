//复数类 complex 的相关服务的实现放在 C++源文件 complex.cpp 中 #include <iostream.h>
#include <math.h>
#include "complex.h"

complex &complex ::operator+(complex &ob)
{
    //重载函数：复数加法运算。
    complex *result = new complex(Re + ob.Re, Im + ob.Im);
    return *result;
}
complex &complex ::operator-(complex &ob)
{
    //重载函数：复数减法运算
    complex *result = new complex(Re - ob.Re, Im - ob.Im);
    return *result;
}
complex &complex ::operator*(complex &ob)
{
    //重载函数：复数乘法运算
    complex *result =
        new complex(Re * ob.Re - Im * ob.Im, Im * ob.Re + Re * ob.Im);
    return *result;
}
complex &complex ::operator/(complex &)
{
    //重载函数：复数除法运算
    double d = ob.Re * ob.Re + ob.Im * ob.Im;
    complex *result = new complex((Re * ob.Re + Im * ob.Im) / d,
                                  (Im * ob.Re - Re * ob.Im) / d);
    return *result;
}
friend ostream &operator<<(ostream &os, complex &ob)
{
    //友元函数：重载<<，将复数 ob 输出到输出流对象 os 中。
    return os << ob.Re << (ob.Im >= 0.0) ? "+" : "-" << fabs(ob.Im) << "i";
}