//
// main.cpp for /home/vink/projet/cpp/abstract/src/main.cpp in /home/vink
//
// Made by vink
// Login   <kevin platel@epitech.net>
//
// Started on  Tue Feb 12 10:57:51 2013 vink
// Last update Tue Feb 12 13:17:42 2013 vink
//

#include <iostream>
#include "IOperand.hh"
#include "Memory.hh"

int main()
{
  Memory	a;
  a.push(a.createOperand(Int32, "259"));
  a.push(a.createOperand(Double, "16.5"));
  a.push(a.createOperand(Float, "16.9"));
  a.push(a.createOperand(Int16, "16"));
  a.push(a.createOperand(Int8, "16"));
  a.dump();
  return 0;
}
