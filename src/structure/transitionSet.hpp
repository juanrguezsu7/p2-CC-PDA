/**
 * @file transitionSet.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a set of transitions of a PDA state.
 * @date 12/10/2024
 */

#pragma once

#include <stdexcept>
#include <map>

#include "symbol.hpp"

class State;

/**
 * @brief Type to represent the result of a transition. The result is a tuple containing the next state and the symbols to push to the stack.  
 */
using TransitionResult = std::tuple<State*, std::vector<Symbol>>;

class TransitionSet {
  public:
    static const std::vector<TransitionResult> EMPTY_TRANSITION_RESULTS;

    void AddTransition(const Symbol&, const Symbol&, State*, const std::vector<Symbol>&);
    bool HasTransitions(const Symbol&, const Symbol&) const;
    const std::vector<TransitionResult>& GetTransitions(const Symbol&, const Symbol&) const;
  private:
    std::map<Symbol, std::map<Symbol, std::vector<TransitionResult>>> transitions;
};
