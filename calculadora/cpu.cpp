#include "cpu.h"
#include <cmath>
#include <iostream>
//#include "calculator.h"
//#include "enumerators.h"

void ChristoferCpu::memoryRecall()
{
  showResult(memValue, memCount, memDecimalPosition, memSignal, false);
}

void ChristoferCpu::addMemory()
{
  calculate(true, Operation::ADDITION);
}

void ChristoferCpu::subtractMemory()
{
  calculate(true, Operation::SUBTRACTION);
}

void ChristoferCpu::vectorToVector(Digit vO[], Digit vD[])
{
  for (int i = 0; i < 8; i++)
  {
    vD[i] = vO[i];
  }
}

void ChristoferCpu::memoryToRegister()
{
  if (operation == Operation::NONE)
  {
    resetValues(op1);
    vectorToVector(memValue, op1);
    op1Count = memCount;
    op1DecimalPosition = memDecimalPosition;
    op1Signal = memSignal;
  }
  else
  {
    resetValues(op2);
    vectorToVector(memValue, op2);
    op2Count = memCount;
    op2DecimalPosition = memDecimalPosition;
    op2Signal = memSignal;
  }
}

double ChristoferCpu::raiz(double valor)
{
  return sqrt(valor);
}
double ChristoferCpu::percentage(double valor)
{
  return sqrt((valor / 100));
}

void ChristoferCpu::setDecimalPosition()
{
  if (operation == NONE)
  {
    if (op1Count == 0)
    {
      receiveDigit(Digit::ZERO);
      op1DecimalPosition = op1Count;
    }
    else
    {
      op1DecimalPosition = op1Count;
    }
  }
  else
  {
    if (op2Count == 0)
    {
      receiveDigit(Digit::ZERO);
    }
    op2DecimalPosition = op2Count;
  }
}

void ChristoferCpu::resetValues(Digit *v)
{
  for (int i = 0; i < 8; i++)
  {
    v[i] = Digit::ZERO;
  }
}

int ChristoferCpu::digitToInt(Digit k)
{
  switch (k)
  {
  case ZERO:
    return 0;
    break;
  case ONE:
    return 1;
    break;
  case TWO:
    return 2;
    break;
  case THREE:
    return 3;
    break;
  case FOUR:
    return 4;
    break;
  case FIVE:
    return 5;
    break;
  case SIX:
    return 6;
    break;
  case SEVEN:
    return 7;
    break;
  case EIGHT:
    return 8;
    break;
  case NINE:
    return 9;
    break;
  }
  return 0;
}

Digit ChristoferCpu::intToDigit(int k)
{
  switch (k)
  {
  case 0:
    return Digit::ZERO;
    break;
  case 1:
    return Digit::ONE;
    break;
  case 2:
    return Digit::TWO;
    break;
  case 3:
    return Digit::THREE;
    break;
  case 4:
    return Digit::FOUR;
    break;
  case 5:
    return Digit::FIVE;
    break;
  case 6:
    return Digit::SIX;
    break;
  case 7:
    return Digit::SEVEN;
    break;
  case 8:
    return Digit::EIGHT;
    break;
  case 9:
    return Digit::NINE;
    break;
  }
  return Digit::ZERO;
}

void ChristoferCpu::resultToRegister(float result, int count, int decimalPosition, bool memoryOperation, Digit *destino)
{
  if (result < 0)
  {
    result = result * -1;
  }
  int vTemp[8];
  int size = count;
  int valtemp = result * pow(10, (count - decimalPosition) == 0 ? 0 : decimalPosition);
  for (int i = 0; i < size; i++)
  {
    vTemp[i] = valtemp % 10;
    valtemp = valtemp / 10;
  }

  for (int i = 0; i < size; i++)
  {
    if (memoryOperation)
    {
      memValue[i] = ChristoferCpu::intToDigit(vTemp[size - i - 1]);
    }
    else
    {
      op1[i] = ChristoferCpu::intToDigit(vTemp[size - i - 1]);
    }
  }
}

double ChristoferCpu::convertToInt(Digit *v, int opCount, int decimalPos, Signal signal)
{
  double value = 0;
  if (opCount == 0)
    return value;
  for (int i = 0; i < opCount; i++)
  {
    value = value * 10 + ChristoferCpu::digitToInt(v[i]);
  }
  if (decimalPos != 0)
    value = value / (pow(10, opCount - decimalPos));

  if (signal == Signal::NEGATIVE)
  {
    value = (double)value * -1;
  }
  return value;
}

