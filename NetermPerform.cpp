#include "Header.h"
string NetermE::performExpression(AutomateStack* automateStack) {
    int indexOfOperator;
    if (valueOfNeterm[0] == '-' and mayBeMinus) {
        indexOfOperator = searchOperator(1);
    }
    else{
        indexOfOperator = searchOperator(0);
    }
    if (indexOfOperator == -1) {
        string tExpression = valueOfNeterm;
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        automateStack->push(t);
    }
    else
    {
        bool isPlus = valueOfNeterm[indexOfOperator]=='+';
        string tExpression(valueOfNeterm, 0, indexOfOperator);
        string eExpression(valueOfNeterm, indexOfOperator + 1, valueOfNeterm.size() - 1);
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        NetermE *e;
        e = new NetermE(eExpression, startPosition + indexOfOperator + 1, false);
        NetermOperator *oper;
        if (isPlus){
            oper = new NetermPlus(startPosition + indexOfOperator);
        }
        else{
            oper = new NetermSubtraction(startPosition + indexOfOperator);
        }
        automateStack->push(oper);
        automateStack->push(e);
        automateStack->push(t);
    }
    return "";
}
string NetermT::performExpression(AutomateStack* automateStack)
{
    int indexOfOperator = searchOperator();
    if (indexOfOperator == -1) {
        string pExpression = valueOfNeterm;
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        automateStack->push(p);
    }
    else
    {
        bool isMulti = valueOfNeterm[indexOfOperator]=='*';
        string pExpression(valueOfNeterm, 0, indexOfOperator);
        string tExpression(valueOfNeterm, indexOfOperator + 1, valueOfNeterm.size() - 1);
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        NetermT *t;
        t = new NetermT(tExpression, startPosition + indexOfOperator + 1);
        NetermOperator *oper;
        if (isMulti){
            oper = new NetermMulti(startPosition + indexOfOperator);
        }
        else{
            oper = new NetermDivision(startPosition + indexOfOperator);
        }
        automateStack->push(oper);
        automateStack->push(t);
        automateStack->push(p);


    }
    return "";
}
string NetermP::performExpression(AutomateStack* automateStack)
{
    if (valueOfNeterm[0] == '(' ){
        string eExpression(valueOfNeterm, 1, valueOfNeterm.size()-2);
        NetermE* e;
        e = new NetermE(eExpression, startPosition+1);
        automateStack->push(e);
        return "";
    }
    else {
       return valueOfNeterm;
    }
}
string NetermOperator::performExpression(AutomateStack* automateStack)
{
    return valueOfNeterm;
}

