//
// Memory.cpp for /home/vink/projet/cpp/abstract/src/Memory.cpp in /home/vink
//
// Made by vink
// Login   <kevin platel@epitech.net>
//
// Started on  Tue Feb 12 10:24:50 2013 vink
// Last update Fri Feb 22 17:30:47 2013 vink
//

#include <iostream>
#include <algorithm>
#include "Memory.hh"
#include "Operand.hpp"

void	print(IOperand *a)
{
  std::cout << a->toString() << std::endl;
}

Memory::Memory()
{
  this->create[Int8] = &Memory::createInt8;
  this->create[Int16] = &Memory::createInt16;
  this->create[Int32] = &Memory::createInt32;
  this->create[Float] = &Memory::createFloat;
  this->create[Double] = &Memory::createDouble;
}

Memory::~Memory()
{
  while (!this->mem.empty())
    {
      if (this->mem.front())
	delete this->mem.front();
      this->mem.pop_front();
    }
}

std::string &	Memory::dump()
{
  int	i = 0;
  while (i < this->mem.size())
    {
      this->_dump += this->mem[i]->toString() + "\n";
      i++;
    }
  return (this->_dump);
}

void		Memory::operator()(IOperand *a)
{
  this->_dump += (a->toString() + "\n");
}

IOperand*	Memory::get() const
{
  return (this->mem[0]);
}

IOperand*	Memory::pop()
{
  IOperand*	tmp;

  if (this->mem.empty())
    throw Memory::EmptyStack("invalid pop on a empty stack.", __LINE__);
  tmp = this->mem.front();
  this->mem.pop_front();
  return (tmp);
}

void		Memory::push(IOperand *a)
{
  if (a == 0)
    throw Memory::InvalidPush("invalid value push.", __LINE__);
  this->mem.push_front(a);
}

IOperand*	Memory::createOperand(eOperandType type, std::string const & value)
{
  return ((this->*(this->create[type]))(value));
}

IOperand*	Memory::createDouble(const std::string &value)
{
  return (new Operand<double>(Double, value));
}

IOperand*	Memory::createFloat(const std::string &value)
{
  return (new Operand<float>(Float, value));
}

IOperand*	Memory::createInt32(const std::string &value)
{
  return (new Operand<int>(Int32, value));
}

IOperand*	Memory::createInt16(const std::string &value)
{
  return (new Operand<short>(Int16, value));
}

IOperand*	Memory::createInt8(const std::string &value)
{
  return (new Operand<char>(Int8, value));
}
