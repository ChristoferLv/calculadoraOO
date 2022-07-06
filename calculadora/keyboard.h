#pragma once
#include "calculator.h"
#include "cpu.h"
class Key;
class ChristoferKeyboard : public Keyboard
{
    Key *keys[200];
    int KeysCount = 0;

public:

    void addKey(Key *);
    void receiveDigit(Digit);
    void receiveOperation(Operation);
    void receiveControl(Control);
};