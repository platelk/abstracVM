
#ifndef		__CHIPSET_HH__
# define	__CHIPSET_HH__

#include	<ostream>
#include	<istream>
#include	<string>
#include	<vector>

class	Chipset
{
  std::istream	&input;
  std::ostream	&output;
public:
  Chipset(std::istream &, std::ostream &);
  ~Chipset();
  Chipset(const Chipset &);
  Chipset	&operator=(const Chipset &);

  bool		is_empty()		const;
  
  std::vector<std::string>	*get();
  void				send(const std::string);
  
};

#endif
