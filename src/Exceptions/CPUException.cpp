
#include	"AException.hh"

CPUException::CPUException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[CPU] Error line " << line << " : " << m;
  this->msg = o.str();
}
CPUException::~CPUException()
{
  //delete registers?
}
const char      *CPUException::what() const throw()
{
  return (this->msg.c_str());
}

MemoryException::MemoryException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[Memory] Error line " << line << " : " << m;
  this->msg = o.str();
}
MemoryException::~MemoryException()
{
  //delete registers?
}
const char      *MemoryException::what() const throw()
{
  return (this->msg.c_str());
}

OperandException::OperandException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[Operand] Error line " << line << " : " << m;
  this->msg = o.str();
}
OperandException::~OperandException()
{
  //delete registers?
}
const char      *OperandException::what() const throw()
{
  return (this->msg.c_str());
}
