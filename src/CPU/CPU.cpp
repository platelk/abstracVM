
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
  chipset(c), memory(m)
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
}

std::string	CPU::exec()
{
  std::vector<std::string>	*frame;
  while ((frame = this->chipset->get()) != 0)
    {
      if (!frame->empty())
	{
	  std::string	f_action = frame->at(0);
	  std::map<std::string, t_ptrCPU>::iterator it = this->action.find(f_action);
	  if (it != this->action.end())
	    {
	      frame->erase(frame->begin());
	      std::string	res = (this->*(*it).second)(*frame);
	      if (res != "")
		this->chipset->send(res);
	    }
	}
    }
}

bool	CPU::checkParam(std::vector<std::string> &elms, int needed)
{
  return (elms.size() == needed);
}

eOperandType	CPU::getOperandType(std::string &str)
{
  unsigned int pos;

  for (pos = 0; pos < str.size() && str[pos] != ')'; ++pos);
  std::string	ope = str.substr(0, pos);
  for (unsigned int i = 0; i < NBR_OPERAND; ++i)
    if (ope == operand_syntax[i])
      return (static_cast<eOperandType>(i));
  //exeption unknow operand type
}

std::string	CPU::getOperandValue(std::string &str)
{
  if (str.size() && str[0] == '(')
    {
      str = str.substr(0, 1);
      for (unsigned int i = 1; i < str.size(); ++i)
	if (str[0] == ')')
	  return (str.substr(0, i));
    }
  //exeption erreur de syntaxe;
}

eTokenValue	CPU::getValueType(const std::string &value) const
{
  if (value.find(".") != std::string::npos)
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

std::string	CPU::add(std::vector<std::string> &frame)
{
  if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->memory->push(*this->registers[0] + this->registers[1]);
    }
  //exeption pass assez d'argument
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
      this->memory->push(*this->registers[0] / this->registers[1]);
    }
  //exeption pass assez d'argument
 return (std::string(""));
}

std::string	CPU::sub(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->memory->push(*this->registers[0] - this->registers[1]);
    }
  //exeption pass assez d'argument
 return (std::string(""));
}

std::string	CPU::mod(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      //exeption divition par zero;
      this->memory->push(*this->registers[0] % this->registers[1]);
    }
 //exeption pass assez d'argument
 return (std::string(""));
}

std::string	CPU::mul(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
    {
      //exeption rien sur la pile
      this->registers[0] = this->memory->pop();
      this->registers[1] = this->memory->pop();
      this->memory->push(*this->registers[0] * this->registers[1]);
    }
 //exeption pass assez d'argument
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
      //exeption bad type;
    }
 //exeption pas assez d'argument
 return (std::string(""));
}
std::string	CPU::pop(std::vector<std::string> &frame)
{
 if (checkParam(frame, 0))
   this->memory->pop();
 return (std::string(""));
 //exeption pas assez d'argument
}
std::string	CPU::dump(std::vector<std::string> &frame)
{
  if (checkParam(frame, 0))
    return (this->memory->dump());
  return (std::string(""));
 //exeption pas assez d'argument
}
std::string	CPU::exit(std::vector<std::string> &frame)
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
	  //if (this->registers[0]->toString() != value)
	    //exeption
	}
      //exeption bad type;
    }
  //exeption pas assez d'argument
  return (std::string(""));
}
