#include	<iostream>
#include	"CPU.hh"

static	const std::string	operand_syntax[5] =
  {
    "int8",
    "int16",
    "int32",
    "float",
    "double"
  };

static	const eTokenValue	operand_value[5] =
  {
    INTEGER,
    INTEGER,
    INTEGER,
    FLOAT,
    FLOAT
  };

CPU::CPU(Chipset *c, Memory *m):
  chipset(c), memory(m), finished(false)
{
  this->action["add"] = &CPU::add;
  this->action["sub"] = &CPU::sub;
  this->action["mod"] = &CPU::mod;
  this->action["div"] = &CPU::div;
  this->action["mul"] = &CPU::mul;
  this->action["push"] = &CPU::push;
  this->action["pop"] = &CPU::pop;
  this->action["dump"] = &CPU::dump;
  this->action["exit"] = &CPU::exit;
  this->action["assert"] = &CPU::assert;
}

  CPU::~CPU()
{
  if (!finished)
    std::cout << "ERROR" << std::endl;
}


Chipset	*CPU::getChipset()	const
{
  return (this->chipset);
}

Memory	*CPU::getMemory()	const
{
  return (this->memory);
}

void		CPU::setChipset(Chipset *c)
{
  this->chipset = c;
}

void		CPU::setMemory(Memory *m)
{
  this->memory = m;
}


bool	CPU::exec()
{
  std::vector<std::string>	*frame;
  frame = this->chipset->get();
  if (frame && !frame->empty())
    {
      std::string	f_action = frame->at(0);
      std::map<std::string, t_ptrCPU>::iterator it = this->action.find(f_action);
      if (it != this->action.end())
	{
	  frame->erase(frame->begin());
	  std::string	res = (this->*(*it).second)(*frame);
	  if (res != "")
	    {
	      if (res == "SAM EXIT")
		this->finished = true;
	      else
		this->chipset->send(res);
	    }
	  return (true);
	}
      else
	{
	  std::string	error("Unknown instruction ");
	  throw CPU::UnknownInstruction(error + f_action, __LINE__ );
	}
    }
  return (false);
}

bool	CPU::checkParam(std::vector<std::string> &elms, unsigned int needed)
{
  return (elms.size() == needed);
}

eOperandType	CPU::getOperandType(std::string &str)
{
  unsigned int pos;

  for (pos = 0; pos < str.size() && str[pos] != '('; ++pos);
  std::string	ope = str.substr(0, pos);
  for (unsigned int i = 0; i < NBR_OPERAND; ++i)
    if (ope == operand_syntax[i])
      return (static_cast<eOperandType>(i));
  std::string	error("Unknown operand type ");
  throw CPU::UnknownOperandType(error + ope, __LINE__);
}

std::string	CPU::getOperandValue(std::string &str)
{
  unsigned int pos = 0;

  for (pos = 0; pos < str.size() && str[pos] != '('; ++pos);
  if (str.size() && str[pos] == '(')
    {
      str = str.substr(pos + 1);
      for (unsigned int i = 1; i < str.size(); ++i)
	if (str[i] == ')')
	  return (str.substr(0, i));
    }
  throw CPU::SyntaxError("Syntax error, missing character '('", __LINE__);
}

eTokenValue	CPU::getValueType(const std::string &value) const
{
  if (value.find(".") == std::string::npos)
    return (INTEGER);
  else if (value.find(".") == value.rfind("."))
    return (FLOAT);
  else
    return (UNKNOW);
}

bool	CPU::well_typed(eOperandType op, const std::string &value) const
{
  return (operand_value[op] == this->getValueType(value));
}

void		CPU::checkPrecision()
{
  this->registers[2] = this->registers[0];
  this->registers[3] = this->registers[1];
  if (this->registers[0]->getType() < this->registers[1]->getType())
    this->registers[2] = this->memory->createOperand(this->registers[1]->getType(),
						     this->registers[0]->toString());
  else if (this->registers[1]->getType() < this->registers[0]->getType())
    this->registers[3] = this->memory->createOperand(this->registers[0]->getType(),
						     this->registers[1]->toString());
}

std::string	CPU::add(std::vector<std::string> &frame)
{
  if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->checkPrecision();
      this->memory->push(*this->registers[2] + this->registers[3]);
    }
  else
    throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
  return (std::string(""));
}

std::string	CPU::div(std::vector<std::string> &frame)
{
  if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      //exeption divition par zero;
      this->checkPrecision();
      this->memory->push(*this->registers[2] / this->registers[3]);
    }
  else
    throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}

std::string	CPU::sub(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->checkPrecision();
      this->memory->push(*this->registers[2] - this->registers[3]);
    }
 else
   throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}

std::string	CPU::mod(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->checkPrecision();
      //exeption divition par zero;
      this->memory->push(*this->registers[2] % this->registers[3]);
    }
 else
   throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}

std::string	CPU::mul(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->checkPrecision();
      this->memory->push(*this->registers[2] * this->registers[3]);
    }
 else
   throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}

std::string	CPU::push(std::vector<std::string> &frame)
{
 if (checkParam(frame, 1))
    {
      eOperandType	type = this->getOperandType(frame[0]);
      std::string	value = this->getOperandValue(frame[0]);
      if (well_typed(type, value))
	{
	  this->registers[0] = this->memory->createOperand(type, value);
	  this->memory->push(this->registers[0]);
	}
      else
	{
	  std::string	error("Syntax error, bad type for ");
	  throw CPU::SyntaxError(error + value, __LINE__);
	}
    }
 else
   throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}
std::string	CPU::pop(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
   this->memory->pop();
  else
   throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
 return (std::string(""));
}
std::string	CPU::dump(std::vector<std::string> &frame)
{
  if (checkParam(frame, 0))
    return (this->memory->dump());
  else
    throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
  return (std::string(""));
}
std::string	CPU::exit(std::vector<std::string> &)
{
  return (std::string("SAM EXIT"));
}

std::string	CPU::assert(std::vector<std::string> &frame)
{
  if (checkParam(frame, 1))
    {
      eOperandType	type = this->getOperandType(frame[0]);
      std::string	value = this->getOperandValue(frame[0]);

      if (well_typed(type, value))
	{
	  this->registers[0] = this->memory->pop();
	  this->memory->push(this->registers[0]);
	  if (this->registers[0]->toString() != value)
	    throw AssertFaillure("Instruction \"assert\" fail", __LINE__);  
	}
      else
	{
	  std::string	error("Syntax error, bad type for ");
	  throw CPU::SyntaxError(error + value, __LINE__);
	}
    }
  else
    throw CPU::SyntaxError("Syntax error, not enough parameters", __LINE__);
  return (std::string(""));
}

UnknownInstruction::~UnknownInstruction()
{

}
