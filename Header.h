#pragma once
#include<iostream>
using namespace std;
class Neterm;
class NetermE;
class NetermT;
class NetermP;
class NetermPlus;
class NetermMult;
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
    virtual int analyzeExpression(AutomatStack* magaz) = 0;
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
    void performExpression(AutomatStack*)override;
    int analyzeExpression(AutomatStack*)override;
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
    int analyzeExpression(AutomatStack*);
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
    int analyzeExpression(AutomatStack*);
};
class NetermPlus :public Neterm {
public:
    NetermPlus(int pos) {
        type = OPERATOR;
        valueOfNeterm = '+';
        startPosition = pos;
    }
    void performExpression(AutomatStack* magaz);
    int analyzeExpression(AutomatStack*);
};
class NetermMult :public Neterm {
public:
    NetermMult(int pos) {
        type = OPERATOR;
        valueOfNeterm = '*';
        startPosition = pos;
    }
    void performExpression(AutomatStack* magaz);
    int analyzeExpression(AutomatStack*);
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