void ChristoferCpu::clearAllValues()
{
  resetValues(op1);
  resetValues(op2);
  op1Count = 0;
  op1DecimalPosition = 0;
  op2Count = 0;
  op2DecimalPosition = 0;
  op1Signal = Signal::POSITIVE;
  op1Signal = Signal::POSITIVE;
  operation = Operation::NONE;
}

void ChristoferCpu::calculate(bool memoryOperation, Operation operation)
{
  bool operationError = false;
  double op1Temp;
  double op2Temp;
  double result;
  if (memoryOperation)
  {
    if (ChristoferCpu::operation == NONE)
      op1Temp = convertToInt(op1, op1Count, op1DecimalPosition, op1Signal);
    else
      op1Temp = convertToInt(op2, op2Count, op2DecimalPosition, op2Signal);
    op2Temp = convertToInt(memValue, memCount, memDecimalPosition, memSignal);
  }
  else
  {
    op1Temp = convertToInt(op1, op1Count, op1DecimalPosition, op1Signal);
    op2Temp = convertToInt(op2, op2Count, op2DecimalPosition, op2Signal);
  }

  switch (operation)
  {
  case ADDITION:
    result = (op1Temp + op2Temp);
    break;
  case SUBTRACTION:
    result = op1Temp - op2Temp;
    break;
  case MULTIPLICATION:
    result = op1Temp * op2Temp;
    break;
  case DIVISION:
    result = op1Temp / op2Temp;
    break;
  case PERCENTAGE:
    result = percentage((operation == Operation::NONE ? op1Temp : op2Temp));
    findDecimalPoint(result, false, this->operation, true);
    if (operation == Operation::NONE)
    {
      resultToRegister(result, op1Count, op1DecimalPosition, false, op1);
      showResult(op1, op1Count, op1DecimalPosition, op1Signal, true);
    }
    else
    {
      resultToRegister(result, op2Count, op2DecimalPosition, false, op2);
      showResult(op2, op2Count, op2DecimalPosition, op2Signal, true);
    }
    break;
  case SQUARE_ROOT:
    result = ChristoferCpu::raiz((this->operation == Operation::NONE ? op1Temp : op2Temp));
    findDecimalPoint(result, false, this->operation, true);
    if (this->operation == Operation::NONE)
    {
      resultToRegister(result, op1Count, op1DecimalPosition, false, op1);
      showResult(op1, op1Count, op1DecimalPosition, op1Signal, true);
      return;
    }
    else
    {
      resultToRegister(result, op2Count, op2DecimalPosition, false, op2);
      showResult(op2, op2Count, op2DecimalPosition, op2Signal, true);
      return;
    }
    break;
  }
  // result = (int)(result * pow(10, 7));
  // result = result / pow(10, 7);

  if (result > 99999999 || result < -99999999)
  {
    operationError = true;
  }

  if (memoryOperation)
  {
    if (!operationError)
    {
      memSignal = (result < 0 ? Signal::NEGATIVE : Signal::POSITIVE);
      findDecimalPoint(result, memoryOperation, this->operation, false);
      resultToRegister(result, memCount, memDecimalPosition, memoryOperation, memValue);
    }
  }
  else
  {
    op1Count = 0;
    op1DecimalPosition = 0;
    op2Count = 0;
    op2DecimalPosition = 0;
    resetValues(op1);
    resetValues(op2);
    operation = Operation::NONE;
    if (operationError)
    {
      result = 0;
      this->halt = true;
      display->clear();
      display->setError();
    }
    else
    {
      op1Signal = (result < 0 ? Signal::NEGATIVE : Signal::POSITIVE);
      findDecimalPoint(result, memoryOperation, this->operation, false);
      resultToRegister(result, op1Count, op1DecimalPosition, memoryOperation, op1);
      showResult(op1, op1Count, op1DecimalPosition, op1Signal, false);
    }
  }
}

void ChristoferCpu::findDecimalPoint(double valorE, bool memoryOperation, Operation operation, bool unary)
{
  double valor = valorE;
  valor = (valor < 0 ? (double)valor * -1 : valor);
  double temp = valor;
  double temp2 = 0;
  int antes;
  int depois;
  double potencia = 0;

  if ((int)temp < 1)
  {
    antes = 1;
  }
  else
  {
    while (temp >= 1)
    {
      temp = temp / 10;
      temp2++;
    }
    antes = temp2;
  }

  valor = (int)(valor * pow(10, 7 - antes));
  valor = valor / pow(10, 7 - antes);

  temp = 0;
  temp2 = 0;

  if ((int)valor == valor)
  {
    depois = 0;
  }
  else
  {
    potencia = 10;
    for (int i = 1; i < 9; i++)
    {
      temp = (int)(valor * potencia) / potencia;
      temp = fmod(temp * potencia, potencia);
      temp = temp / pow(10, i);
      temp2 = valor - temp;
      if (temp2 == (int)valor)
      {
        depois = i;
        break;
      }
      potencia = potencia * 10;
    }
  }
  if (memoryOperation)
  {
    memCount = antes + depois;
    memDecimalPosition = (depois == 0 ? op1Count : depois);
    return;
  }
  else
  {
    if (unary)
    {
      if (operation != Operation::NONE)
      {
        op2Count = antes + depois;
        op2DecimalPosition = (depois == 0 ? op1Count : depois);
        return;
      }
    }
    op1Count = antes + depois;
    op1DecimalPosition = (depois == 0 ? op1Count : depois);
  }
}

