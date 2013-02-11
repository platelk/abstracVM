
#include	<iostream>
#include	<fstream>
#include	"Chipset.hh"

int	main()
{
  /*
  std::filebuf	f;

  f.open("plop.txt", std::ios::in);
  std::istream	in(&f);
  Chipset	c(in, std::cout);
  */
  Chipset	c(std::cin, std::cout);
  //switch for test standard input
  while (!c.is_empty())
    {
      std::vector<std::string>	*p = c.get();
      std::string		o("");
      if (p)
	{
	  for (std::vector<std::string>::iterator it = p->begin(); it != p->end(); ++it)
	    o += *it + " | " ;
	  c.send(o);
	  std::cout << std::endl;
	}
    }
}
