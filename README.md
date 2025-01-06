For this assignment, you will implement 2 features for the file system:
1) A ranged search that will search a FileAVL object for files within a given size range. In the code that's already provided to you, the FileAVL class is already implemented as an AVL tree of File objects, ordered by size.
You will implement this as a method of the FileAVL class, and you will write that method in solution.cpp.
For context, a data structure like this would have to be maintained in addition to the actual file system specifically to support efficient searches on file size. Note that FileAVL Node struct contains only File pointers, not actual File objects, so it can simply point to the same File objects as the actual file system.
2) The implementation of a prefix trie using for efficient prefix search. This trie differs from a standard trie in that at each node, it will hold all files whose names begin with the prefix defined by the path leading to that node. This is a significant trade-off of space for time.
In struct FileTrieNode:
- stored is the character that leads to the node. It is not actually needed, but it's useful for debugging.
- matching is the set of pointers to Files whose filenames start with the prefix corresponding to the path leading to the node.
- next is the set of the node's child pointers. Each node can have a child for each letter, so we use a map to efficiently map each letter to the corresponding child node.
Additional specifications:
- The root, representing the empty string (0 characters), should hold a pointer to every File.
- The search should support a filename and extension, e.g. importantstuff.doc
- The actual file system is not part of this project, so there are no file paths or directories, just filenames with extensions.
- Characters allowed are a-z, 0-9, and . (period).
- The search should be case-insensitive.
You must implement all methods of FileTrie except for the constructor, which is just a default constructor. You can find the FileTrie class in FileTrie.hpp, but you must implement the methods in solution.cpp.
All of your code will be written in solution.cpp.

Update for extra credit:
For extra credit, you must:
1) Add a compiler directive "USE_VECTOR" at the top of your submitted FileTrie.hpp file:
#ifndef USE_VECTOR
#define USE_VECTOR
#endif
2) Implement your own destructor for the FileTrie class within solution.cpp
If USE_VECTOR is not defined, the destructor provided by us will be used, which is the destructor for the map implementation.

- [x] Project
- [x] Extra Credit 
