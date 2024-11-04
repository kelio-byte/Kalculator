//
// Created by kun on 24-10-31.
//

#include <iostream>
#include "convertor.h"
using namespace std;

int main() {
    string input;
    getline(cin,input);
    convertor test(input);
    test.data_cleaning();
    cout<<"after data-cleaning:\t"<<test.GetInfix()<<endl;
    test.infix_to_postfix();
    cout<<"infix to postfix:\t"<<test.GetPostfix()<<endl;
    test.postfix_to_value();
    cout<<"postfix to eventual value:\t"<<test.GetEventual_value()<<endl;
    return 0;
}
