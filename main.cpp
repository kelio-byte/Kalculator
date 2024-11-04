//
// Created by kun on 24-10-31.
//

#include <iostream>
#include "convertor.h"
using namespace std;

int main() {
    convertor test("(1+2)*((  8/2-1)/(7-4.54))");
    test.data_cleaning();
    cout<<"after data-cleaning:"<<test.GetInfix()<<endl;
    test.infix_to_postfix();
    cout<<"infix to postfix:"<<test.GetPostfix()<<endl;
    test.postfix_to_value();
    cout<<"postfix to eventual value:"<<test.GetEventual_value()<<endl;
    return 0;
}
