
#include	"CPU.hh"

CPU::CPU(Chipset *c):
  chipset(c)
{
  action["add"] = &CPU::add;
  action["sub"] = &CPU::sub;
  action["mod"] = &CPU::mod;
  action["div"] = &CPU::div;
  action["mul"] = &CPU::mul;
  action["push"] = &CPU::push;
  action["pop"] = &CPU::pop;
  action["dump"] = &CPU::dump;
  action["exit"] = &CPU::exit;
  action["assert"] = &CPU::assert;
}

CPU::~CPU()
{
}

std::string	CPU::exec(std::vector<std::string> &frame)
{
}
