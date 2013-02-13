#include	<sstream>
#include	<ios>
#include	"Chipset.hh"

Chipset::Chipset(std::istream &in, std::ostream &out):
  input(in), output(out)
{
}

Chipset::~Chipset()
{
}

std::vector<std::string>	*Chipset::get()
{
  std::string		tmp_line;
  
  if (getline(this->input, tmp_line))
    {
      size_t pos = tmp_line.find(";");

      if (pos != std::string::npos)
	tmp_line = tmp_line.substr(0, pos);
      
      std::stringstream		line(tmp_line);
      std::string		buff;
      std::vector<std::string>	*res = new std::vector<std::string>;
  
      while (line >> buff)
	res->push_back(buff);
      
      return (res);
    }
  return (0);
}

void	Chipset::send(const std::string str)
{
  this->output << str;
}

bool	Chipset::is_empty()	const
{
  return (!this->input.good());
}
