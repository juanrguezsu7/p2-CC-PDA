/**
 * @file main.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the client code.
 * @date 12/10/2024
 */

#include <iostream>

#include "input/PDAInput.hpp"

/**
 * @brief Main function which runs the program.
 * @return 0 on success.
 */
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <PDAFileName>" << std::endl;
    return EXIT_FAILURE;
  }
  std::string fileName{argv[1]};
  try {
    PDA pda{PDAInput::ReadPDA(fileName)};
    pda.EnableTrace(); // Comment this line to disable trace
    std::cout << "PDA loaded from file " + fileName;
    std::string input;
    std::cout << "\nReading input strings from console (empty string to exit)...\n";
    while (true) { 
      std::getline(std::cin, input);
      if (input.length() > 0) {
        if (pda.Accepts(input)) {
          std::cout << "--> Accepted\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        } else {
          std::cout << "--> Rejected\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
        }
      } else {
        break;
      }
    }
  } catch (const std::exception& EXCEPTION) {
    std::cout << EXCEPTION.what() << std::endl;
    return EXIT_FAILURE;
  }
}
