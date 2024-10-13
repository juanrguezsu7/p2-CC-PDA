/**
 * @file state.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a PDA state.
 * @date 12/10/2024
 */

#pragma once

#include <map>
#include <tuple>

#include "symbol.hpp"

/**
 * @brief Class to represent a PDA state. A state is a node in the graph of a PDA which contains transitions to other states depending 
 *        on the input symbol and the top of the stack.
 */
class State {
  using TransitionResult = std::tuple<State*, std::vector<Symbol>>;
  using InputSymbolTransitions = std::map<Symbol, std::map<Symbol, std::vector<TransitionResult>>>;
  public:
    State(const std::string& NAME);
    const std::string& ToString() const;
    InputSymbolTransitions& Transitions();
    const InputSymbolTransitions& Transitions() const;
  private:
    const std::string name;
    InputSymbolTransitions transitions;
};
