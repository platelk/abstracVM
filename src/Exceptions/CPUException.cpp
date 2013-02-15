
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
