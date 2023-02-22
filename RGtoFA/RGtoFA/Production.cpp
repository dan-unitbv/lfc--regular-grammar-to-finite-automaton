#include "Production.h"

std::string Production::getU() const
{
    return u;
}
std::string Production::getV() const
{
    return v;
}

std::istream& operator>>(std::istream& in, Production& production)
{
    in >> production.u >> production.v;
    return in;
}
std::ostream& operator<<(std::ostream& os, Production& production)
{
    os << production.u << "->" << production.v;
    return os;
}