#ifndef __OPERAND_H__
# define __OPERAND_H__

#include <sstream>
#include <limits>
#include "IOperand.hh"
#include "Memory.hh"

template<class T>
class Operand : public IOperand
{
private:
  eOperandType	_type;
  const T		_value;


  T		getValueOfType(std::string const & string_value) const
  {
    std::stringstream	ss;
    T tmp;

    ss << string_value;
    ss >> tmp;

    return (tmp);
  }
public:
  class Overflow : public OperandException
  {
  public:
    Overflow(const std::string &msg, int line)
      : OperandException(msg, line)
    {}
    virtual ~Overflow() throw() {}
  };
  class Underflow : public OperandException
  {
  public:
    Underflow(const std::string &msg, int line)
      : OperandException(msg, line)
    {}
    virtual ~Underflow() throw() {}
  };
  class DivideByZero : public OperandException
  {
  public:
    DivideByZero(const std::string &msg, int line)
      : OperandException(msg, line)
    {}
    virtual ~DivideByZero() throw() {}
  };

  class InvalidOperation : public OperandException
  {
  public:
    InvalidOperation(const std::string &msg, int line)
      : OperandException(msg, line)
    {}
    virtual ~InvalidOperation() throw(){}
  };

  Operand(eOperandType type, T const value)
    : _type(type), _value(value)
  {
  }
  Operand(eOperandType type, std::string const & value)
    : _type(type), _value(this->getValueOfType(value))
  {
  }
  virtual ~Operand() {}

  int		getPrecision() const
  {
    return (this->_type);
  }

  eOperandType	getType() const
  {
    return (this->_type);
  }

  std::string	toString() const
  {
    std::stringstream ss;

    ss << this->_value;
    return (ss.str());
  }

  IOperand*	operator+(const IOperand &op) const
  {
    T op_value;

    op_value = this->getValueOfType((op.toString()));
    if ((op_value > 0) && (this->_value > (std::numeric_limits<T>::max()) - op_value))
      throw Operand::Overflow("overflow operation.", __LINE__);
    if ((op_value < 0) && (this->_value < (std::numeric_limits<T>::min()) - op_value))
      throw Operand::Overflow("underflow operation.", __LINE__);
    return (new Operand<T>(this->_type, this->_value + op_value));
  }

  IOperand*	operator-(const IOperand &op) const
  {
    T op_value;

    op_value = this->getValueOfType(op.toString());
    if ((op_value < 0) && (this->_value < (std::numeric_limits<T>::max()) - op_value))
      throw Operand::Overflow("overflow operation.", __LINE__);
    if ((op_value > 0) && (this->_value > (std::numeric_limits<T>::min()) - op_value))
      throw Operand::Overflow("underflow operation.", __LINE__);
    return (new Operand<T>(this->_type, this->_value - op_value));
  }

  IOperand*	operator*(const IOperand &op) const
  {
    T op_value;

    op_value = this->getValueOfType(op.toString());
    if ((std::numeric_limits<T>::max() / (this->_value < 0 ? (this->_value * -1) : this->_value)) < (op_value < 0 ? (op_value * -1) : op_value))
      throw Operand::Overflow("overflow operation.", __LINE__);
    return (new Operand<T>(this->_type, this->_value * op_value));
  }

  IOperand*	operator/(const IOperand &op) const
  {
    T op_value;

    op_value = this->getValueOfType(op.toString());
    if (op_value == 0)
      throw Operand::DivideByZero("divide by zero", __LINE__);
    return (new Operand<T>(this->_type, this->_value / op_value));
  }

  IOperand*	operator%(const IOperand &op) const;

};


template<typename T>
IOperand*	Operand<T>::operator%(const IOperand &op) const
{
  T op_value;

  op_value = this->getValueOfType(op.toString());
  if (op_value == 0)
    throw Operand::DivideByZero("divide by zero", __LINE__);
  return (new Operand<T>(this->_type, this->_value % op_value));
}


template<>
IOperand*	Operand<double>::operator%(const IOperand &) const
{
  throw Operand::InvalidOperation("invalid modulo operation on double", __LINE__);
}

template<>
IOperand*	Operand<float>::operator%(const IOperand &) const
{
  throw Operand::InvalidOperation("invalid modulo operation on float", __LINE__);
}

template<>
char		Operand<char>::getValueOfType(std::string const & string_value) const
{
  std::stringstream	ss;
  int tmp;

  ss << string_value;
  ss >> tmp;

  return (static_cast<char>(tmp));
}

template<>
std::string	Operand<char>::toString() const
{
  std::stringstream ss;

  ss << static_cast<int>(this->_value);
  return (ss.str());
}

#endif /* !__OPERAND_H__ */
