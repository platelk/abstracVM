
#include	<sstream>
#include	"ModExceptions.hh"

CPUException::CPUException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[CPU] Error line " << line << " : " << msg;
  this->msg = o.str();
}
CPUException::~CPUException()	throw()
{}

const char      *CPUException::what() const throw()
{
  return (this->msg.c_str());
}

MemoryException::MemoryException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[Memory] Error line " << line << " : " << msg;
  this->msg = o.str();
}
MemoryException::~MemoryException() throw()
{}
const char      *MemoryException::what() const throw()
{
  return (this->msg.c_str());
}

OperandException::OperandException(const std::string &msg, int line)
{
  std::ostringstream    o;

  o << "[Operand] Error line " << line << " : " << msg;
  this->msg = o.str();
}
OperandException::~OperandException() throw()
{}
const char      *OperandException::what() const throw()
{
  return (this->msg.c_str());
}
