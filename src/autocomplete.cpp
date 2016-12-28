#include <cctype>
#include <stack>
#include <queue>
#include <sstream>
#include <cstdint>
#include <ostream>
#include <fstream>

#include "autocomplete.h"

AutoComplete::AutoComplete() {
    this->root = this->newNode();
}

AutoComplete::~AutoComplete() {
  Node* currNode = this->root;
  if (currNode == NULL) return;

  std::stack<Node*> toDelete;
  toDelete.push(currNode);

  while (!toDelete.empty()){
    currNode = toDelete.top();
    toDelete.pop();

    for (int i = 0; i < 26; i++) {
      if (currNode->children[i] != NULL){
        toDelete.push(currNode->children[i]);
      }
    }
    delete currNode;
  }
}

Node* AutoComplete::newNode() {
    Node* node = new Node;
    node->val = '\0';
    node->isEndOfWord = false;

    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void AutoComplete::insert(std::string word) {
    Node* currNode = this->root;
    char currentLetter = '\0';
    int letterIndex = 0;

    int wordLen = word.length();
    for (int i = 0; i < wordLen; i++) {
        // convert to lower case
        currentLetter = (char)tolower((int)word[i]);

        // Shift index, ascci table: https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
        letterIndex = (int)currentLetter - 97;

        // We only accept letters
        if (letterIndex < 0 || letterIndex > 25) break;

        if (currNode->children[letterIndex]){
            // Do nothing
        }
        else {
            // Create new node
            currNode->children[letterIndex] = this->newNode();
            currNode->children[letterIndex]->val = currentLetter;
        }
        currNode = currNode->children[letterIndex];
    }
    currNode->isEndOfWord = true;
}

Node* AutoComplete::getNode(std::string substring) {
  Node* currNode = this->root;
  char currentLetter = '\0';
  int letterIndex = 0;
  int length = substring.length();

  for (int i = 0; i < length; i++){
      currentLetter = substring[i];
      letterIndex = (int)currentLetter - 97;

      if (letterIndex < 0 || letterIndex > 25) return NULL;

      // If letter does not have matching node
      if (!currNode->children[letterIndex]) return NULL;
      else {
          currNode = currNode->children[letterIndex];
      }
  }
  return currNode;
}


bool AutoComplete::contains(std::string word) {
  Node* lastNode = this->getNode(word);

  if (lastNode) return true;
  else return false;
}

std::string AutoComplete::getCompletions(std::string word) {
  Node* parentNode = this->getNode(word);
  if (parentNode == NULL ||
  parentNode->val != word[word.length() - 1]) return "";

  Node* currentNode;
  std::string prefix;
  std::stack<Node*> toVisit;
  toVisit.push(parentNode);

  // each node in toVisit has a corresponding prefix in prefixes

  std::stack<std::string> prefixes;

  // Remove last letter from word so that it is not repeated
  word = word.substr(0, word.length() - 1);
  prefixes.push(word);
  std::vector<std::string> wordsFound;

  while (!toVisit.empty()){
    currentNode = toVisit.top();
    toVisit.pop();
    prefix = prefixes.top();
    prefixes.pop();

    if (isLeaf(currentNode)){
      prefix += currentNode->val;
      wordsFound.push_back(prefix);
    }
    else {
      prefix += currentNode->val;
      if (currentNode->isEndOfWord){
        wordsFound.push_back(prefix);
      }
      // Check all children for completions
      for (int i = 0; i < 26; i++) {
        if (currentNode->children[i] != NULL){
          toVisit.push(currentNode->children[i]);
          prefixes.push(prefix);
        }
      }
    }
  }
  std::stringstream allWords;
  for (std::vector<std::string>::iterator it = wordsFound.begin() ; it != wordsFound.end(); ++it){
    allWords << *it << " ";
  }
  allWords << "\n";
  return allWords.str();
}

bool AutoComplete::isLeaf(Node* node) {
  if (node == NULL) return false;

  if (!node->isEndOfWord) return false;
  for (int i = 0; i < 26; i++){
    if (node->children[i] != NULL) return false;
  }
  return true;
}

void AutoComplete::insertDictionary() {
  std::string DICTIONARY_FILE = "dictionary.txt";
  std::ifstream input_file(DICTIONARY_FILE);
  std::string word;

  if (!input_file){
    printf("file not opened");
    return;
  }
  while (input_file >> word){
    this->insert(word);
  }
}
