// hash table using linear open addressing and division
// implements dictionary methods other than erase

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include "hash.h" // mapping functions from K to nonnegative integer
#include "illegal.h"

template <class K, class E>
class hashTable
{
public:
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table; }

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    std::pair<const K, E> *find(const K &) const;
    void insert(const std::pair<const K, E> &);
    void output(std::ostream &out) const;

protected:
    int search(const K &) const;
    std::pair<const K, E> **table; // hash table
    myHash<K> hash;                // maps type K to nonnegative integer
    int dSize;                     // number of pairs in dictionary
    int divisor;                   // hash function divisor
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    // allocate and initialize hash table array
    table = new std::pair<const K, E> *[divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = nullptr;
}

template <class K, class E>
int hashTable<K, E>::search(const K &theKey) const
{ // Search an open addressed hash table for a pair with key theKey.
  // Return location of matching pair if found, otherwise return
  // location where a pair with key theKey may be inserted
  // provided the hash table is not full.

    int i = (int)hash(theKey) % divisor; // home bucket
    int j = i;                           // start at home bucket
    do
    {
        if (table[j] == nullptr || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor; // next bucket
    } while (j != i);          // returned to home bucket?

    return j; // table full
}

template <class K, class E>
std::pair<const K, E> *hashTable<K, E>::find(const K &theKey) const
{ // Return pointer to matching pair.
  // Return NULL if no matching pair.
    // search the table
    int b = search(theKey);

    // see if a match was found at table[b]
    if (table[b] == nullptr || table[b]->first != theKey)
        return nullptr; // no match

    return table[b]; // matching pair
}

template <class K, class E>
void hashTable<K, E>::insert(const std::pair<const K, E> &thePair)
{ // Insert thePair into the dictionary. Overwrite existing
  // pair, if any, with same key.
  // Throw hashTableFull exception in case table is full.
    // search the table for a matching pair
    int b = search(thePair.first);

    // check if matching pair found
    if (table[b] == nullptr)
    {
        // no matching pair and table not full
        table[b] = new std::pair<const K, E>(thePair);
        dSize++;
    }
    else
    { // check if duplicate or table full
        if (table[b]->first == thePair.first)
        { // duplicate, change table[b]->second
            table[b]->second = thePair.second;
        }
        else // table is full
            throw hashTableFull();
    }
}

template <class K, class E>
void hashTable<K, E>::output(std::ostream &out) const
{ // Insert the hash table into the stream out.
    for (int i = 0; i < divisor; i++)
        if (table[i] == nullptr)
            std::cout << "NULL" << std::endl;
        else
            std::cout << table[i]->first << " " << table[i]->second << std::endl;
}

// overload <<
template <class K, class E>
std::ostream &operator<<(std::ostream &out, const hashTable<K, E> &x)
{
    x.output(out);
    return out;
}

#endif
