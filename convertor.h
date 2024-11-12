//
// Created by kun on 24-10-29.
//

#ifndef CALCULATOR_CONVERTOR_H
#define CALCULATOR_CONVERTOR_H

#include <stack>
#include <string>
#include <iostream>
#include <regex>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;

class convertor {
private:
    int priority(char op) const;    //在这里定义运算符的优先级
    string ori;
    string infix;
    string postfix;
    double eventual_value;
    int tag = 1;
public:
    convertor(string string1);
    string GetInfix();
    string GetPostfix();
    double GetEventual_value();
    int GetTag();
    void SetInfix(string tem_str);
    void SetPostfix(string tem_str);
    void SetEventual_value(double tem_value);
    bool isNumber(char ch);
    bool isOperator(char ch);
    void data_cleaning();  //用户输入的字符串还会有自己的变量，而且也涉及函数，需要先清洗
    void infix_to_postfix();   //前缀变后缀
    void postfix_to_value();    //后缀变值
};

#endif //CALCULATOR_CONVERTOR_H
