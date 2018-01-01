#include <string>

#ifndef SRC_AUTOCOMP_H
#define SRC_AUTOCOMP_H

struct Node {
    char val;
    Node* children[26]; // size of alphabet
    bool isEndOfWord;
};

class AutoComplete{
    public:
        AutoComplete();
        ~AutoComplete();

        void insert(std::string word);
        void insertDictionary();
        bool contains(std::string word);
        std::string getCompletions(std::string word);

    private:
        Node* root;

        static Node* newNode();
        Node* getNode(std::string substring);
        static bool isLeaf(Node* node);

        friend class AutoCompleteTest;
};

#endif
