/**
 * @file PDAInput.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to read a PDA from a file.
 * @date 12/10/2024
 */

#include "PDAInput.hpp"

/** 
 * @brief Symbol used to indicate that a line is a comment.
 */
const char PDAInput::COMMENT_SYMBOL = '#';

/**
 * @brief Reads a PDA from a file. The format is specified in the class documentation.
 * 
 * @param FILENAME Name of the file to read the PDA from.
 * @return The PDA read from the file.
 * @throw std::invalid_argument If the file does not exist or the PDA specified in the file is invalid.
 */
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
    const Symbol SYMBOL{rawData[0]};
    if (SYMBOL == Symbol::EPSILON) {
      throw std::invalid_argument{"Reading file error: Stack alphabet cannot contain the empty symbol"};
    }
    stackAlphabet.insert(SYMBOL);
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

/**
 * @brief Adds a transition to the PDA.
 * 
 * @param states Map of states of the PDA.
 * @param RAW_TRANSITION Raw data of the transition.
 * @param INNER_ALPHABET Alphabet of the input symbols.
 * @param STACK_ALPHABET Alphabet of the stack symbols.
 * @throw std::invalid_argument If the transition is invalid.
 */
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
  fromState->Transitions().AddTransition(inputSymbol, stackSymbol, toState, stackSymbols);
}

/**
 * @brief Formats the alphabet to a string.
 * 
 * @param ALPHABET Alphabet to format.
 * @return The formatted alphabet.
 */
std::string PDAInput::AlphabetFormatting(const Alphabet& ALPHABET) {
  return std::accumulate(ALPHABET.begin(), ALPHABET.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; });
}

/**
 * @brief Formats the states to a string.
 * 
 * @param STATES States to format.
 * @return The formatted states.
 */
std::string PDAInput::StatesFormatting(const std::map<std::string, State*>& STATES) {
  return std::accumulate(STATES.begin(), STATES.end(), std::string{}, [](const std::string& ACCOUNT, const std::pair<std::string, State*>& PAIR) { return ACCOUNT + PAIR.first + " "; });
}
