#include "Header.h"
void NetermE::performExpression(AutomateStack* automateStack) {
    int indexOfPlus = searchOperator();
    if (indexOfPlus == -1) {
        string tExpression = valueOfNeterm;
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        automateStack->push(t);
    }
    else
    {
        string tExpression(valueOfNeterm, 0, indexOfPlus);
        string eExpression(valueOfNeterm, indexOfPlus + 1, valueOfNeterm.size() - 1);
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        NetermE *e;
        e = new NetermE(eExpression, startPosition + indexOfPlus + 1);
        NetermPlus *plus;
        plus = new NetermPlus(indexOfPlus + startPosition);
        automateStack->push(plus);
        automateStack->push(e);
        automateStack->push(t);
    }
}
int NetermE::analyzeExpression(AutomateStack* automateStack) {
    int indexOfPlus = searchOperator();
    if (indexOfPlus == -1) {
        string tExpression = valueOfNeterm;
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        automateStack->push(t);
    }
    else
    {
        string tExpression(valueOfNeterm, 0, indexOfPlus);
        string eExpression(valueOfNeterm, indexOfPlus + 1, valueOfNeterm.size() - 1);
        if (eExpression.empty()) {
            type = UP;
            return startPosition + indexOfPlus + 1;
        }

        if(tExpression.empty()){
            type = UP;
            return startPosition;
        }
        NetermT *t;
        t = new NetermT(tExpression, startPosition);
        NetermPlus *plus;
        plus = new NetermPlus(startPosition + indexOfPlus);
        NetermE *e;
        e = new NetermE(eExpression, startPosition + indexOfPlus + 1);
        automateStack->push(e);
        automateStack->push(plus);
        automateStack->push(t);

    }
    return -1;
}
void NetermT::performExpression(AutomateStack* automateStack)
{

    int indexOfMulti = searchOperator();
    if (indexOfMulti == -1) {
        string pExpression = valueOfNeterm;
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        automateStack->push(p);
    }
    else
    {
        string pExpression(valueOfNeterm, 0, indexOfMulti);
        string tExpression(valueOfNeterm, indexOfMulti + 1, valueOfNeterm.size() - 1);
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        NetermT *t;
        t = new NetermT(tExpression, startPosition + indexOfMulti + 1);
        NetermMulti *multi;
        multi = new NetermMulti(startPosition + indexOfMulti);
        automateStack->push(multi);
        automateStack->push(t);
        automateStack->push(p);


    }
}
int NetermT::analyzeExpression(AutomateStack* automateStack)
{
    int indexOfMulti = searchOperator();
    if (indexOfMulti == -1) {
        string pExpression = valueOfNeterm;
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        automateStack->push(p);
    }
    else
    {
        string pExpression(valueOfNeterm, 0, indexOfMulti);
        string tExpression(valueOfNeterm, indexOfMulti + 1, valueOfNeterm.size() - 1);
        if (tExpression.empty()){
            type = UP;
            return startPosition + indexOfMulti + 1;
        }
        if(pExpression.empty()){
            type = UM;
            return startPosition;
        }
        NetermP *p;
        p = new NetermP(pExpression, startPosition);
        NetermT *t;
        t = new NetermT(tExpression, startPosition + indexOfMulti + 1);
        NetermMulti *multi;
        multi = new NetermMulti(startPosition + indexOfMulti);
        automateStack->push(t);
        automateStack->push(multi);
        automateStack->push(p);
    }
    return -1;
}
void NetermP::performExpression(AutomateStack* automateStack)
{
    if (valueOfNeterm[0] == '(' ){
        string eExpression(valueOfNeterm, 1, valueOfNeterm.size()-2);
        NetermE* e;
        e = new NetermE(eExpression, startPosition+1);
        automateStack->push(e);
    }
    else {
        cout << valueOfNeterm;
    }
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
void NetermPlus::performExpression(AutomateStack* automateStack)
{
    cout<<valueOfNeterm;
}
int NetermPlus::analyzeExpression(AutomateStack* automateStack)
{
    return -1;
}
void NetermMulti::performExpression(AutomateStack* automateStack)
{
    cout<<valueOfNeterm;
}
int NetermMulti::analyzeExpression(AutomateStack* automateStack)
{
    return -1;
}