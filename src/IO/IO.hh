
#ifndef		__IO_HH__
# define	__IO_HH__

#include	<sstream>
#include	<istream>
#include	<ostream>

class	IO
{
  std::istream		&input;
  std::ostream		&output;
  std::stringstream	buffer;
public:
  IO(std::istream &, std::ostream &);
  ~IO();
  IO(const IO &);
  IO	&operator=(const IO &);

  std::string	get();
  void		send(const std::string &);
};

#endif
