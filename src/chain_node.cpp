#include <sstream>
#include "chain_node.h"

template<class T>
chain<T>::chain(int initialCapacity = 10) {
    if (initialCapacity < 1){
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList) {
    listSize = theList.listSize;
    if (listSize == 0){
        firstNode = nullptr;
        return;
    }
}