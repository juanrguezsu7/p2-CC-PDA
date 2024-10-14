/**
 * @file PDAStack.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent the stack of a PDA.
 * @date 12/10/2024
 */

#include "PDAStack.hpp"

/**
 * @brief Constructs a new PDAStack object.
 * 
 * @param INNER_ALPHABET Alphabet of the stack symbols.
 * @param INITIAL_SYMBOL Initial symbol of the stack.
 */
PDAStack::PDAStack(const Alphabet& INNER_ALPHABET, const Symbol& INITIAL_SYMBOL) : innerAlphabet(INNER_ALPHABET) {
  Push(INITIAL_SYMBOL);
}

/**
 * @brief Pushes a symbol to the stack.
 * 
 * @param SYMBOL Symbol to push.
 * @throw std::invalid_argument If the symbol is not in the stack alphabet.
 */
void PDAStack::Push(const Symbol& SYMBOL) {
  if (SYMBOL == Symbol::EPSILON) {
    return;
  }
  if (innerAlphabet.find(SYMBOL) == innerAlphabet.end()) {
    const std::string ALPHABET_STR{std::accumulate(innerAlphabet.begin(), innerAlphabet.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; })};
    throw std::invalid_argument{"Reading file error: Stack symbol: '" + SYMBOL.ToString() + "' not found in stack alphabet ( " + ALPHABET_STR + ")"};
  }
  stack.push(SYMBOL);
}

/**
 * @brief Pushes a vector of symbols to the stack.
 * 
 * @param SYMBOLS Symbols to push.
 */
void PDAStack::Push(const std::vector<Symbol>& SYMBOLS) {
  std::vector<Symbol> reversedSymbols{SYMBOLS};
  std::reverse(reversedSymbols.begin(), reversedSymbols.end());
  for (const Symbol& SYMBOL : reversedSymbols) {
    Push(SYMBOL);
  }
}

/**
 * @brief Pops a symbol from the stack and returns it.
 * 
 * @return The symbol popped.
 */
Symbol PDAStack::Pop() {
  const Symbol SYMBOL{stack.top()};
  stack.pop();
  return SYMBOL;
}

/**
 * @brief Checks if the stack is empty.
 * 
 * @return true If the stack is empty.
 * @return false If the stack is not empty.
 */
bool PDAStack::IsEmpty() const {
  return stack.empty();
}

/**
 * @brief Returns a string representation of the stack.
 * 
 * @return The string representation of the stack.
 */
std::string PDAStack::ToString() const {
  std::string result;
  std::stack<Symbol> tempStack{stack};
  while (!tempStack.empty()) {
    result += tempStack.top().ToString();
    tempStack.pop();
  }
  return result;
}
