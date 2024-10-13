#include "state.hpp"

using InputSymbolTransitions = std::map<Symbol, std::map<Symbol, std::vector<std::tuple<State*, std::vector<Symbol>>>>>;

State::State(const std::string& NAME) : name(NAME) {}

const std::string& State::ToString() const { 
  return name; 
}

InputSymbolTransitions& State::Transitions() { 
  return transitions; 
}

const InputSymbolTransitions& State::Transitions() const { 
  return transitions; 
}