
#include	"MotherBoard.hh"

MotherBoard::MotherBoard(Chipset *c, Memory *m, CPU *u):
  chipset(c), cpu(u), memory(m)
{
}

MotherBoard::~MotherBoard()
{
}

void	MotherBoard::setChipset(Chipset *c)
{
  this->chipset = c;
  if (this->cpu)
    this->cpu->setChipset(c);
}
void	MotherBoard::setCPU(CPU *u)
{
  this->cpu = u;
}
void	MotherBoard::setMemory(Memory *m)
{
  this->memory = m;
  if (this->memory)
    this->memory = m;
}

Chipset	*MotherBoard::getChipset()	const
{
  return (this->chipset);
}
Memory	*MotherBoard::getMemory()	const
{
  return (this->memory);
}
CPU	*MotherBoard::getCPU()	const
{
  return (this->cpu);
}

void	MotherBoard::boot()
{
  while (this->cpu->exec());
  if (!this->cpu->is_finished())
    throw CPU::MissingExit("missing exit instruction", __LINE__ );
}
