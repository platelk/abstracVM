
#ifndef		__CPUEXCEPTION_H__
# define	__CPUEXCEPTION_H__

class	CPUException: public	std::exception
{
  std::string         msg;
public:
  CPUException(const std::string &, int line);
  virtual ~CPUException() throw() {}
  virtual const char  *what() const throw();
};

class	MemoryException: public	std::exception
{
  std::string         msg;
public:
  MemoryException(const std::string &, int line);
  virtual ~MemoryException() throw() {}
  virtual const char  *what() const throw();
};

class	OperandException: public	std::exception
{
  std::string         msg;
public:
  OperandException(const std::string &, int line);
  virtual ~OperandException() throw() {}
  virtual const char  *what() const throw();
};

#endif
