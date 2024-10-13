/**
 * @file PDAInput.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to read a PDA from a file.
 * @date 12/10/2024
 */

#pragma once

#include <fstream>
#include <algorithm>
#include <sstream>

#include "../structure/PDA.hpp"

/**
 * @brief Type to represent the result of a transition. The result is a tuple containing the next state and the symbols to push to the stack. 
 */
using TransitionResult = std::tuple<State*, std::vector<Symbol>>;

/**
 * @brief Class to read a PDA from a file. The file must have the following format (comments with a '#' starting the line will be ignored):
 * 
 *        - The first line contains the states of the PDA separated by spaces.
 * 
 *        - The second line contains the input alphabet of the PDA separated by spaces.
 * 
 *        - The third line contains the stack alphabet of the PDA separated by spaces.
 * 
 *        - The fourth line contains the initial state of the PDA.
 * 
 *        - The fifth line contains the initial stack symbol of the PDA.
 * 
 *        - The rest of the lines contain the transitions of the PDA in the format: "fromState inputSymbol stackTop toState stackSymbols"
 * 
 *        - To represent the empty symbol use the '.' character.
 */
class PDAInput {
  public:
    const static char COMMENT_SYMBOL;

    static PDA ReadPDA(const std::string&);
  private:
    static void AddTransition(std::map<std::string, State*>&, const std::string&, const Alphabet&, const Alphabet&);
    static std::string AlphabetFormatting(const Alphabet&);
    static std::string StatesFormatting(const std::map<std::string, State*>&);
};
