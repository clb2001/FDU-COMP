#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 这里的模式匹配处理要全面
// 处理的方式存在问题，因为存在同一侧的相同次数项，这个没有处理好，不能用等于来识别常数项
bool isOperator(char ch){
    if (ch == '+' || ch == '-'){
        return true;
    }
    else{
        return false;
    }
}

void process(string equation, vector<string> &coef2, vector<string> &coef1, vector<string> &coef0){
    for (int i = 0; i < equation.length(); i++){
        if (isOperator(equation[i]) && equation[i+2] == 'x' && equation[i+3] == '^' && equation[i+4] == '2'){
            string temp = "";
            temp += equation[i];
            temp += equation[i+1];
            coef2.push_back(temp);
        }
        else if (isOperator(equation[i]) && equation[i+2] == 'x'){
            string temp = "";
            temp += equation[i];
            temp += equation[i+1];
            coef1.push_back(temp);
        }
        // 匹配常数项比较复杂
        else if (isOperator(equation[i]) && (i == equation.length()-2 || isOperator(equation[i+2]) || equation[i+2] == '=')){
            string temp = "";
            temp += equation[i];
            temp += equation[i+1];
            coef0.push_back(temp);
        }
        else if (equation[i] == '='){
            string temp = "=";
            coef0.push_back(temp);
            coef1.push_back(temp);
            coef2.push_back(temp);
        }
    }
}

int main(){
    vector<string> coef2, coef1, coef0;
    string equation;
    cin >> equation;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    // 字符串处理
    process(equation, coef2, coef1, coef0);
    int record2 = coef2.size();
    int record1 = coef1.size();
    int record0 = coef0.size();

    // 处理二次项
    for (int i = 0; i < coef2.size(); i++){
        if (coef2[i] == "="){
            record2 = i;
            break;
        }
    }

    for (int i = 0; i < coef2.size(); i++){
        if (coef2[i] != "="){
            string temp;
            temp += coef2[i];
            if (i < record2){
                a += atof(temp.c_str());
            }
            else if (i > record2){
                a -= atof(temp.c_str());
            }
        }
        else{
            continue;
        }
    }

    // 处理一次项
    for (int i = 0; i < coef1.size(); i++){
        if (coef1[i] == "="){
            record1 = i;
            break;
        }
    }

    for (int i = 0; i < coef1.size(); i++){
        if (coef1[i] != "="){
            string temp;
            temp += coef1[i];
            if (i < record1){
                b += atof(temp.c_str());
            }
            else if (i > record1){
                b -= atof(temp.c_str());
            }
        }
        else{
            continue;
        }
    }

    // 处理常数项
    for (int i = 0; i < coef0.size(); i++){
        if (coef0[i] == "="){
            record0 = i;
            break;
        }
    }

    for (int i = 0; i < coef0.size(); i++){
        if (coef0[i] != "="){
            string temp;
            temp += coef0[i];
            if (i < record0){
                c += atof(temp.c_str());
            }
            else if (i > record0){
                c -= atof(temp.c_str());
            }
        }
        else{
            continue;
        }
    }

    double delta = pow(b,2) - 4*a*c;

    if (fabs(a) > 1e-3){
        if (delta <= -1e-10){
            cout << "No solution" << endl;
        }

        else if (fabs(delta) < 1e-10){
            double x = (-b)/(2*a);
            printf("%.2lf\n", x);
        }

        else if (delta >= 1e-10){
            double x1 = (-b - sqrt(delta))/(2*a);
            double x2 = (-b + sqrt(delta))/(2*a);
            printf("%.2lf\n", x1);
            printf("%.2lf\n", x2);
        }
    }

    else if(fabs(a) < 1e-10 && fabs(b) > 1e-3){ 
        double x0 = (-c)/b;
        printf("%.2lf\n", x0);
    }

    else if(fabs(a) < 1e-10 && fabs(b) < 1e-10 && fabs(c) > 1e-3){
        cout << "No solution" << endl;
    }
    return 0;
}

/*
太难了太难了，不过总是在社导课上通过了编译
*/