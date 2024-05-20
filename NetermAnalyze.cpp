#include "Header.h"
int NetermE::analyzeExpression(AutomateStack* automateStack) {
    int indexOfOperator = searchOperator();
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
        if (eExpression.empty()) {
            if (isPlus){
                type = UP;
            }
            else{
                type = US;
            }
            return startPosition + indexOfOperator + 1;
        }
        if(tExpression.empty()){
            if (isPlus){
                type = UP;
            }
            else{
                type = US;
            }
            return startPosition;
        }
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        NetermOperator *oper;
        if (isPlus){
            oper = new NetermPlus(startPosition + indexOfOperator);
        }
        else{
            oper = new NetermSubtraction(startPosition + indexOfOperator);
        }
        NetermE *e;
        e = new NetermE(eExpression, startPosition + indexOfOperator + 1);
        automateStack->push(e);
        automateStack->push(oper);
        automateStack->push(t);

    }
    return -1;
}
int NetermT::analyzeExpression(AutomateStack* automateStack)
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
        if (tExpression.empty()){
            type = UO;
            return startPosition + indexOfOperator + 1;
        }
        if(pExpression.empty()){
            if (isMulti){
                type = UM;
            }
            else{
                type = UD;
            }
            return startPosition;
        }
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

        automateStack->push(t);
        automateStack->push(oper);
        automateStack->push(p);
    }
    return -1;
}

int NetermP::analyzeExpression(AutomateStack* automateStack)
{
    int size = valueOfNeterm.size();
    bool hasBrackets = searchBrackets();

    if (hasBrackets) {
        if (valueOfNeterm[0] == '(' and valueOfNeterm[size - 1] == ')') {
            string eExpression(valueOfNeterm, 1, size - 2);
            if (eExpression.empty()) {
                type = EB;
                return startPosition + 1;
            }
            NetermE *e;
            e = new NetermE(eExpression, startPosition + 1);
            automateStack->push(e);
        } else if (valueOfNeterm[0] == '(') {
            int i = 0;
            for(; i<size;i++){
                if (valueOfNeterm[i]==')'){
                    break;
                }
            }
            type = NONOPERA;
            return startPosition+i;
        } else {
            int i = 0;
            for(; i<size;i++){
                if (valueOfNeterm[i]=='('){
                    break;
                }
            }
            type = NONOPERB;
            return startPosition+i;
        }
    }
    return -1;
}

int NetermOperator::analyzeExpression(AutomateStack* automateStack)
{
    return -1;
}

