#pragma once

#include <stack>
#include <stdexcept>
#include <set>
#include <numeric>

#include "symbol.hpp"

using Alphabet = std::set<Symbol>;

class PDAStack {
  public:
    PDAStack(const Alphabet&, const Symbol&);
    void Push(const Symbol&);
    Symbol Pop();
    bool IsEmpty() const;
    std::string ToString() const;
  private:
    const Alphabet innerAlphabet;
    std::stack<Symbol> stack;
};