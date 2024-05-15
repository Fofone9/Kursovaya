#pragma once
#include<iostream>
using namespace std;
class Neterm;
class NetermE;
class NetermT;
class NetermP;
class NetermPlus;
class NetermMulti;
class AutomateStack;
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
    Neterm() {
        valueOfNeterm = "";
        startPosition = 0;
        type = 0;
    }
    explicit Neterm(const string& val) : valueOfNeterm(val) {
        valueOfNeterm = val;
        startPosition = 0;
        type = 0;
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
        type = E;
    };
    NetermE(const string& val, int pos) : Neterm(val) {
        type = E;
        startPosition = pos;
    };
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '+':
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
        type = T;
    };
    NetermT(const string& val, int pos) : Neterm(val) {
        type = T;
        startPosition = pos;
    };
    int searchOperator() {
        for (int i = 0; i < valueOfNeterm.size(); i++) {
            switch (valueOfNeterm[i])
            {
                case '*':
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
        type = P;
    };
    NetermP(const string& val, int pos) : Neterm(val) {
        type = P;
        startPosition = pos;
    };
    void performExpression(AutomateStack* automateStack) override;
    int analyzeExpression(AutomateStack*) override;
};
class NetermPlus :public Neterm {
public:
    explicit NetermPlus(int pos) {
        type = OPERATOR;
        valueOfNeterm = '+';
        startPosition = pos;
    }
    void performExpression(AutomateStack*) override;
    int analyzeExpression(AutomateStack*) override;
};
class NetermMulti :public Neterm {
public:
    explicit NetermMulti(int pos) {
        type = OPERATOR;
        valueOfNeterm = '*';
        startPosition = pos;
    }
    void performExpression(AutomateStack*) override;
    int analyzeExpression(AutomateStack*) override;
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
    void push(NetermPlus* b) {
        Node* node = new Node(b);
        node->next = root;
        root = node;
    }
    void push(NetermMulti* b) {
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