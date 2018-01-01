# Autocompletion in C++

Uses a trie (see [here](https://www.geeksforgeeks.org/trie-insert-and-search/) for an explanation of how tries work) `O(m)` lookup time, where `m` is the length of the string. This approach is time-efficient but considerably space-inefficient. A more space efficient implementation of autocomplete using ternary search trees (much more space-efficient but only slightly less time-efficient) can be found at https://github.com/jdrnd/autocomplete-ternary.

![Screenshot](https://image.prntscr.com/image/guGifAWPR4qMnBE2jrzOzw.png)

#### Building
For the standard REPL, just run the included `build.sh` file, which will produce the `./autocomp` binary.

#### Usage
This is just a demo; to use build, then run the binary. Press `t` to run tests,
`e` to exit, and `w` to enter a word and have the program return completions.

#### Verifying Memory Integrity
To check for memory leaks, install `valgrind` and run the following command:
`valgrind --leak-check=yes ./autocomp -v`


#### API

`void Autocomplete::insert(std::string word)`
Inserts `word` into the trie, making it available for future completion requests

`void AutoComplete::insertDictionary()`
Inserts all words contained in `dictionary.txt` into the trie

`bool AutoComplete::contains(std::string word)`
Returns whether or not `word` is in the trie

`std::string AutoComplete::getCompletions(std::string word)`
Returns a newline-delimited list of all possible completions of `word` currently stored in the trie.
