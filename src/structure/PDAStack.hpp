/**
 * @file PDAStack.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent the stack of a PDA.
 * @date 12/10/2024
 */

#pragma once

#include <stack>
#include <stdexcept>
#include <set>
#include <numeric>

#include "symbol.hpp"

/**
 * @brief Type to represent the alphabet of the stack of a PDA.
 */
using Alphabet = std::set<Symbol>;

/**
 * @brief Class to represent the stack of a PDA. The stack is a LIFO structure which contains symbols from a stack alphabet.
 */
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
