#include <string>

#include "hashFunctions.h"

using std::string;

int hash(int value, int range) {
    // value could be out of range, use mod to put back into range
    int toReturn = value % range;
    if (toReturn < 0) {
        // add range to ensure positive hash value
        toReturn += range;
    }
    return toReturn;
}

int hash(string value, int range) {
    int hash_value = 0;
    for (int i = 0; i < value.length(); i++) {
        hash_value *= 31;       // prime number helps to avoid hash collisions
        hash_value += value[i];
    }

    // now, compress down to range
    int toReturn = hash_value % range;
    if (toReturn < 0) {
        toReturn += range;
    }
    return toReturn;
}
