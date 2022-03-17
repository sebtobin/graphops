# Polymorphic Unweighted Directional Graph Implementation using a Hash Table in C 

Polymorphic unweighted directional graph implementation in C with create and insert node operations. Each node in the graph can store a pointer to any structure. The graph structure uses a hashtable to store all nodes, allowing O(1) insert and O(1) lookup to retrieve the most recently created node containing the same data. Built such that the insert edge and create node functions do not need to be called directly by the program using the library, thought insert edge may be used for scenarios where edges need to be inserted without inserting any new node.

Written by Sebastian Tobin Couzens