#include	<iostream>
#include	<sstream>
#include	<ios>
#include	"Chipset.hh"

Chipset::Chipset(IO *t):
  io(t)
{
}

Chipset::~Chipset()
{
}

std::vector<std::string>	*Chipset::get()
{
  std::string		tmp_line;

  while ((tmp_line = this->io->get()) != "EOF")
    {
      size_t pos = tmp_line.find(";");

      if (pos != std::string::npos)
	tmp_line = tmp_line.substr(0, pos);

      std::stringstream		line(tmp_line);
      std::string		buff;
      std::vector<std::string>	*res = new std::vector<std::string>;

      while (line >> buff)
	res->push_back(buff);
      if (res->size())
	return (res);
      else
	delete res;
    }
  return (0);
}

void	Chipset::send(const std::string str)
{
  if (str.size() > 0)
    this->io->send(str);
}
