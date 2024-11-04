//
// Created by kun on 24-10-29.
//


#include "convertor.h"

#include <utility>

convertor::convertor(string string1) : ori(std::move(string1)), infix(string1), postfix(string1), eventual_value(0) {}

string convertor::GetInfix() {
    return infix;
}

string convertor::GetPostfix() {
    return postfix;
}

double convertor::GetEventual_value() {
    return eventual_value;
}

int convertor::priority(char op) const {
    if(op == '+' || op == '-'){
        return 1;
    }else{
        return 2;   //如果栈顶的是乘除，那就要先出栈，让加减入栈；如果栈顶的是加减，那就直接入栈
    }
}

bool convertor::isNumber(char ch) {
    return isdigit(ch) || ch == '.';
}

bool convertor::isOperator(char ch) {
    if(ch == '*' || ch == '/' || ch == '+' || ch == '-'){
        return true;
    }
    return false;
}

void convertor::data_cleaning() {
    string result = ori;

    //先把空格去掉
    result.erase(remove_if(result.begin(),result.end(), ::isspace),result.end());
    //然后使用正则表达式把函数式变成对应的值
    regex sin1_pattern(R"(\bsin\(([-+]?\d*\.?\d*)\))"); //这个用来匹配sin(x)
    regex sin2_pattern(R"(\bsin\(pi/([-+]?\d*\.?\d*)\))");   //这个用来匹配sin(π/x)
    regex cos1_pattern(R"(\bcos\(([-+]?\d*\.?\d*)\))"); //这个用来匹配cos(x)
    regex cos2_pattern(R"(\bcos\(pi/([-+]?\d*\.?\d*)\))");   //这个用来匹配cos(π/x)
    regex tan1_pattern(R"(\btan\(([-+]?\d*\.?\d*)\))"); //这个用来匹配tan(x)
    regex tan2_pattern(R"(\btan\(pi/([-+]?\d*\.?\d*)\))");   //这个用来匹配tan(π/x)
    regex pow_pattern(R"(\bpow\(([-+]?\d*\.?\d*),([-+]?\d*\.?\d*)\))"); //这个用来匹配pow(x,y)
    regex log1_pattern(R"(\blog\(([-+]?\d*\.?\d*)\))"); //这个用来匹配ln(x)
    regex log2_pattern(R"(\blog\(([-+]?\d*\.?\d*),([-+]?\d*\.?\d*)\))");    //这个用来匹配log(x,y)
    regex var_pattern(R"(\b([a-zA-Z]+)\b)"); //这个用来匹配变量名

    auto replace_matches = [](const std::string& expr, const std::regex& pattern, auto func) {
        std::string new_expr;
        std::sregex_iterator it(expr.begin(), expr.end(), pattern);
        std::sregex_iterator end;

        int last_pos = 0;
        for (; it != end; ++it) {
            std::smatch match = *it;
            new_expr += expr.substr(last_pos, match.position() - last_pos);
            new_expr += func(match);
            last_pos = match.position() + match.length();
        }
        new_expr += expr.substr(last_pos);
        return new_expr;
    };

    result = replace_matches(result, sin1_pattern, [](const std::smatch& match) -> std::string{
        double tem_value = std::stod(match[1].str());
        double value = sin(tem_value);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, sin2_pattern, [](const std::smatch& match) -> std::string{
        //这里默认分子是π
        double fenmu = std::stod(match[1].str());
        double value = sin(acos(-1)/fenmu);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, cos1_pattern, [](const std::smatch& match) -> std::string{
        double tem_value = std::stod(match[1].str());
        double value = cos(tem_value);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });

    result = replace_matches(result, cos2_pattern, [](const std::smatch& match) -> std::string{
        //这里默认分子是π
        double fenmu = std::stod(match[1].str());
        double value = cos(acos(-1)/fenmu);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, tan1_pattern, [](const std::smatch& match) -> std::string{
        double tem_value = std::stod(match[1].str());
        double value = tan(tem_value);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, tan2_pattern, [](const std::smatch& match) -> std::string{
        //这里默认分子是π
        double fenmu = std::stod(match[1].str());
        double value = tan(acos(-1)/fenmu);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, log1_pattern, [](const std::smatch& match) -> std::string{
        double tem_value = std::stod(match[1].str());
        double value = log(tem_value);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, log2_pattern, [](const std::smatch& match) -> std::string{
        double base = stod(match[1].str());
        double exponent = std::stod(match[2].str());
        double value = log(exponent)/ log(base);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, pow_pattern, [](const std::smatch& match) -> std::string{
        double base = std::stod(match[1].str());
        double exponent = std::stod(match[2].str());
        double value = pow(base, exponent);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });
    result = replace_matches(result, var_pattern, [](const std::smatch& match) -> std::string{
        cout<<'"'<<match[1].str()<<'"'<<" semms to be a variable, can you give me its value ?\n";
        double value = 0;
        cin>>value;
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    });

    this->SetInfix(result);
}

void convertor::infix_to_postfix() {
    string tem = this->GetInfix(); //这个是数据清洗之后的中缀表达式
    //先把空格去掉
    tem.erase(remove_if(tem.begin(),tem.end(), ::isspace),tem.end());
    string tem_result;  //这个暂存得到的后缀表达式
    stack<char> saved_operator;   //这个暂存运算符
    int i = 0;
    while(i != tem.length()){
        if(tem[i] == '('){
            saved_operator.push(tem[i]);
        }else if(tem[i] == ')'){
            while(saved_operator.top() != '('){
                tem_result += saved_operator.top();
                tem_result += ' ';
                saved_operator.pop();
            }
            saved_operator.pop();   //弹出'('
        }else if(isOperator(tem[i])){
            while (!saved_operator.empty() && isOperator(saved_operator.top()) && (priority(saved_operator.top()) >= priority(tem[i]))) {
                tem_result += saved_operator.top();
                tem_result += ' ';
                saved_operator.pop();
            }
            saved_operator.push(tem[i]);
        }else{
            tem_result += tem[i];
            if(i != tem.length()){
                if(tem[i+1] == '.'){
                    i++;
                    tem_result += tem[i];
                    while(isNumber(tem[i+1])){
                        i++;
                        tem_result += tem[i];
                    }
                }
            }
            tem_result += ' ';
        }
        i++;
    }
    while(!saved_operator.empty()){ //如果栈非空
        tem_result += saved_operator.top();
        tem_result += ' ';
        saved_operator.pop();
    }


    this->SetPostfix(tem_result);
}

void convertor::postfix_to_value() {
    string tem = this->GetPostfix();   //这个是后缀表达式
    stack<double> opnd; //这个用来存放操作数

    int i = 0;
    while(i != postfix.length() - 1){   //这里减一是因为最后一个字符一定是空格
        if(isNumber(tem[i])){
            string tem_string;
            tem_string += tem[i];
            if(i != tem.length()){
                if(tem[i+1] == '.'){
                    i++;
                    tem_string += tem[i];
                    while(isNumber(tem[i+1])){
                        i++;
                        tem_string += tem[i];
                    }
                }
            }
            opnd.push(stod(tem_string));    //有可能有小数
        }else if(isOperator(tem[i])){   //这里采用else if而不是else，是因为还有空格
            double var2 = opnd.top();
            opnd.pop();
            double var1 = opnd.top();
            opnd.pop();
            if(tem[i] == '+'){
                opnd.push(var1 + var2);
            }else if(tem[i] == '-'){
                opnd.push(var1 - var2);
            }else if(tem[i] == '*'){
                opnd.push(var1 * var2);
            }else{
                opnd.push(var1 / var2);
            }
        }
        i++;
    }

    this->SetEventual_value(opnd.top());
    opnd.pop();
}

void convertor::SetInfix(string tem_str) {
    this->infix = std::move(tem_str);
}

void convertor::SetPostfix(string tem_str) {
    this->postfix = std::move(tem_str);
}

void convertor::SetEventual_value(double tem_value) {
    this->eventual_value = tem_value;
}
