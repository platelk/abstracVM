#include	<iostream>
#include	<ostream>
#include	<istream>
#include	<fstream>
#include	<sstream>
#include	"IO.hh"

IO::IO(std::istream &i, std::ostream &o):
  input(i), output(o), buffer("")
{
  bool	enough = false;
  std::string	end;
  std::string	line;

  while (!enough && getline(this->input, line))
    {
      std::stringstream	is(line);
      if ((is >> end) == ";;")
	enough = true;
      else
	this->buffer << line << std::endl;
    }
}

IO::~IO()
{
}

std::string	IO::get()
{
  std::string	line;

  if (getline(this->buffer, line))
    return (line);
  return ("EOF");
}

void		IO::send(const std::string &str)
{
  
  this->output << str;
  this->output.flush();
}
