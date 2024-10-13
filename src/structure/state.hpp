#pragma once

#include <map>
#include <tuple>

#include "symbol.hpp"

class State {
  using InputSymbolTransitions = std::map<Symbol, std::map<Symbol, std::vector<std::tuple<State*, std::vector<Symbol>>>>>;
  public:
    State(const std::string& NAME);
    const std::string& ToString() const;
    InputSymbolTransitions& Transitions();
    const InputSymbolTransitions& Transitions() const;
  private:
    const std::string name;
    InputSymbolTransitions transitions;
};