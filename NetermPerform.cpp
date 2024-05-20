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
void NetermOperator::performExpression(AutomateStack* automateStack)
{
    cout<<valueOfNeterm;
}

