
#ifndef		__CPU__
# define	__CPU__

#include	<map>
#include	<vector>
#include	<string>
#include	"Chipset.hh"
#include	"IOperand.hh"
#include	"Memory.hh"

#define		NBR_OPERAND	5

class	CPU;

typedef	std::string (CPU::*t_ptrCPU)(std::vector<std::string> &);

enum	eTokenValue
  {
    INTEGER,
    FLOAT,
    UNKNOW
  };

class	CPU
{
  std::map<std::string, t_ptrCPU>					action;
  Chipset								*chipset;
  Memory								*memory;
  IOperand								*registers[4];
  bool									finished;
public:
  
  class		UnknownInstruction:	public	CPUException
  {
  public:
    virtual ~UnknownInstruction();
  };
  class		UnknownOperandType:	public	CPUException {};
  class		MissingExit:		public	CPUException {};
  class		AssertFaillure:		public	CPUException {};
  class		SyntaxError:		public	CPUException {};

  CPU(Chipset *, Memory *);
  ~CPU();
  CPU(const CPU&);
  CPU &operator=(const CPU &);

  bool		exec();

  bool		checkParam(std::vector<std::string> &, unsigned int);

  std::string	add(std::vector<std::string> &);
  std::string	div(std::vector<std::string> &);
  std::string	sub(std::vector<std::string> &);
  std::string	mod(std::vector<std::string> &);
  std::string	mul(std::vector<std::string> &);

  std::string	push(std::vector<std::string> &);
  std::string	pop(std::vector<std::string> &);
  std::string	dump(std::vector<std::string> &);
  std::string	exit(std::vector<std::string> &);
  std::string	assert(std::vector<std::string> &);

  void		checkPrecision();

  Chipset	*getChipset()	const;
  Memory	*getMemory()	const;

  void		setChipset(Chipset *);
  void		setMemory(Memory *);

private:
  eOperandType	getOperandType(std::string &str);
  std::string	getOperandValue(std::string &);
  bool		well_typed(eOperandType, const std::string &) const;
  eTokenValue	getValueType(const std::string &) const;
};

#endif
