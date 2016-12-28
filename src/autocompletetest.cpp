#include <iostream>
#include <cassert>
#include <fstream>

#include "autocomplete.h"


class AutoCompleteTest {
public:
    void runTests() {
      testInsertionAndContains();
      testCompletion();
      testDictImport();
    }

private:
    AutoComplete autocompleter;

    void testInsertionAndContains(){
      std::cout << "testing containment: \n";
      autocompleter.insert("joel");
      autocompleter.insert("test");
      assert(autocompleter.contains("joel"));
      assert(autocompleter.contains("test"));
      assert(!autocompleter.contains("stuff"));
    }

    void testCompletion(){
      std::string result = autocompleter.getCompletions("jo");
      assert(result == "joel \n");

      result = autocompleter.getCompletions("te");
      assert(result == "test \n");

      autocompleter.insert("joela");
      autocompleter.insert("joeldavid");
      result = autocompleter.getCompletions("joel");
      std::cout << result;
      assert(result == "joel joeldavid joela \n");

    }

    void testDictImport(){
      std::ifstream input_file("dictionary.txt");
      std::string word;

      if (!input_file){
        std::cout << "file not opened";
        return;
      }
      while (input_file >> word){
        autocompleter.insert(word);
      }
      std::string result = autocompleter.getCompletions("te");
      std::cout << result << "\n";
    }
};