void ChristoferCpu::showResult(Digit valor[], int count, int decimalSeparator, Signal signal, bool unary)
{
  display->clear();
  if (display == NULL)
    return;
  // if (count == 0)
  // display->add(Digit::ERRO);
  if (signal == Signal::NEGATIVE)
  {
    display->setSignal(Signal::NEGATIVE);
  }
  for (int i = 0; i < count; i++)
  {
    switch (valor[i])
    {
    case 0:
      display->add(Digit::ZERO);
      break;
    case 1:
      display->add(Digit::ONE);
      break;
    case 2:
      display->add(Digit::TWO);
      break;
    case 3:
      display->add(Digit::THREE);
      break;
    case 4:
      display->add(Digit::FOUR);
      break;
    case 5:
      display->add(Digit::FIVE);
      break;
    case 6:
      display->add(Digit::SIX);
      break;
    case 7:
      display->add(Digit::SEVEN);
      break;
    case 8:
      display->add(Digit::EIGHT);
      break;
    case 9:
      display->add(Digit::NINE);
      break;
    }
    if (i == op1DecimalPosition)
    {
      display->setDecimalSeparator();
    }
  }
  if (!unary)
    display->clear();
}

void ChristoferCpu::clearValue()
{
  if (operation == NONE)
  {
    resetValues(op1);
    op1Count = 0;
    op1DecimalPosition = 0;
    op1Signal = Signal::POSITIVE;
    return;
  }
  resetValues(op2);
  op2Count = 0;
  op2DecimalPosition = 0;
  op2Signal = Signal::POSITIVE;
  pontoUsado = false;
}

void ChristoferCpu::reset()
{
  clearAllValues();
  halt = false;
  pontoUsado = false;
  display->clear();
  display->clear();
  display->clear();
  display->clear();
}

void ChristoferCpu::receiveDigit(Digit digit)
{
  if (halt)
    return;
  if (operation == NONE)
  {
    if (digit == ZERO && op1Count == 0)
      return;
    if (op1Count < 8)
    {
      op1[op1Count] = digit;
      op1Count++;
    }
    else
      return;
  }
  else
  {
    if (digit == ZERO && op2Count == 0)
      return;
    if (op2Count < 8)
    {
      op2[op2Count] = digit;
      op2Count++;
    }
    else
      return;
  }
  // std::cout << "Estamos aqui" << this->display;

  this->display ? this->display->add(digit) : void();
}

void ChristoferCpu::receiveOperation(Operation operation)
{
  if (halt)
    return;
  if (op1DecimalPosition == 0)
  {
    op1DecimalPosition = op1Count;
  }
  if (op2Count != 0)
  {
    calculate(false, this->operation);
  }
  if (operation == Operation::SQUARE_ROOT || operation == Operation::PERCENTAGE)
  {
    calculate(false, operation);
    return;
  }
  this->operation = operation;
  pontoUsado = false;
  display->clear();
}

void ChristoferCpu::receiveControl(Control control)
{
  switch (control)
  {
  case EQUAL:
    if (halt)
      return;
    if (op2DecimalPosition == 0)
    {
      op2DecimalPosition = op2Count;
    }
    calculate(false, this->operation);
    pontoUsado = false;
    display->clear();
    break;
  case CLEAR:
    if (halt)
      return;
    clearValue();
    break;
  case RESET:
    reset();
    break;
  case DECIMAL_SEPARATOR:
    if (pontoUsado)
      setDecimalPosition();
    pontoUsado = true;
    display->setDecimalSeparator();
    break;
  case MEMORY_ADDITION:
    addMemory();
    break;
  case MEMORY_SUBTRACTION:
    subtractMemory();
    break;
  case MEMORY_READ_CLEAR:
    memoryRecall();
    memoryToRegister();
    break;

  default:
    // std::cout << "default";
    break;
  }
}