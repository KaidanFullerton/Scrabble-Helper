#pragma once

#include <string>

using std::string;

// Header file for overloaded hash functions used in hashTable implementation

/**
 * Generates a hash code for an integer.
 * @param value The integer to hash.
 * @param range The range of integers to hash to.
 * @return The hash of the provided integer.
 */
int hash(int value, int range);

/**
 * Generates a hash code for a string.
 * @param value The string to hash.
 * @param range The range of integers to hash to.
 * @return The hash of the provided string.
 */
int hash(string value, int range);

/**
 * Future:
 * Add hash functions for class objects as needed
 */