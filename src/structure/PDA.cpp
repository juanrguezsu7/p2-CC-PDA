#include "PDA.hpp"

PDA::PDA(const std::map<std::string, State*>& STATES, const Alphabet& INNER_ALPHABET, State* INITIAL_STATE, const PDAStack& INITIAL_STACK)
         : states(STATES), innerAlphabet(INNER_ALPHABET), initialState(INITIAL_STATE), initialStack(INITIAL_STACK) {}

bool PDA::Accepts(const std::string& INPUT) {
  pendantTransitions.push(TransitionInfo{initialState, Symbol::ToSymbols(INPUT), initialStack});
  while (!pendantTransitions.empty()) {
    if (ProcessTransition()) {
      pendantTransitions = std::queue<TransitionInfo>{};
      return true;
    }
  }
  return false;
}

bool PDA::ProcessTransition() {
  TransitionInfo currentTransition{pendantTransitions.front()};
  pendantTransitions.pop();
  if (isTraceEnabled) {
    PrintTransitionTrace(currentTransition);
  }
  State* actualState{std::get<0>(currentTransition)};
  std::vector<Symbol> inputSymbols{std::get<1>(currentTransition)};
  PDAStack stack{std::get<2>(currentTransition)};
  if (stack.IsEmpty()) {
    return inputSymbols.empty();
  }
  Symbol stackTop{stack.Pop()};
  Symbol actualSymbol{inputSymbols.empty() ? Symbol::EPSILON : inputSymbols[0]};
  if (innerAlphabet.find(actualSymbol) == innerAlphabet.end()) {
    const std::string ALPHABET_STR = std::accumulate(innerAlphabet.begin(), innerAlphabet.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; });
    throw std::invalid_argument{"Runtime error: Symbol: '" + actualSymbol.ToString() + "' not found in PDA alphabet ( " + ALPHABET_STR + ")"};
  }
  if (actualState->Transitions().find(actualSymbol) != actualState->Transitions().end()
      && actualState->Transitions()[actualSymbol].find(stackTop) != actualState->Transitions()[actualSymbol].end()) {
    const auto& POSSIBLE_TRANSITIONS = actualState->Transitions()[actualSymbol][stackTop];
    for (const auto& TRANSITION : POSSIBLE_TRANSITIONS) {
      State* nextState{std::get<0>(TRANSITION)};
      std::vector<Symbol> stackSymbols{std::get<1>(TRANSITION)};
      std::vector<Symbol> newInputSymbols{inputSymbols.size() > 1 ? std::vector<Symbol>{inputSymbols.begin() + 1, inputSymbols.end()} : std::vector<Symbol>{}};
      PDAStack newStack{stack};
      for (int i{0}; i < stackSymbols.size(); ++i) {
        Symbol toPushSymbol{stackSymbols[stackSymbols.size() - 1 - i]};
        if (toPushSymbol != Symbol::EPSILON) {
          newStack.Push(toPushSymbol);
        }
      }
      pendantTransitions.push(TransitionInfo{nextState, newInputSymbols, newStack});
      if (isTraceEnabled) {
        PrintNextTransitions(actualState, actualSymbol, stackTop, nextState, stackSymbols);
      }
    }
  }
  // Checking epsilon transitions only if we have not checked them yet.
  if (actualSymbol != Symbol::EPSILON && actualState->Transitions().find(Symbol::EPSILON) != actualState->Transitions().end()
      && actualState->Transitions()[Symbol::EPSILON].find(stackTop) != actualState->Transitions()[Symbol::EPSILON].end()) {
    auto& POSSIBLE_TRANSITIONS = actualState->Transitions()[Symbol::EPSILON][stackTop];
    for (auto& TRANSITION : POSSIBLE_TRANSITIONS) {
      State* nextState{std::get<0>(TRANSITION)};
      std::vector<Symbol> stackSymbols{std::get<1>(TRANSITION)};
      PDAStack newStack{stack};
      for (int i{0}; i < stackSymbols.size(); ++i) {
        Symbol toPushSymbol{stackSymbols[stackSymbols.size() - 1 - i]};
        if (toPushSymbol != Symbol::EPSILON) {
          newStack.Push(toPushSymbol);
        }
      }
      pendantTransitions.push(TransitionInfo{nextState, inputSymbols, newStack});
      if (isTraceEnabled) {
        PrintNextTransitions(actualState, Symbol::EPSILON, stackTop, nextState, stackSymbols);
      }
    }
  }
  return false;
}

void PDA::PrintTransitionTrace(const TransitionInfo& TRANSITION) const {
  std::cout << "--------------------\nCurrent transition:";
  std::cout << "\n\tState: " + std::get<0>(TRANSITION)->ToString();
  std::cout << "\n\tSymbols: ";
  for (const Symbol& SYMBOL : std::get<1>(TRANSITION)) {
    std::cout << SYMBOL.ToString();
  }
  std::cout << "\n\tStack: ";
  std::cout << std::get<2>(TRANSITION).ToString();
  std::cout << "\n\tNext transitions:\n";
}

void PDA::PrintNextTransitions(State* origin, const Symbol& TO_CONSUME, const Symbol& STACK_TOP, State* destiny, const std::vector<Symbol>& STACK_REPLACEMENT) const {
  std::cout << "\t\tFrom state: " + origin->ToString();
  std::cout << "\n\t\tConsume: " + TO_CONSUME.ToString();
  std::cout << "\n\t\tStack top: " + STACK_TOP.ToString();
  std::cout << "\n\t\tTo state: " + destiny->ToString();
  std::cout << "\n\t\tStack replacement: ";
  for (const Symbol& SYMBOL : STACK_REPLACEMENT) {
    std::cout << SYMBOL.ToString();
  }
  std::cout << "\n\n";
}

void PDA::EnableTrace() {
  isTraceEnabled = true;
}

PDA::~PDA() {
  for (const auto& STATE : states) {
    delete STATE.second;
  }
}