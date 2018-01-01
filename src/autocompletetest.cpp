#include <iostream>
#include <cassert>
#include <fstream>

#include "autocomplete.h"


// TODO make a header file for this!

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
      assert(result == "joel\n\n");

      result = autocompleter.getCompletions("te");
      assert(result == "test\n\n");

      autocompleter.insert("joela");
      autocompleter.insert("joeldavid");
      result = autocompleter.getCompletions("joel");
      assert(result == "joel\njoeldavid\njoela\n\n");
      std::cout << "Completion test passed \n";

    }

    void testDictImport(){
      autocompleter.insertDictionary();

      std::string result = autocompleter.getCompletions("photosynthesis");
      std::cout << result;
      assert(result == "photosynthesis\nphotosynthesises\n\n");
      std::cout << "Dictionary import and completions passed \n";
    }
};
