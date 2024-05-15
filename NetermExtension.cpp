#include "Header.h"
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
int NetermE::analyzeExpression(AutomatStack* magaz) {
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
int NetermT::analyzeExpression(AutomatStack* magaz)
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
int NetermP::analyzeExpression(AutomatStack* magaz)
{
    return -1;
}
void NetermPlus::performExpression(AutomatStack* magaz)
{
    cout<<valueOfNeterm;
}
int NetermPlus::analyzeExpression(AutomatStack* magaz)
{
    return -1;
}
void NetermMult::performExpression(AutomatStack* magaz)
{
    cout<<valueOfNeterm;
}
int NetermMult::analyzeExpression(AutomatStack* magaz)
{
    return -1;
}