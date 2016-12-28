#include <string>

struct Node {
    char val;
    Node* children[26]; // size of alphabet
    bool isEndOfWord;
};

class AutoComplete{
    public:
        AutoComplete();

        void insert(std::string word);
        bool contains(std::string word);
        std::string getCompletions(std::string word);

    private:
        Node* root;

        static Node* newNode();
        Node* getNode(std::string substring);
        bool isLeaf(Node* node);

        friend class AutoCompleteTest;
};
