#include "symbol.hpp"

const Symbol Symbol::EPSILON = Symbol{'.'};

Symbol::Symbol(const char VALUE) : value(VALUE) {}

std::vector<Symbol> Symbol::ToSymbols(const std::string& INPUT_STR) {
  std::vector<Symbol> symbols;
  for (char c : INPUT_STR) {
    symbols.emplace_back(Symbol{c});
  }
  return symbols;
}
    
bool Symbol::operator ==(const Symbol& OTHER) const {
  return value == OTHER.value;
}

bool Symbol::operator !=(const Symbol& OTHER) const {
  return value != OTHER.value;
}

bool Symbol::operator <(const Symbol& OTHER) const {
  return value < OTHER.value;
}

std::string Symbol::ToString() const {
  return std::string{value};
}