
#include	<istream>
#include	<ostream>
#include	<fstream>
#include	"CPU.hh"
#include	"Memory.hh"
#include	"Chipset.hh"
#include	"MotherBoard.hh"

std::istream *getInput(int argc, char **argv)
{
  if (argc > 1)
    return (new std::ifstream(argv[1]));
  return (&std::cin);
}

std::ostream *getOutput(int argc, char **argv)
{
  if (argc > 2)
    return (new std::ofstream(argv[2]));
  return (&std::cout);
}

int	main(int argc, char **argv)
{
  std::istream	*in = getInput(argc, argv);
  std::ostream	*out = getOutput(argc, argv);
  
  IO		i(*in, *out);
  Chipset	c(&i);
  Memory	m;
  CPU		u(&c, &m);
  MotherBoard	mother(&c, &m, &u);
  mother.boot();
  return (0);
  // penser au try et au poweroff
}
