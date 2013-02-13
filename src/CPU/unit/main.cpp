
#include	<iostream>
#include	<fstream>
#include	"CPU.hh"
#include	"Chipset.hh"
#include	"IOperand.hh"
#include	"Memory.hh"

int	main()
{
  std::filebuf	f;

  f.open("plop.txt", std::ios::in);
  std::istream	in(&f);
  Chipset	c(in, std::cout);
  Memory	m;

  CPU	mine(&c, &m);
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  mine.exec();
  std::cout << " fin" << std::endl;
  return (0);
}
