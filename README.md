# Tree Project (Text Analyzer)
- **Programmer**: Mike Boyle
- **Date**: 2022-05-19
- **Section**: CSC-331H

This project uses AVL trees to parse and analyze text.

## Contents
The following files should be present in the same folder:

- `StyleChecker.cpp` (implementation file)
- `StyleChecker.h` (header file)
- `main.cpp` (tester and driver)
- `.replit` (if running in replit.com)
- `README.md` (the file you are reading now)
- `in.txt` (example text file to analyze)

There are also files that implement the AVL tree. These should also be present

- `node.h`
- `AVLTree.cpp`
- `AVLTree.h`
- `treeNodeData.h` (struct that holds a copy of note data without links to other nodes)

## Usage
To use the `StyleChecker` class in your program, you'll need to `#include "Calculator.h"`.

You can then construct and use instances of the class. For example:
```
StyleChecker sc("in.txt", "out.txt");
sc.analyze(); // analyze text at `in.txt` and write report to `out.txt`
```

## Manual and automated testing
The driver program (`main.cpp`) allows for manual testing of the calculator class.

To run the tester on the replit.com repo, simply press the Run button.

The `in.txt` file is included as an example text to analyze.

To compile and run locally:

1. Ensure all project files are in the same folder.
1. Compile `main.cpp`: `g++ --std=c++11 main.cpp StyleChecker.cpp -o main`. Note that you must compile `StyleChecker.cpp` in the same command.
1. Run the compiled executable: `./main.out`

## Implementation notes
### Text parsing
Although this may be suboptimal, I decided to leverage the AVL tree structure when parsing the text. The general procedure is:

1. Parse the file into lines (delimited by `\n`) and insert each paragraph into a `paragraphs` AVL tree.
1. Traverse the `paragraphs` tree and, at each node, split the paragraph into sentences. Insert each sentence into a `sentences` AVL tree.
1. Traverse the `sentences` tree. At each node, split the sentence into tokens and insert each token into the `words` tree. If the token is > 3 characters, also insert it into the `longWords` tree.
1. Generate text statistics by using the sizes of the different trees, other cumulative statistics gathered while parsing, and traversing the `words` and `longWords` trees to find overused words and build the index.

### AVL Tree
I implemented my own AVL tree class, for a few reasons:

1. I wanted the tree to hold a `size` variable to make some of the analysis more efficient.
1. I wanted tree nodes to hold a `count` variable that increments each time the same key is added to the tree. This is a way of solving the problem that we need to know how many times each word is used.
1. I had trouble understanding the various cases in the reference code, and wanted to try an implementation that requires less logic / fewer cases by holding a `height` variable in the node in addition to `balance.` Because height is stored and updated in each node, getting the height of a subtree is an O(1) operation (not O(log n)).

### Traversals, callbacks, and lambdas
The AVL tree is a private member of the `StyleChecker` class, so the problem arises of how to give `StyleChecker` access to tree nodes, which should be private to the tree.

One possible solution is to create some kind of iterator, although this is not as straightforward as it would be in a linear data structure.

I've taken a different approach by creating a public `inOrder` function which accepts a callback function that is then called on the node when it is visited in order. (I did not need pre and post order, but equivalent public functions could have been created.) The code in `StyleChecker` uses C++ lambdas to create and pass the callback functions.




