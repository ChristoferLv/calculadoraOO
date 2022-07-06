#include <iostream>
#include "calculator.h"
//#include "enumerators.h"
#include "keyboard.h"
#include "cpu.h"
#include "display.h"

int main()
{
    /*Display* d1 = new ChristoferDisplay();
    Cpu* cpu1 = new ChristoferCpu();
    cpu1->setDisplay(d1);
    cpu1->receiveDigit(ONE);
    cpu1->receiveDigit(ONE);
    cpu1->receiveOperation(SUBTRACTION);
    cpu1->receiveDigit(TWO);
    cpu1->receiveDigit(ONE);
    cpu1->receiveControl(EQUAL);*/

    Keyboard *k1 = new ChristoferKeyboard();
    Display *d1 = new ChristoferDisplay();
    Cpu *cpu1 = new ChristoferCpu();
    KeyDigit nKey0(Digit::ZERO), nKey1(Digit::ONE), nKey2(Digit::TWO), nKey3(Digit::THREE), nKey4(Digit::FOUR), nKey5(Digit::FIVE), nKey6(Digit::SIX), nKey7(Digit::SEVEN), nKey8(Digit::EIGHT), nKey9(Digit::NINE);
    KeyOperation oKey0(Operation::ADDITION), oKey1(Operation::SUBTRACTION), oKey2(Operation::MULTIPLICATION), oKey3(Operation::DIVISION), oKey4(SQUARE_ROOT), oKey5(PERCENTAGE);
    KeyControl cKey0(Control::EQUAL), cKey1(Control::MEMORY_READ_CLEAR), cKey2(Control::MEMORY_ADDITION), cKey3(Control::MEMORY_SUBTRACTION), cKey4(Control::CLEAR), cKey5(Control::RESET), cKey6(Control::DECIMAL_SEPARATOR);
    k1->setCpu(cpu1);
    cpu1->setDisplay(d1);


    k1->addKey(&nKey0);
    k1->addKey(&nKey1);
    k1->addKey(&nKey2);
    k1->addKey(&nKey3);
    k1->addKey(&nKey4);
    k1->addKey(&nKey5);
    k1->addKey(&nKey6);
    k1->addKey(&nKey7);
    k1->addKey(&nKey8);
    k1->addKey(&nKey9);

    k1->addKey(&oKey0);
    k1->addKey(&oKey1);
    k1->addKey(&oKey2);
    k1->addKey(&oKey3);
    k1->addKey(&oKey4);
    k1->addKey(&oKey5);
    
    k1->addKey(&cKey0);
    k1->addKey(&cKey1);
    k1->addKey(&cKey2);
    k1->addKey(&cKey3);
    k1->addKey(&cKey4);
    k1->addKey(&cKey5);
    k1->addKey(&cKey6);
    
    nKey9.press();
    oKey4.press();
    oKey0.press();
    nKey1.press();
    cKey0.press();
}
