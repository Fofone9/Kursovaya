#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include "Header.h"
using namespace std;

class ExpressionParser {
    string expression;
    AutomateStack magazine;
    int exceptionPosition;
    string exeptionType;
public:
    ExpressionParser()
    {
        expression = "";
    };
    ExpressionParser(string includingExpression) {
        expression = includingExpression;
    };
    void analyze(){
        exceptionPosition = bracketsAnalyze();
        if (exceptionPosition == -1){
            NetermE *S;
            S = new NetermE(expression, 0);
            magazine.push(S);
            exceptionPosition = 0;
            while (!magazine.empty()) {
                Neterm* currentNeterm = magazine.pop();
                exceptionPosition = currentNeterm->analyzeExpression(&magazine);
                if (exceptionPosition != -1){
                    switch (currentNeterm->type) {
                        case UP:
                            exeptionType = "unexpected operator +, needed argument";
                            break;
                        case UM:
                            exeptionType = "unexpected operator *, needed argument ";
                            break;
                        case EB:
                            exeptionType = "unexpected bracket, needed argument";
                            break;
                        case NONOPERB:
                            exeptionType = "need operator before brackets";
                            break;
                        case NONOPERA:
                            exeptionType = "need operator after brackets";
                        case UD:
                            exeptionType = "unexpected operator /, needed argument ";
                        case US:
                            exeptionType = "unexpected operator -, needed argument ";
                        case UO:
                            exeptionType = "unexpected sequence of operators, must be argument";
                    }
                    showException();
                    return;
                }
            }
            magazine = AutomateStack();
            perform();}
        else{
            showException();
            return;
        }
    }
    int bracketsAnalyze(){
        stack<int> brackets;
        for(int i = 0; i<expression.size(); i++){
            switch (expression[i]) {
                case '(':
                    brackets.push(i);
                    break;
                case ')':
                    if (brackets.empty()){

                        exeptionType = "unexpected symbol ')'";
                        return i;
                    }
                    brackets.pop();
                    break;
                default:
                    break;
            }
        }
        if (!brackets.empty()){
            exeptionType = "unexpected symbol '('";
            return brackets.top();
        }
        return -1;
    }
    void showException(){
        if (exceptionPosition>= expression.size())exeptionType = "unexpected end of operation, need argument";
        cout<<expression<<endl;
        for (int i = 0; i < exceptionPosition; i++){
            cout<<'-';
        }
        cout<<'^'<<endl;
        cout<<exeptionType<<endl;

    }
    void perform() {
        cout<<expression<<endl;
        cout<<"your expression is OK, want to perform it(must considered only numbers)[1:yes, 0:no]"<<endl;
        bool agree;
        cin>>agree;
        if (agree) {
            vector<string> expr;
            stack<double> values;
            NetermE *S;
            S = new NetermE(expression, 0);
            magazine.push(S);
            while (!magazine.empty()) {
                Neterm *currentNeterm = magazine.pop();
                string elementOfExpression = currentNeterm->performExpression(&magazine);
                if (!elementOfExpression.empty()) {
                    expr.push_back(elementOfExpression);
                }
            }
//            for (string num: expr) {
//                cout << num << ' ';
//            }
            cout << endl;
            for (string elem: expr) {
                if (elem == "+") {
                    double second = values.top();
                    values.pop();
                    double first = values.top();
                    values.pop();
                    double num = first + second;
                    values.push(num);
                } else if (elem == "-") {
                    double second = values.top();
                    values.pop();
                    double first = values.top();
                    values.pop();
                    double num = first - second;
                    values.push(num);
                } else if (elem == "*") {
                    double second = values.top();
                    values.pop();
                    double first = values.top();
                    values.pop();
                    double num = first * second;
                    values.push(num);
                } else if (elem == "/") {
                    double second = values.top();
                    values.pop();
                    double first = values.top();
                    values.pop();
                    double num = first / second;
                    values.push(num);
                } else {
                    double number = 0;
                    for (char num: elem) {
                        if (num == '-')
                            number *= -1;
                        else {
                            number *= 10;
                            number += num - 48;
                        }
                    }
                    values.push(number);
                }
            }
            cout <<"answer = "<< values.top();
            values.pop();
            cout << endl;
        }
    }

};

int main()
{
    cout << "start analyze" << endl;
    ifstream in;
    in.open("../samples.txt");
    string primer;
    while(getline(in, primer)) {
        ExpressionParser ep(primer);
        ep.analyze();
        cout<<endl;
    }
    cout <<endl<< "end"<<endl;
    in.close();
    return 0;
}
