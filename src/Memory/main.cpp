//
// main.cpp for /home/vink/projet/cpp/abstract/src/main.cpp in /home/vink
//
// Made by vink
// Login   <kevin platel@epitech.net>
//
// Started on  Tue Feb 12 10:57:51 2013 vink
// Last update Tue Feb 12 21:36:59 2013 vink
//

#include <iostream>
#include "IOperand.hh"
#include "Memory.hh"

int main()
{
  Memory	a;
  IOperand*	b;
  IOperand*	c;

  a.push(a.createOperand(Int32, "259"));
  a.push(a.createOperand(Double, "16.5"));
  a.push(a.createOperand(Float, "16.9"));
  a.push(a.createOperand(Int8, "0"));
  a.push(a.createOperand(Int8, "120"));
  std::cout << a.dump();
  std::cout << "=========" << std::endl;
  b = a.pop();
  c = a.pop();
  std::cout << a.dump();
  std::cout << "=========" << std::endl;
  std::cout << b->toString() << std::endl;
  std::cout << c->toString() << std::endl;
  std::cout << (*b - c)->toString() << std::endl;
  return 0;
}
