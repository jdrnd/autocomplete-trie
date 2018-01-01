#include <iostream>
#include <string>

#include "autocompletetest.h"


int main(void) {
  bool should_quit = false;
  char command;
  std::string prefix;
  std::string results;

  AutoCompleteTest tester;
  AutoComplete autocompleter;
  autocompleter.insertDictionary();

  while (true) {
    std::cout << "\nPress t to run tests, e to exit, or w to enter a word to complete: \n";
    std::cin >> command;

    switch (command) {
      case 't':
        tester.runTests();
        break;
      case 'e':
        should_quit = true;
        break;
      case 'w':
        std::cout << "Enter work to get completions for: \n";
        std::cin >> prefix;
        results = autocompleter.getCompletions(prefix);
        std::cout << "\n" << results;
        break;
    }
    if (should_quit) break;
  }

}
