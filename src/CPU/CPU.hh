
#ifndef		__CPU__
# define	__CPU__

#include	<map>
#include	<vector>
#include	<string>
#include	"Chipset.hh"
//#include	"IOperand.hh"
//#include	"Memory.hh"

class	CPU
{
  std::map<std::string, void CPU::*ptr(std::vector<std::string>)>	action;
  Chipset								*chipset;
  //  Memory								*memory;
  //IOperand								*registers;
public:
  //  CPU(Memory *, Chipset *);
  //tmp
  CPU(Chipset *);
  //
  ~CPU();
  CPU(const CPU&);
  CPU &operator=(const CPU &);

  std::string	exec(std::vector<std::string> &);

  bool		checkParam(std::vector<std::string> &, int);

  std::string	add(std::vector<std::string> &);
  std::string	div(std::vector<std::string> &);
  std::string	sub(std::vector<std::string> &);
  std::string	mod(std::vector<std::string> &);
  std::string	mul(std::vector<std::string> &);

  std::string	push(std::vector<std::string> &);
  std::string	pop(std::vector<std::string> &);
  std::string	dump(std::vector<std::string> &);
  std::string	exit(std::vector<std::string> &);

  
};

#endif
