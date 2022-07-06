#include "keyboard.h"
#include "calculator.h"
#include "cpu.h"

void ChristoferKeyboard::addKey(Key *key)
{
  this->keys[this->KeysCount] = key;
  key->setReceiver(this);
  KeysCount++;
}

void ChristoferKeyboard::receiveDigit(Digit digit)
{
  this->cpu ? this->cpu->receiveDigit(digit) : void();
};
void ChristoferKeyboard::receiveOperation(Operation operation)
{
  this->cpu ? this->cpu->receiveOperation(operation) : void();
};
void ChristoferKeyboard::receiveControl(Control control)
{
  this->cpu ? this->cpu->receiveControl(control) : void();
};