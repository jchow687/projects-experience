Part A:
A set is an Abstract Data Type (ADT) that maintains an unordered collection of (key, item) pairs; any given key can only occur in the set once. 
It starts out empty and grows as the user inserts new (key, item) pairs. The user can retrieve items by specifying a key, but cannot remove or update pairs. 
Items are distinguished by their unique key.

Compile Part A with : gcc -Wall -Wextra set.c test_set.c -o test_


Part B:
A hash table is a set of (key, item) pairs. It acts just like the set from the user's perspective, but under the hood is much more efficient for large collections. 

Your hashtable.c should implement a set of (key, item) pairs of type (char*, void*), 
and export exactly the functions in the provided hashtable.h file. Your hashtable should make use of the set ADT in its implementation, 
an easy way to do this would be to create an array of sets. Whenever a new item is added, it is then sorted into one of the sets. 
You can choose any hashing algorithm you like, since our keys will always be strings an easy one is treating the key as an integer and using modulus.

Compile Part B with: gcc -Wall -Wextra set.c hashtable.c test_hashtable.c -o test_hashtable

Part C:
An LRU Cache is an ADT that has limited capacity and will discard the least recently used item when in need of storage space. 
You will need to keep track of the number of elements in the LRU, and what the max is. 
When asked to insert an element into a "full" LRU, remove the least recently used item and then insert the new one. 
An element is "used" when it is inserted or accessed through the find method.

Compile Part C with: gcc -Wall -Wextra -g set.c hashtable.c lru.c test_LRU.c -o test_lru && ./test_lru
 
An additonal function I have added is remove_LRU.

Context: "void remove_lru(lru_t* set)"
the purpose of the function was to remove the least recently used node in the cache if the cache was ever full
and exceeded the capacity.

-Joshua Chow / Student ID: 1971403
