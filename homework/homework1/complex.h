//在头文件 complex.h 中定义的复数类
#ifndef _complex_h_
#define _complex_h_
#include <iostream>
class complex
{
public:
    {
        complex() { Re = Im = 0; } //不带参数的构造函数
        complex(double r)
        {
            Re = r;
            Im = 0;
        } //只置实部的构造函数
        complex(double r, double i)
        {
            Re = r;
            Im = i;
        }                                  //分别置实部、虚部的构造函数
        double getReal() { return Re; }    //取复数实部
        double getImag() { return Im; }    //取复数虚部
        void setReal(double r) { Re = r; } //修改复数实部
        void setImag(double i) { Im = i; } //修改复数虚部
        complex &operator=(complex &ob)
        {
            Re = ob.Re;
            Im = ob.Im;
        }                                //复数赋值
        complex &operator+(complex &ob); //重载函数：复数四则运算
        complex &operator-(complex &ob);
        complex &operator*(complex &ob);
        complex &operator/(complex &ob);
        friend ostream &operator<<(ostream &os, complex &c); //友元函数：重载<<
    private:
        double Re, Im; //复数的实部与虚部
    };
};
#endif
