#include<iostream>
#include<stack>
#include "Header.h"
//#include "NetermExtension.cpp"
using namespace std;

class ExpressionParser {
    string expression;
    AutomatStack magazine;
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
            NetermE* S = new NetermE(expression, 0);
            magazine.push(S);
            exceptionPosition = 0;
            while (!magazine.empty()) {
                Neterm* currentNeterm = magazine.pop();
                exceptionPosition = currentNeterm->analyzeExpression(&magazine);
                if (exceptionPosition != -1){
                    showException();
                    return;
                }
            }
            magazine = AutomatStack();
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

                        exeptionType = "Обнаружена лишняя закрывающая скобка";
                        return i;
                    }
                    brackets.pop();
                    break;
                default:
                    break;
            }
        }
        if (!brackets.empty()){

            exeptionType = "Обнаружена лишняя открывающаяся скобка";
            return brackets.top();
        }
        return -1;
    }
    void showException(){
        cout<<expression<<endl;
        for (int i = 0; i < exceptionPosition; i++){
            cout<<'-';
        }
        cout<<'^'<<endl;
        cout<<exeptionType<<endl;

    }
    void perform() {
        NetermE* S = new NetermE(expression,0);
        magazine.push(S);
        while (!magazine.empty()) {
            Neterm* currentNeterm = magazine.pop();
            currentNeterm->performExpression(&magazine);
        }
    }

};

int main()
{
    string primer = "1*a+b*c+2";
    ExpressionParser ep(primer);
    cout<<primer<<endl<<"start analyze"<<endl;
    ep.analyze();
    cout <<endl<< "end"<<endl;
    return 0;
}
