#pragma once
#include "calculator.h"
//#include "enumerators.h"
class ChristoferDisplay : public Display
{
public:
    void add(Digit);
    void setDecimalSeparator();
    void setSignal(Signal signal);
   // void proximaLinha();
    void setError();
    void clear();
};