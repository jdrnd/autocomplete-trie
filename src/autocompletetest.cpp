#include <iostream>
#include <cassert>
#include <fstream>

#include "autocompletetest.h"
#include "autocomplete.h"



// TODO make a header file for this!

void AutoCompleteTest::runTests() {
  testInsertionAndContains();
  testCompletion();
  testDictImport();
}


void AutoCompleteTest::testInsertionAndContains(){
  std::cout << "testing containment: \n";
  this->autocompleter.insert("joel");
  this->autocompleter.insert("test");
  assert(this->autocompleter.contains("joel"));
  assert(this->autocompleter.contains("test"));
  assert(!this->autocompleter.contains("stuff"));
  std::cout << "Insertion test passed \n";
}

void AutoCompleteTest::testCompletion(){
  std::string result = this->autocompleter.getCompletions("jo");
  assert(result == "joel\n\n");

  result = this->autocompleter.getCompletions("te");
  assert(result == "test\n\n");

  this->autocompleter.insert("joela");
  this->autocompleter.insert("joeldavid");
  result = this->autocompleter.getCompletions("joel");
  assert(result == "joel\njoeldavid\njoela\n\n");
  std::cout << "Completion test passed \n";
}

void AutoCompleteTest::testDictImport(){
  this->autocompleter.insertDictionary();

  std::string result = this->autocompleter.getCompletions("photosynthesis");
  std::cout << result;
  assert(result == "photosynthesis\nphotosynthesises\n\n");
  std::cout << "Dictionary import and completions passed \n";
}
