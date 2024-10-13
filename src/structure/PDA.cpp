/**
 * @file PDA.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a stack emptying Pushdown Automaton.
 * @date 12/10/2024
 */

#include "PDA.hpp"

/**
 * @brief Maximum number of transitions to process.
 */
const unsigned PDA::MAX_TRANSITIONS{10000000};

/**
 * @brief Constructs a new PDA object.
 * 
 * @param STATES Map of states of the PDA.
 * @param INNER_ALPHABET Alphabet of the input symbols.
 * @param givenInitialState Initial state of the PDA.
 * @param INITIAL_STACK Initial stack of the PDA.
 */
PDA::PDA(const std::map<std::string, State*>& STATES, const Alphabet& INNER_ALPHABET, State* givenInitialState, const PDAStack& INITIAL_STACK)
         : states(STATES), innerAlphabet(INNER_ALPHABET), initialState(givenInitialState), initialStack(INITIAL_STACK) {
  isTraceEnabled = false;
}

/**
 * @brief Checks if the PDA accepts a given input string.
 * 
 * @param INPUT Input string to check.
 * @return true If the PDA accepts the input string.
 * @return false If the PDA does not accept the input string.
 * @throw std::runtime_error If the maximum number of transitions is reached.
 */
bool PDA::Accepts(const std::string& INPUT) {
  pendantTransitions = std::queue<TransitionInfo>{};
  transitionCounter = 0;
  // Pushing the initial state to the queue of transitions.
  pendantTransitions.push(TransitionInfo{initialState, Symbol::ToSymbols(INPUT), initialStack});
  // Processing transitions until the stack is empty or the input string is consumed and the stack is empty.
  while (!pendantTransitions.empty()) {
    ++transitionCounter;
    // If the stack is empty and the input string is consumed, the PDA accepts the input string.
    if (ProcessTransition()) {
      return true;
    }
    // If the maximum number of transitions is reached, we stop the process and throw an exception.
    if (transitionCounter == MAX_TRANSITIONS) {
      throw std::runtime_error{"Runtime error: Maximum number of transitions reached."};
    }
  }
  return false;
}

/**
 * @brief Processes the next transition in the queue, updating the queue with the new possible transitions.
 * 
 * @return true If the stack is empty and the input string is consumed.
 * @return false If the stack is empty and the input string is not consumed or the stack is not empty.
 * @throw std::invalid_argument If a symbol of the input string is not in the PDA alphabet.
 */
