#pragma once

#include "linearDictionary.h"
#include "adts/dictionary.h"

template <typename K, typename V> class HashTable : public Dictionary<K, V> {
  public:
    /**
     * Creates a new HashTable with a maximum load factor of 0.75.
     */
    HashTable();

    /**
     * Creates a new HashTable.
     * @param maxLoadFactor The maximum load factor which will be permitted
     *                      before this hash table changes its capacity.
     */
    HashTable(float maxLoadFactor);
    /**
     * Cleans up this HashTable.
     */
    ~HashTable();

    /**
     * Dictionary ADT Methods
     */
    int getSize();
    bool isEmpty();
    void insert(K key, V value);
    void update(K key, V value);
    V get(K key);
    bool contains(K key);
    void remove(K key);
    vector<K> getKeys();
    vector<pair<K, V>> getItems();

  private:
    /**
     * Doubles the capacity of the table in order to reduce the load factor.
     * All items should be rehashed into the new table
     */
    void expandCapacity();

    int size;
    int capacity;
    LinearDictionary<K, V>* table;
    float maxLoadFactor;
};

#include "hashTable-inl.h"
