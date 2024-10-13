#pragma once

#include <fstream>
#include <algorithm>
#include <sstream>

#include "../structure/PDA.hpp"

using TransitionResult = std::tuple<State*, std::vector<Symbol>>;

class PDAInput {
  public:
    const static char COMMENT_SYMBOL;

    static PDA ReadPDA(const std::string&);
  private:
    static void AddTransition(std::map<std::string, State*>&, const std::string&, const Alphabet&, const Alphabet&);
    static std::string AlphabetFormatting(const Alphabet&);
    static std::string StatesFormatting(const std::map<std::string, State*>&);
};