bool PDA::ProcessTransition() {
  // Retrieving the current transition, which contains the actual state, the input symbols to consume and the stack.
  const TransitionInfo CURRENT_TRANSITION{pendantTransitions.front()};
  pendantTransitions.pop();
  if (isTraceEnabled) {
    PrintTransitionTrace(CURRENT_TRANSITION);
  }
  State* actualState{std::get<0>(CURRENT_TRANSITION)};
  const std::vector<Symbol> INPUT_SYMBOLS{std::get<1>(CURRENT_TRANSITION)};
  PDAStack stack{std::get<2>(CURRENT_TRANSITION)};
  // If the stack is empty, we check if the input string is consumed.
  if (stack.IsEmpty()) {
    return INPUT_SYMBOLS.empty();
  }
  // Getting the top of the stack and the actual symbol to consume to find the next possible transitions.
  const Symbol STACK_TOP{stack.Pop()};
  const Symbol ACTUAL_SYMBOL{INPUT_SYMBOLS.empty() ? Symbol::EPSILON : INPUT_SYMBOLS[0]};
  // If the actual symbol is not in the PDA alphabet, we throw an exception.
  if (innerAlphabet.find(ACTUAL_SYMBOL) == innerAlphabet.end()) {
    const std::string ALPHABET_STR{std::accumulate(innerAlphabet.begin(), innerAlphabet.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; })};
    throw std::invalid_argument{"Runtime error: Symbol: '" + ACTUAL_SYMBOL.ToString() + "' not found in PDA alphabet ( " + ALPHABET_STR + ")"};
  }
  // Retrieving the possible transitions from the actual state with the actual symbol and the top of the stack.
  if (actualState->Transitions().find(ACTUAL_SYMBOL) != actualState->Transitions().end()
      && actualState->Transitions()[ACTUAL_SYMBOL].find(STACK_TOP) != actualState->Transitions()[ACTUAL_SYMBOL].end()) {
    const auto& POSSIBLE_TRANSITIONS{actualState->Transitions()[ACTUAL_SYMBOL][STACK_TOP]};
    // For each possible transition, we create a new transition with the next state, the new input symbols and the new stack.
    for (const auto& TRANSITION : POSSIBLE_TRANSITIONS) {
      State* nextState{std::get<0>(TRANSITION)};
      const std::vector<Symbol> NEW_STACK_SYMBOLS{std::get<1>(TRANSITION)};
      const std::vector<Symbol> NEW_INPUT_SYMBOLS{INPUT_SYMBOLS.size() > 1 ? std::vector<Symbol>{INPUT_SYMBOLS.begin() + 1, INPUT_SYMBOLS.end()} : std::vector<Symbol>{}};
      PDAStack newStack{stack};
      // Pushing the new symbols to the stack.
      for (int i{0}; i < NEW_STACK_SYMBOLS.size(); ++i) {
        const Symbol TO_PUSH_SYMBOL{NEW_STACK_SYMBOLS[NEW_STACK_SYMBOLS.size() - 1 - i]};
        if (TO_PUSH_SYMBOL != Symbol::EPSILON) {
          newStack.Push(TO_PUSH_SYMBOL);
        }
      }
      // Adding the new transition to the queue of transitions.
      pendantTransitions.push(TransitionInfo{nextState, NEW_INPUT_SYMBOLS, newStack});
      // Printing the next transitions if the trace mode is enabled.
      if (isTraceEnabled) {
        PrintNextTransitions(actualState, ACTUAL_SYMBOL, STACK_TOP, nextState, NEW_STACK_SYMBOLS);
      }
    }
  }
  // Checking epsilon transitions only if we have not checked them yet.
  if (ACTUAL_SYMBOL != Symbol::EPSILON && actualState->Transitions().find(Symbol::EPSILON) != actualState->Transitions().end()
      && actualState->Transitions()[Symbol::EPSILON].find(STACK_TOP) != actualState->Transitions()[Symbol::EPSILON].end()) {
    const auto& POSSIBLE_TRANSITIONS{actualState->Transitions()[Symbol::EPSILON][STACK_TOP]};
    for (const auto& TRANSITION : POSSIBLE_TRANSITIONS) {
      State* nextState{std::get<0>(TRANSITION)};
      const std::vector<Symbol> NEW_STACK_SYMBOLS{std::get<1>(TRANSITION)};
      PDAStack newStack{stack};
      for (int i{0}; i < NEW_STACK_SYMBOLS.size(); ++i) {
        const Symbol TO_PUSH_SYMBOL{NEW_STACK_SYMBOLS[NEW_STACK_SYMBOLS.size() - 1 - i]};
        if (TO_PUSH_SYMBOL != Symbol::EPSILON) {
          newStack.Push(TO_PUSH_SYMBOL);
        }
      }
      pendantTransitions.push(TransitionInfo{nextState, INPUT_SYMBOLS, newStack});
      if (isTraceEnabled) {
        PrintNextTransitions(actualState, Symbol::EPSILON, STACK_TOP, nextState, NEW_STACK_SYMBOLS);
      }
    }
  }
  return false;
}

/**
 * @brief Prints the current transition trace.
 * 
 * @param TRANSITION Current transition.
 */
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

/**
 * @brief Prints the next transitions of the PDA.
 * 
 * @param origin Origin state of the transition.
 * @param TO_CONSUME Symbol to consume.
 * @param STACK_TOP Top of the stack.
 * @param destiny Destiny state of the transition.
 * @param STACK_REPLACEMENT Symbols to replace in the stack.
 */
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

/**
 * @brief Enables the trace mode of the PDA.
 */
void PDA::EnableTrace() {
  isTraceEnabled = true;
}

/**
 * @brief Returns the number of transitions processed by the PDA.
 * 
 * @return The number of transitions processed by the PDA.
 */
unsigned PDA::TransitionCounter() const {
  return transitionCounter;
}

/**
 * @brief Destroys the PDA object, freeing the memory of the states.
 */
PDA::~PDA() {
  for (const auto& STATE : states) {
    delete STATE.second;
  }
}
