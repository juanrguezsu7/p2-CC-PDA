/**
 * @file transitionSet.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a set of transitions of a PDA state.
 * @date 12/10/2024
 */

#include "transitionSet.hpp"

const std::vector<TransitionResult> TransitionSet::EMPTY_TRANSITION_RESULTS{};

/**
 * @brief Adds a transition to the set of transitions.
 * 
 * @param INPUT_SYMBOL Input symbol of the transition.
 * @param STACK_SYMBOL Stack symbol of the transition.
 * @param TO_STATE Next state of the transition.
 * @param STACK_SYMBOLS Symbols to push to the stack.
 */
void TransitionSet::AddTransition(const Symbol& INPUT_SYMBOL, const Symbol& STACK_SYMBOL, State* TO_STATE, const std::vector<Symbol>& STACK_SYMBOLS) {
  if (transitions.find(INPUT_SYMBOL) != transitions.end()) {
    auto& inputTransitions{transitions[INPUT_SYMBOL]};
    if (inputTransitions.find(STACK_SYMBOL) != inputTransitions.end()) {
        inputTransitions[STACK_SYMBOL].emplace_back(TransitionResult{TO_STATE, STACK_SYMBOLS});
    } else {
      inputTransitions.emplace(STACK_SYMBOL, std::vector<TransitionResult>{TransitionResult{TO_STATE, STACK_SYMBOLS}});
    }
  } else {
    transitions.emplace(INPUT_SYMBOL, std::map<Symbol, std::vector<TransitionResult>> {{STACK_SYMBOL, std::vector<TransitionResult>{TransitionResult{TO_STATE, STACK_SYMBOLS}}}});
  }
}

/**
 * @brief Checks if there are transitions for a given input and stack symbol.
 * 
 * @param INPUT_SYMBOL Input symbol to check.
 * @param STACK_SYMBOL Stack symbol to check.
 * @return true If there are transitions for the input and stack symbol.
 * @return false If there are no transitions for the input and stack symbol.
 */
bool TransitionSet::HasTransitions(const Symbol& INPUT_SYMBOL, const Symbol& STACK_SYMBOL) const {
  try {
    const auto& INPUT_TRANSITIONS{transitions.at(INPUT_SYMBOL)};
    return INPUT_TRANSITIONS.find(STACK_SYMBOL) != INPUT_TRANSITIONS.end();
  } catch (...) {
    return false;
  }
}

/**
 * @brief Returns the transitions for a given input and stack symbol.
 * 
 * @param INPUT_SYMBOL Input symbol to check.
 * @param STACK_SYMBOL Stack symbol to check.
 * @return The transitions for the input and stack symbol.
 */
const std::vector<TransitionResult>& TransitionSet::GetTransitions(const Symbol& INPUT_SYMBOL, const Symbol& STACK_SYMBOL) const {
  if (!HasTransitions(INPUT_SYMBOL, STACK_SYMBOL)) {
    return EMPTY_TRANSITION_RESULTS;
  }
  return transitions.at(INPUT_SYMBOL).at(STACK_SYMBOL);
}