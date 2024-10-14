/**
 * @file state.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a PDA state.
 * @date 12/10/2024
 */

#pragma once

#include "transitionSet.hpp"

/**
 * @brief Class to represent a PDA state. A state is a node in the graph of a PDA which contains transitions to other states depending 
 *        on the input symbol and the top of the stack.
 */
class State {
  public:
    State(const std::string&);
    const std::string& ToString() const;
    const TransitionSet& Transitions() const;
    TransitionSet& Transitions();
  private:
    const std::string name;
    TransitionSet transitions;
};
