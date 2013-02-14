
#ifndef		__MOTHERBOARD_HH__
# define	__MOTHERBOARD_HH__

#include	"Memory.hh"
#include	"CPU.hh"
#include	"Chipset.hh"

class	MotherBoard
{
  Chipset	*chipset;
  CPU		*cpu;
  Memory	*memory;

public:
  MotherBoard(Chipset *, Memory *, CPU *);
  ~MotherBoard();
  MotherBoard(const MotherBoard &);
  MotherBoard &operator=(const MotherBoard &);
  
  void	setChipset(Chipset *);
  void	setCPU(CPU *);
  void	setMemory(Memory *);

  Chipset	*getChipset()	const;
  Memory	*getMemory()	const;
  CPU		*getCPU()	const;

  void	boot();
};

#endif
