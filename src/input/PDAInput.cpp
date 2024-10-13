#include "PDAInput.hpp"

const char PDAInput::COMMENT_SYMBOL = '#';

PDA PDAInput::ReadPDA(const std::string& FILENAME) {
  std::ifstream reader{FILENAME};
  if (!reader.is_open()) {
    throw std::invalid_argument{"Reading file error: File '" + FILENAME + "' not found"};
  }
  std::vector<std::string> rawLines;
  for (std::string line; std::getline(reader, line);) {
    rawLines.emplace_back(line);
  }
  std::vector<std::string> lines;
  std::copy_if(rawLines.begin(), rawLines.end(), std::back_inserter(lines), [](const std::string& LINE) { return LINE[0] != COMMENT_SYMBOL; });
  std::map<std::string, State*> states;
  std::stringstream readingStream{lines[0]};
  std::string rawData;
  while (readingStream >> rawData) {
    states.emplace(rawData, new State{rawData});
  }
  Alphabet alphabet{Symbol::EPSILON};
  readingStream = std::stringstream{lines[1]};
  while (readingStream >> rawData) {
    alphabet.insert(Symbol{rawData[0]});
  }
  Alphabet stackAlphabet;
  readingStream = std::stringstream{lines[2]};
  while (readingStream >> rawData) {
    stackAlphabet.insert(Symbol{rawData[0]});
  }
  if (states.find(lines[3]) == states.end()) {
    throw std::invalid_argument{"Reading file error: Initial state: '" + lines[3] + "' not found in states list ( " + StatesFormatting(states) + ")"};
  }
  State* initialState{states.at(lines[3])};
  Symbol initialStackSymbol{Symbol{lines[4][0]}};
  if (stackAlphabet.find(initialStackSymbol) == stackAlphabet.end()) {
    throw std::invalid_argument{"Reading file error: Initial stack symbol: '" + lines[4] + "' not found in stack alphabet ( " + AlphabetFormatting(stackAlphabet) + ")"};
  }
  for (int i{5}; i < lines.size(); ++i) {
    AddTransition(states, lines[i], alphabet, stackAlphabet);
  }
  return PDA{states, alphabet, initialState, PDAStack{stackAlphabet, initialStackSymbol}};
}

void PDAInput::AddTransition(std::map<std::string, State*>& states, const std::string& RAW_TRANSITION, const Alphabet& INNER_ALPHABET, const Alphabet& STACK_ALPHABET) {
  std::stringstream readingStream{RAW_TRANSITION};
  std::string rawData;
  readingStream >> rawData;
  std::string fromStateName{rawData};
  readingStream >> rawData;
  Symbol inputSymbol{rawData[0]};
  readingStream >> rawData;
  Symbol stackSymbol{rawData[0]};
  readingStream >> rawData;
  std::string toStateName{rawData};
  readingStream >> rawData;
  std::vector<Symbol> stackSymbols{Symbol::ToSymbols(rawData)};
  if (states.find(fromStateName) == states.end()) {
    throw std::invalid_argument{"Reading file error: From state: '" + fromStateName + "' not found in states list ( " + StatesFormatting(states) + ")"};
  }
  State* fromState{states.at(fromStateName)};
  if (states.find(toStateName) == states.end()) {
    throw std::invalid_argument{"Reading file error: To state: '" + toStateName + "' not found in states list ( " + StatesFormatting(states) + ")"};
  }
  State* toState{states.at(toStateName)};
  if (INNER_ALPHABET.find(inputSymbol) == INNER_ALPHABET.end()) {
    throw std::invalid_argument{"Reading file error: Input symbol: '" + inputSymbol.ToString() + "' not found in alphabet ( " + AlphabetFormatting(INNER_ALPHABET) + ")"};
  }
  if (STACK_ALPHABET.find(stackSymbol) == STACK_ALPHABET.end()) {
    throw std::invalid_argument{"Reading file error: Stack symbol: '" + stackSymbol.ToString() + "' not found in stack alphabet ( " + AlphabetFormatting(STACK_ALPHABET) + ")"};
  }
  if (fromState->Transitions().find(inputSymbol) != fromState->Transitions().end()) {
    auto& inputTransitions = fromState->Transitions()[inputSymbol];
    if (inputTransitions.find(stackSymbol) != inputTransitions.end()) {
        inputTransitions[stackSymbol].emplace_back(TransitionResult{toState, stackSymbols});
    } else {
      inputTransitions.emplace(stackSymbol, std::vector<TransitionResult>{TransitionResult{toState, stackSymbols}});
    }
  } else {
    fromState->Transitions().emplace(inputSymbol, std::map<Symbol, std::vector<TransitionResult>> {{stackSymbol, std::vector<TransitionResult>{TransitionResult{toState, stackSymbols}}}});
  }
}

std::string PDAInput::AlphabetFormatting(const Alphabet& ALPHABET) {
  return std::accumulate(ALPHABET.begin(), ALPHABET.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; });
}

std::string PDAInput::StatesFormatting(const std::map<std::string, State*>& STATES) {
  return std::accumulate(STATES.begin(), STATES.end(), std::string{}, [](const std::string& ACCOUNT, const std::pair<std::string, State*>& PAIR) { return ACCOUNT + PAIR.first + " "; });
}