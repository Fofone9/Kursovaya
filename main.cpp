#include<iostream>
#include<stack>
using namespace std;
class NetermE;
class NetermT;
class NetermP;
class NetermPlus;
class AutomatStack;
struct Node;

enum types
{
    E,
    T,
    P,
    OPERATOR
};
class Neterm
{
public:
    int startPosition;
    int type;
    string valueOfNeterm;

public:
    Neterm() { valueOfNeterm = ""; }
    Neterm(string val) : valueOfNeterm(val) {};
    virtual void performExpression(AutomatStack* magaz) = 0;
    virtual int analizeExpression(AutomatStack* magaz) = 0;
    int skipBrackets(int position) {
        int sumOfBrackets = 1;
        position++;
        while (sumOfBrackets != 0)
        {
            switch (valueOfNeterm[position])
            {
                case '(':
                    sumOfBrackets++;
                    position++;
                    break;
                case ')':
                    sumOfBrackets--;
                    position++;
                    break;
                default:
                    position++;
            }
        }
        return position;
    }
};
class NetermE :public Neterm {
public:
    NetermE() {
        valueOfNeterm = "";
        type = E;
    };
    NetermE(string val, int pos) : Neterm(val) {
        type = E;
        startPosition = pos;
    };
    string getVal() {
        return valueOfNeterm;
    }
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '+':
                    return i;
                    break;
                case '(':
                    i = skipBrackets(i);
                default:
                    break;
            }
        }
        return -1;
    }
    void performExpression(AutomatStack*);
    int analizeExpression(AutomatStack*);
};

class NetermT :public Neterm {
public:
    NetermT() {
        valueOfNeterm = "";
        type = T;
    };
    NetermT(string val, int pos) : Neterm(val) {
        type = T;
        startPosition = pos;
    };
    string getVal() {
        return valueOfNeterm;
    };
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '*':
                    return i;
                    break;
                case '(':
                    i = skipBrackets(i);
                default:
                    break;
            }
        }
        return -1;
    }
    void performExpression(AutomatStack* magaz);
    int analizeExpression(AutomatStack*);
};

class NetermP :public Neterm {
public:
    NetermP() {
        valueOfNeterm = "";
        type = P;
    };
    NetermP(string val, int pos) : Neterm(val) {
        type = P;
        startPosition = pos;
    };
    string getVal() {
        return valueOfNeterm;
    };
    void performExpression(AutomatStack* magaz);
    int analizeExpression(AutomatStack*);
};
class NetermPlus :public Neterm {
public:
    NetermPlus(int pos) {
        type = OPERATOR;
        valueOfNeterm = '+';
        startPosition = pos;
    }
    void performExpression(AutomatStack* magaz);
    int analizeExpression(AutomatStack*);
};
class NetermMult :public Neterm {
public:
    NetermMult(int pos) {
        type = OPERATOR;
        valueOfNeterm = '*';
        startPosition = pos;
    }
    void performExpression(AutomatStack* magaz);
    int analizeExpression(AutomatStack*);
};

