#include<iostream>
#include<fstream>
#include<stack>
#include "Header.h"
//#include "NetermExtension.cpp"
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
        NetermE *S;
        S = new NetermE(expression, 0);
        magazine.push(S);
        while (!magazine.empty()) {
            Neterm* currentNeterm = magazine.pop();
            currentNeterm->performExpression(&magazine);
        }
        cout<<endl;
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
