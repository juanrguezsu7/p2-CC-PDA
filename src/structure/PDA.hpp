/**
 * @file PDA.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a stack emptying Pushdown Automaton.
 * @date 12/10/2024
 */

#pragma once

#include <queue>
#include <iostream>

#include "state.hpp"
#include "PDAStack.hpp"

/**
 * @brief Type to represent the state of a PDA after a transition. The tuple contains actual state, input symbols to consume 
 *        and stack symbols to push.
 */
using TransitionInfo = std::tuple<State*, std::vector<Symbol>, PDAStack>;

/**
 * @brief Class to represent a stack emptying Pushdown Automaton. A PDA is a tuple (Q, Σ, Γ, δ, q0, Z0) where:
 *        - Q is a finite set of states.
 *        - Σ is a finite input alphabet.
 *        - Γ is a finite stack alphabet.
 *        - δ is the transition function.
 *        - q0 is the initial state.
 *        - Z0 is the initial stack symbol.
 *        The PDA accepts an input string if there is a sequence of transitions from the initial state to a final state
 *        such that the stack is empty at the end of the sequence.
 */
class PDA {
  public:
    const static unsigned MAX_TRANSITIONS;

    PDA(const std::map<std::string, State*>&, const Alphabet&, State*, const PDAStack&);
    bool Accepts(const std::string&);
    void EnableTrace();
    unsigned TransitionCounter() const;
    ~PDA();
  private:
    std::queue<TransitionInfo> pendantTransitions;
    std::map<std::string, State*> states;
    Alphabet innerAlphabet;
    State* initialState;
    PDAStack initialStack;
    bool isTraceEnabled;
    unsigned transitionCounter;
    bool ProcessTransition();
    void PrintTransitionTrace(const TransitionInfo&) const;
    void PrintNextTransitions(State*, const Symbol&, const Symbol&, State*, const std::vector<Symbol>&) const;
};
