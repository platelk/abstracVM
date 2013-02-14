
#ifndef		__CHIPSET_HH__
# define	__CHIPSET_HH__

#include	"IO.hh"
#include	<string>
#include	<vector>

class	Chipset
{
  IO		*io;
public:
  Chipset(IO *t);
  ~Chipset();
  Chipset(const Chipset &);
  Chipset	&operator=(const Chipset &);

  std::vector<std::string>	*get();
  void				send(const std::string);
  
};

#endif
