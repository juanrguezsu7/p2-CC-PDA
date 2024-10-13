#pragma once

#include <queue>
#include <iostream>

#include "state.hpp"
#include "PDAStack.hpp"

using TransitionInfo = std::tuple<State*, std::vector<Symbol>, PDAStack>;

class PDA {
  public:
    PDA(const std::map<std::string, State*>&, const Alphabet&, State*, const PDAStack&);
    bool Accepts(const std::string&);
    void EnableTrace();
    ~PDA();
  private:
    std::queue<TransitionInfo> pendantTransitions;
    std::map<std::string, State*> states;
    Alphabet innerAlphabet;
    State* initialState;
    PDAStack initialStack;
    bool isTraceEnabled;
    bool ProcessTransition();
    void PrintTransitionTrace(const TransitionInfo&) const;
    void PrintNextTransitions(State*, const Symbol&, const Symbol&, State*, const std::vector<Symbol>&) const;
};