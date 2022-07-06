#include "calculator.h"
#include "display.h"
#include <iostream>

void ChristoferDisplay::setError()
{
  std::cout << 'E';
}

void ChristoferDisplay::add(Digit digit)
{
  switch (digit)
  {
  case ZERO:
    std::cout << 0;
    break;
  case ONE:
    std::cout << 1;
    break;
  case TWO:
    std::cout << 2;
    break;
  case THREE:
    std::cout << 3;
    break;
  case FOUR:
    std::cout << 4;
    break;
  case FIVE:
    std::cout << 5;
    break;
  case SIX:
    std::cout << 6;
    break;
  case SEVEN:
    std::cout << 7;
    break;
  case EIGHT:
    std::cout << 8;
    break;
  case NINE:
    std::cout << 9;
    break;
  default:
  setError();
    //std::cout << 'E';
  }
}

void ChristoferDisplay::setSignal(Signal signal)
{
  if (signal == Signal::NEGATIVE)
  {
    std::cout << "-";
  }
}

void ChristoferDisplay::setDecimalSeparator()
{
  std::cout << ".";
}

/*void ChristoferDisplay::proximaLinha()
{
  std::cout << std::endl;
}*/
void ChristoferDisplay::clear()
{
  std::cout << std::endl;
}