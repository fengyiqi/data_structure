// functions to convert from type K to nonnegative integer
// derived from similar classes in SGI STL


#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>

template <class K> class myHash;

template<>
class myHash<std::string>
{
   public:
      size_t operator()(const std::string theKey) const
      {// Convert theKey to a nonnegative integer.
         unsigned long hashValue = 0; 
         int length = (int) theKey.length();
         for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);
    
         return size_t(hashValue);
      }
};

template<>
class myHash<int>
{
   public:
      size_t operator()(const int theKey) const
      {return size_t(theKey);}
};

template<>
class myHash<long>
{
   public:
      size_t operator()(const long theKey) const
      {return size_t(theKey);}
};

#endif
