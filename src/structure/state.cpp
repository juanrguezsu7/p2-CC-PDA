/**
 * @file state.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a PDA state.
 * @date 12/10/2024
 */

#include "state.hpp"

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
 * @brief Returns a read-only reference to the transitions of the state.
 * 
 * @return A read-only reference to the transitions of the state.
 */
const TransitionSet& State::Transitions() const { 
  return transitions; 
}

/**
 * @brief Returns a reference to the transitions of the state.
 * 
 * @return A reference to the transitions of the state.
 */
TransitionSet& State::Transitions() { 
  return transitions;
}
