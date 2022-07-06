#pragma once
#include "display.h"
#include "calculator.h"
//#include "enumerators.h"
class ChristoferCpu : public Cpu
{
private:
    // /ChristoferDisplay *display;
    int op1Count = 0;
    int op1DecimalPosition = 0;
    Signal op1Signal = Signal::POSITIVE;
    int op2Count = 0;
    int op2DecimalPosition = 0;
    Signal op2Signal = Signal::POSITIVE;
    Digit op1[8];
    Digit op2[8];
    bool halt = false;
    Operation operation = Operation::NONE;
    bool pontoUsado = false;

    int memCount = 0;
    int memDecimalPosition = 0;
    Digit memValue[8];
    Signal memSignal = Signal::POSITIVE;
    bool mrcPressed = false;

    void addMemory();
    void subtractMemory();
    void memoryRecall();
    void findDecimalPoint(double valorE, bool memoryOperation, Operation operation, bool unary);
    void resultToRegister(float result, int count, int decimalPosition, bool memoryOperation, Digit* destino);
    void calculate(bool memoryOperation, Operation operation);
    double convertToInt(Digit *v, int opCount, int decimalPos, Signal signal);
    void showResult(Digit valor[], int count, int decimalSeparator, Signal signal, bool unary);
    void memoryToRegister();
    void resetValues(Digit *v);
    void vectorToVector(Digit vO[], Digit vD[]);
    void reset();
    void clearAllValues();
    void clearValue();
    void setDecimalPosition();
    double raiz(double valor);
    double percentage(double valor);
    Digit intToDigit(int k);
    int digitToInt(Digit k);

public:
    void receiveDigit(Digit);
    void receiveOperation(Operation);
    void receiveControl(Control);
};