//
// Created by kun on 24-10-31.
//

#include <iostream>
#include "convertor.h"
using namespace std;

void systemPause(){
    std::cout<<"Press any key to continue..."<< std::endl;
    std::cin.get();// 等待用户按下任意键
}
int main() {
    string input;
    string input1 = "1.00+0.71+0.58+0.69+1.58+8.00";
    string input2 = "(1+2)*((8-2)/(7-4)) + sin(pi/2) + pow(2,3) +log(2,3)";
    string input3 = "sin(pi/2) + cos(pi/4) + tan(pi/6) + log(2) + log(2,3) + pow(2,3)";

    char button;
    cout<<"ready to start? y/n?"<<endl;
    cin>>button;
    getchar();
    while(button == 'y'){
        cout<<"input the arithmetic:";
        getline(cin,input);

        convertor *test1 = new convertor(input);
        test1->data_cleaning();
        cout<<"after data-cleaning---------"<<test1->GetInfix()<<endl;
        test1->infix_to_postfix();
        cout<<"infix to postfix------------"<<test1->GetPostfix()<<endl;
        test1->postfix_to_value();
        cout<<"postfix to eventual value---"<<test1->GetEventual_value()<<endl;

        delete test1;

        cout<<"keep on? y/n?"<<endl;
        cin>>button;
        getchar();
    }

    systemPause();
    return 0;
}