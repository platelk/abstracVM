#ifndef __MEMORY_H__
# define __MEMORY_H__

#include <iostream>
#include <deque>
#include <map>

#include "IOperand.hh"

class Memory
{
typedef	IOperand*	(Memory::*ptrFunc)(std::string const &);
private:
  std::deque<IOperand *>	mem;
  std::string			_dump;
  ptrFunc	create[5];
public:
  Memory();
  virtual ~Memory() {};

  std::string &	dump();
  IOperand*	get() const;
  IOperand*	pop();
  void		push(IOperand *a);

  IOperand*	createOperand(eOperandType type, std::string const & value);

  IOperand*	createDouble(std::string const  &);
  IOperand*	createFloat(std::string const  &);
  IOperand*	createInt32(std::string const  &);
  IOperand*	createInt16(std::string const  &);
  IOperand*	createInt8(std::string const  &);

  void		operator()(IOperand *a);
};

#endif /* !__MEMORY_H__ */
