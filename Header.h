#pragma once
#include<iostream>
using namespace std;
class Neterm;
class NetermE;
class NetermT;
class NetermP;
class NetermPlus;
class NetermMulti;
class NetermOperator;
class AutomateStack;
struct Node;
enum errorTypes
{
    OK, //все норм
    UB, //лишняя скобка
    UP, //лишний плюс
    UM, //лишнее умножение
    NONOPERB, //нужен опрератор перед скобками
    NONOPERA, //нужен опрератор после скобок
    EB, //пустые скобки
    UD, //лишнее деление
    US, //лишнее вычитание
    UO, //лишний оператор после деления или умножения
};
class Neterm
{
public:
    int startPosition;
    int type;
    string valueOfNeterm;

public:
    Neterm() {
        valueOfNeterm = "";
        startPosition = 0;
        type = OK;
    }
    explicit Neterm(const string& val) : valueOfNeterm(val) {
        valueOfNeterm = val;
        startPosition = 0;
        type = OK;
    };
    virtual void performExpression(AutomateStack* automateStack) = 0;
    virtual int analyzeExpression(AutomateStack* automateStack) = 0;
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
        position--;
        return position;
    }
};
class NetermE :public Neterm {
public:
    NetermE() {
        valueOfNeterm = "";
        type = OK;
    };
    NetermE(const string& val, int pos) : Neterm(val) {
        type = OK;
        startPosition = pos;
    };
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '+':
                case '-':
                    return i;
                case '(':
                    i = skipBrackets(i);
                default:
                    break;
            }
        }
        return -1;
    }
    void performExpression(AutomateStack*)override;
    int analyzeExpression(AutomateStack*)override;
};

class NetermT :public Neterm {
public:
    NetermT() {
        valueOfNeterm = "";
        type = OK;
    };
    NetermT(const string& val, int pos) : Neterm(val) {
        type = OK;
        startPosition = pos;
    };
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '*':
                case '/':
                    return i;
                case '(':
                    i = skipBrackets(i);
                default:
                    break;
            }
        }
        return -1;
    }
    void performExpression(AutomateStack* automateStack) override;
    int analyzeExpression(AutomateStack*) override;
};

class NetermP :public Neterm {
public:
    NetermP() {
        valueOfNeterm = "";
        type = OK;
    };
    NetermP(const string& val, int pos) : Neterm(val) {
        type = OK;
        startPosition = pos;
    };
    void performExpression(AutomateStack* automateStack) override;
    int analyzeExpression(AutomateStack*) override;
    bool searchBrackets(){
        for (auto character: valueOfNeterm) {
            if (character == '(') return true;
        }
        return false;
    }
};
class NetermOperator: public Neterm{
public:
    explicit NetermOperator(int pos) {
        type = OK;
        startPosition = pos;
    }
    void performExpression(AutomateStack*) override;
    int analyzeExpression(AutomateStack*) override;
};
class NetermPlus :public NetermOperator {
public:
    explicit NetermPlus (int pos): NetermOperator(pos){
    valueOfNeterm = '+';
}
};
class NetermMulti :public NetermOperator {
public:
    explicit NetermMulti(int pos): NetermOperator(pos) {
        valueOfNeterm = '*';
    }
};
class NetermDivision: public NetermOperator{
public:
    explicit NetermDivision(int pos): NetermOperator(pos) {
        valueOfNeterm = '/';
    }
};
class NetermSubtraction: public NetermOperator{
public:
    explicit NetermSubtraction(int pos): NetermOperator(pos) {
        valueOfNeterm = '-';
    }
};
struct Node {
    Neterm* val;
    Node* next;
    Node(Neterm* v) {
        val = v;
        next = nullptr;
    }
};
class AutomateStack
{
    Node* root;
public:
    AutomateStack() { root = nullptr; }
    explicit AutomateStack(NetermE* b) {
        root = new Node(b);
    }
    explicit AutomateStack(NetermP* b) {
        root = new Node(b);
    }
    explicit AutomateStack(NetermT* b) {
        root = new Node(b);
    }
    explicit AutomateStack(NetermPlus* b) {
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

    void push(NetermOperator* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    Neterm* pop() {
        Node* node = root;
        root = root->next;
        return static_cast<Neterm *>(node->val);
    }
    bool empty() {
        return root == nullptr;
    }
};