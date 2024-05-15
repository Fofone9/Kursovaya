//#include"Header.h"
//using namespace std;
//enum types
//{
//    E,
//    T,
//    P,
//    OPERATOR
//};
//class Neterm
//{
//public:
//    int startPosition;
//    int type;
//    string valueOfNeterm;
//
//public:
//    Neterm() { valueOfNeterm = ""; }
//    Neterm(string val) : valueOfNeterm(val) {};
//    virtual void performExpression(AutomatStack* magaz) = 0;
//    virtual int analizeExpression(AutomatStack* magaz) = 0;
//    int skipBrackets(int position) {
//        int sumOfBrackets = 1;
//        position++;
//        while (sumOfBrackets != 0)
//        {
//            switch (valueOfNeterm[position])
//            {
//                case '(':
//                    sumOfBrackets++;
//                    position++;
//                    break;
//                case ')':
//                    sumOfBrackets--;
//                    position++;
//                    break;
//                default:
//                    position++;
//            }
//        }
//        return position;
//    }
//};
//class NetermE :public Neterm {
//public:
//    NetermE() {
//        valueOfNeterm = "";
//        type = E;
//    };
//    NetermE(string val, int pos) : Neterm(val) {
//        type = E;
//        startPosition = pos;
//    };
//    string getVal() {
//        return valueOfNeterm;
//    }
//    int searchOperator() {
//        for (int i = 0; i < valueOfNeterm.size(); i++) {
//            switch (valueOfNeterm[i])
//            {
//                case '+':
//                    return i;
//                    break;
//                case '(':
//                    i = skipBrackets(i);
//                default:
//                    break;
//            }
//        }
//        return -1;
//    }
//    void performExpression(AutomatStack*);
//    int analizeExpression(AutomatStack*);
//};
//
//class NetermT :public Neterm {
//public:
//    NetermT() {
//        valueOfNeterm = "";
//        type = T;
//    };
//    NetermT(string val, int pos) : Neterm(val) {
//        type = T;
//        startPosition = pos;
//    };
//    string getVal() {
//        return valueOfNeterm;
//    };
//    int searchOperator() {
//        for (int i = 0; i < valueOfNeterm.size(); i++) {
//            switch (valueOfNeterm[i])
//            {
//                case '*':
//                    return i;
//                    break;
//                case '(':
//                    i = skipBrackets(i);
//                default:
//                    break;
//            }
//        }
//        return -1;
//    }
//    void performExpression(AutomatStack* magaz);
//    int analizeExpression(AutomatStack*);
//};
//
//class NetermP :public Neterm {
//public:
//    NetermP() {
//        valueOfNeterm = "";
//        type = P;
//    };
//    NetermP(string val, int pos) : Neterm(val) {
//        type = P;
//        startPosition = pos;
//    };
//    string getVal() {
//        return valueOfNeterm;
//    };
//    void performExpression(AutomatStack* magaz);
//    int analizeExpression(AutomatStack*);
//};
//class NetermPlus :public Neterm {
//public:
//    NetermPlus(int pos) {
//        type = OPERATOR;
//        valueOfNeterm = '+';
//        startPosition = pos;
//    }
//    void performExpression(AutomatStack* magaz);
//    int analizeExpression(AutomatStack*);
//};
//class NetermMult :public Neterm {
//public:
//    NetermMult(int pos) {
//        type = OPERATOR;
//        valueOfNeterm = '*';
//        startPosition = pos;
//    }
//    void performExpression(AutomatStack* magaz);
//    int analizeExpression(AutomatStack*);
//};
