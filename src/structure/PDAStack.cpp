#include "PDAStack.hpp"

PDAStack::PDAStack(const Alphabet& INNER_ALPHABET, const Symbol& INITIAL_SYMBOL) : innerAlphabet(INNER_ALPHABET) {
  Push(INITIAL_SYMBOL);
}

void PDAStack::Push(const Symbol& SYMBOL) {
  if (innerAlphabet.find(SYMBOL) == innerAlphabet.end()) {
    const std::string ALPHABET_STR = std::accumulate(innerAlphabet.begin(), innerAlphabet.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; });
    throw std::invalid_argument{"Reading file error: Stack symbol: '" + SYMBOL.ToString() + "' not found in stack alphabet ( " + ALPHABET_STR + ")"};
  }
  stack.push(SYMBOL);
}

Symbol PDAStack::Pop() {
  const Symbol SYMBOL = stack.top();
  stack.pop();
  return SYMBOL;
}

bool PDAStack::IsEmpty() const {
  return stack.empty();
}

std::string PDAStack::ToString() const {
  std::string result;
  std::stack<Symbol> tempStack{stack};
  while (!tempStack.empty()) {
    result += tempStack.top().ToString();
    tempStack.pop();
  }
  return result;
}