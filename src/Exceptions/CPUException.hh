
#ifndef		__CPUEXCEPTION_H__
# define	__CPUEXCEPTION_H__

class	CPUException: public	std::exception
{
  std::string         msg;
public:
  CPUException(const std::string &, int line);
  virtual ~CPUException();
  virtual const char  *what() const throw();
};

#endif
