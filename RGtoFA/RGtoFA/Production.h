#pragma once
#include <iostream>
#include <string>
class Production {
private:
    std::string u;
    std::string v;
public:
    Production() = default;
    ~Production() = default;

    std::string getU() const;
    std::string getV() const;

    friend std::istream& operator>>(std::istream& in, Production& production);
    friend std::ostream& operator<<(std::ostream& os, Production& production);
};