struct Node {
    Neterm* val;
    Node* next;
    Node(Neterm* v) {
        val = v;
        next = nullptr;
    }
};
class AutomatStack
{
    Node* root;
public:
    AutomatStack() { root = nullptr; }
    AutomatStack(NetermE* b) {
        root = new Node(b);
    }
    AutomatStack(NetermP* b) {
        root = new Node(b);
    }
    AutomatStack(NetermT* b) {
        root = new Node(b);
    }
    AutomatStack(NetermPlus* b) {
        root = new Node(b);
    }
    void push(NetermE* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    void push(NetermP* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    void push(NetermT* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    void push(NetermPlus* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    void push(NetermMult* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    Neterm* pop() {
        Node* node = root;
        root = root->next;
        Neterm* answer = static_cast<Neterm*>(node->val);
        return answer;
    }
    bool empty() {
        return root == nullptr;
    }
};
void NetermE::performExpression(AutomatStack* magaz) {
    int indexOfPlus = searchOperator();
    if (indexOfPlus == -1) {
        string tExpresion = valueOfNeterm;
        NetermT* t = new NetermT(tExpresion, startPosition);
        magaz->push(t);
    }
    else
    {
        string tExpresion(valueOfNeterm, 0, indexOfPlus);
        string eExpresion(valueOfNeterm, indexOfPlus + 1, valueOfNeterm.size() - 1);
        NetermT* t = new NetermT(tExpresion, startPosition+indexOfPlus+1);
        NetermE* e = new NetermE(eExpresion, startPosition);
        NetermPlus* plus = new NetermPlus(indexOfPlus+startPosition);
        magaz->push(plus);
        magaz->push(t);
        magaz->push(e);

    }
}
int NetermE::analizeExpression(AutomatStack* magaz) {
    int indexOfPlus = searchOperator();
    if (indexOfPlus == -1) {
        string tExpresion = valueOfNeterm;
        NetermT* t = new NetermT(tExpresion, startPosition);
        magaz->push(t);
    }
    else
    {
        string tExpresion(valueOfNeterm, 0, indexOfPlus);
        string eExpresion(valueOfNeterm, indexOfPlus + 1, valueOfNeterm.size() - 1);
        if (eExpresion.size()==0){
            return startPosition+indexOfPlus+1;
        }
        if(tExpresion.size()==0){
            return startPosition;
        }
        NetermT* t = new NetermT(tExpresion, startPosition);
        NetermPlus* plus = new NetermPlus(startPosition+indexOfPlus);
        NetermE* e = new NetermE(eExpresion, startPosition+indexOfPlus+1);
        magaz->push(e);
        magaz->push(plus);
        magaz->push(t);

    }
    return -1;
}
void NetermT::performExpression(AutomatStack* magaz)
{

    int indexOfMult = searchOperator();
    if (indexOfMult == -1) {
        string pExpresion = valueOfNeterm;
        NetermP* p = new NetermP(pExpresion, startPosition);
        magaz->push(p);
    }
    else
    {
        string pExpresion(valueOfNeterm, 0, indexOfMult);
        string tExpresion(valueOfNeterm, indexOfMult + 1, valueOfNeterm.size() - 1);
        NetermP* p = new NetermP(pExpresion, startPosition);
        NetermT* t = new NetermT(tExpresion, startPosition+indexOfMult+1);
        NetermMult* mult = new NetermMult(startPosition+indexOfMult);
        magaz->push(t);
        magaz->push(mult);
        magaz->push(p);

    }
}
int NetermT::analizeExpression(AutomatStack* magaz)
{
    int indexOfMult = searchOperator();
    if (indexOfMult == -1) {
        string pExpresion = valueOfNeterm;
        NetermP* p = new NetermP(pExpresion, startPosition);
        magaz->push(p);
    }
    else
    {
        string pExpresion(valueOfNeterm, 0, indexOfMult);
        string tExpresion(valueOfNeterm, indexOfMult + 1, valueOfNeterm.size() - 1);
        if (tExpresion.size()==0){
            return startPosition+indexOfMult+1;
        }
        if(pExpresion.size()==0){
            return startPosition;
        }
        NetermP* p = new NetermP(pExpresion, startPosition);
        NetermT* t = new NetermT(tExpresion, startPosition+indexOfMult+1);
        NetermMult* mult = new NetermMult(startPosition+indexOfMult);
        magaz->push(t);
        magaz->push(mult);
        magaz->push(p);
    }
    return -1;
}
void NetermP::performExpression(AutomatStack* magaz)
{
    cout<<valueOfNeterm;
}
int NetermP::analizeExpression(AutomatStack* magaz)
{
    return -1;
}
void NetermPlus::performExpression(AutomatStack* magaz)
{
    cout<<valueOfNeterm;
}
int NetermPlus::analizeExpression(AutomatStack* magaz)
{
    return -1;
}
void NetermMult::performExpression(AutomatStack* magaz)
{
    cout<<valueOfNeterm;
}
int NetermMult::analizeExpression(AutomatStack* magaz)
{
    return -1;
}
class ExpressionParser {
    string expression;
    AutomatStack magazine;
    int exeptionPosition;
    string exeptionType;
public:
    ExpressionParser()
    {
        expression = "";
    };
    ExpressionParser(string includingExpression) {
        expression = includingExpression;
    };
    void analize(){
        exeptionPosition = bracketsAnalize();
        if (exeptionPosition == -1){
            NetermE* S = new NetermE(expression, 0);
            magazine.push(S);
            exeptionPosition = 0;
            while (!magazine.empty()) {
                Neterm* currentNeterm = magazine.pop();
                exeptionPosition = currentNeterm->analizeExpression(&magazine);
                if (exeptionPosition!=-1){
                    showExeption();
                    return;
                }
            }
            magazine = AutomatStack();
            perform();}
        else{
            showExeption();
            return;
        }
    }
    int bracketsAnalize(){
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
    void showExeption(){
        cout<<expression<<endl;
        for (int i = 0; i<exeptionPosition;i++){
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
    string primer = "1**a+b*c+2";
    ExpressionParser ep(primer);
    cout<<primer<<endl<<"start analization"<<endl;
    ep.analize();
    cout <<endl<< "end"<<endl;
    return 0;
}
