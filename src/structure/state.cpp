/**
 * @file state.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a PDA state.
 * @date 12/10/2024
 */

#include "state.hpp"

/**
 * @brief Type to represent the result of a transition. The result is a tuple containing the next state and the symbols to push to the stack. 
 */
using TransitionResult = std::tuple<State*, std::vector<Symbol>>;

/**
 * @brief Type to represent the transitions of a state. The transitions are stored in a map where the key is the input symbol and the value is
 *        another map whose key is the top of the stack and the value is a vector of TransitionResult.
 */
using InputSymbolTransitions = std::map<Symbol, std::map<Symbol, std::vector<TransitionResult>>>;

/**
 * @brief Constructs a new State object.
 * 
 * @param NAME Name of the state.
 */
State::State(const std::string& NAME) : name(NAME) {}

/**
 * @brief Returns the name of the state.
 * 
 * @return The name of the state.
 */
const std::string& State::ToString() const { 
  return name; 
}

/**
 * @brief Returns a read/write reference to the transitions of the state.
 * 
 * @return A read/write reference to the transitions of the state.
 */
InputSymbolTransitions& State::Transitions() { 
  return transitions; 
}

/**
 * @brief Returns a read-only reference to the transitions of the state.
 * 
 * @return A read-only reference to the transitions of the state.
 */
const InputSymbolTransitions& State::Transitions() const { 
  return transitions; 
}
