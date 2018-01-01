#include "autocomplete.h"

#ifndef SRC_AUTOCOMP_TEST_H
#define SRC_AUTOCOMP_TEST_H

class AutoCompleteTest {
  public:
      void runTests();

  private:
    AutoComplete autocompleter;
    void testInsertionAndContains();
    void testCompletion();
    void testDictImport();
};

#endif
