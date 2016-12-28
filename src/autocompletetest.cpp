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
      std::cout << "Insertion test passed \n";
    }

    void testCompletion(){
      std::string result = autocompleter.getCompletions("jo");
      assert(result == "joel \n");

      result = autocompleter.getCompletions("te");
      assert(result == "test \n");

      autocompleter.insert("joela");
      autocompleter.insert("joeldavid");
      result = autocompleter.getCompletions("joel");
      assert(result == "joel joeldavid joela \n");
      std::cout << "Completion test passed \n";

    }

    void testDictImport(){
      autocompleter.insertDictionary();

      std::string result = autocompleter.getCompletions("photosynthesis");
      std::cout << result;
      assert(result == "photosynthesis photosynthesises \n");
      std::cout << "Dictionary import and completions passed \n";
    }
};
