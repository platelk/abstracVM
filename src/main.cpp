
#include	<fstream>
#include	"CPU.hh"
#include	"Memory.hh"
#include	"Chipset.hh"
#include	"MotherBoard.hh"

int	main(int argc, char **argv)
{
  if (argc > 1)
    {
      std::filebuf	f;
      f.open(argv[1], std::ios::in);
      std::istream	inp(&f);
      IO		i(inp, std::cout);
      Chipset		c(&i);
      Memory		m;
      CPU		u(&c, &m);
      MotherBoard	mother(&c, &m, &u);
      mother.boot();
    }
  // else
  //   IO	i(std::cin, std::cout);


  return (0);
}
