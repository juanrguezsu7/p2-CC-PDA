#pragma once

#include <string>
#include <vector>

class Symbol {
  public:
    const static Symbol EPSILON;
  
    Symbol(const char);
    static std::vector<Symbol> ToSymbols(const std::string&);
    bool operator ==(const Symbol&) const;
    bool operator !=(const Symbol&) const;
    bool operator <(const Symbol&) const;
    std::string ToString() const;
  private: 
    const char value;
};