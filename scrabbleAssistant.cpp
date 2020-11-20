#include "scrabbleAssistant.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

ScrabbleAssistant::ScrabbleAssistant(vector<string> words) {
  
  int vecSize = words.size(); int bucket;
  string key;
  vector<string> temp;

  for(int i = 0; i < vecSize; i++){
    // word enters our main dictionary hash table normally
    hashTable.insert(words[i], words[i]);
    
    // word is then put into alphabetical order for our anagram table
    key = sortLetters(words[i]);

    // if the alphabetized string isn't already in the anagram table, we
    // create a vector containing it and insert the word into the table
    if(!anagramTable.contains(key)){
      vector<string> anagram = {words[i]};
      anagramTable.insert(key, anagram);
    }
    // if the alphabetized string is in the table, we grab the vector pertaining
    // to that string and insert the word into the vector
    else{
      temp = anagramTable.get(key);
      temp.push_back(words[i]);
      anagramTable.update(key, temp);
    }
  }
}

ScrabbleAssistant::~ScrabbleAssistant() {
  // Empty since no dynamic memory
}

bool ScrabbleAssistant::spellCheck(string word) {
  return hashTable.contains(word);
}

vector<string> ScrabbleAssistant::anagramsOf(string letters) {
  // checking for anagrams consist of comparing the alphabetized string of
  // letters passed into the fucnction with the alphabetized keys in our anagramTable
  string key = sortLetters(letters);
  if(anagramTable.contains(key)){
    return anagramTable.get(key);
  }
  // if there is no key found, we return a empty vector to the caller
  return vector<string> {};
}

vector<string> ScrabbleAssistant::findWords(string letters) {
  vector<string> powerSet = stringPowerSet(letters);
  vector<string> legalWords; vector<string> anagrams;
  int vecSize = powerSet.size();
  
  // go through each word in the powerset and compile a vector containing
  // all possible anagrams from the powerset words
  for(int i = 0; i < vecSize; i++){
    anagrams = anagramsOf(powerSet[i]);
    legalWords.insert(end(legalWords), begin(anagrams), end(anagrams));
  }
  // once we have our vector of all possible legal words, we remove duplicates
  legalWords = removeDuplicates(legalWords);
  return legalWords;

}


vector<string> stringPowerSet(string letters){
  vector<string> result;
  // base case: return empty set if letters is empty
  if(letters == ""){
    result.push_back("");
    return result;
  }

  char firstChar = letters[0];
  string sub = letters.substr(1);

  // recursive case: find subset of last n-1 elements in set
  vector<string> smallerResult = stringPowerSet(sub);

  for(int i = 0; i < smallerResult.size(); i++){
      result.push_back(smallerResult[i]); // recursive results
      result.push_back(firstChar+smallerResult[i]); // append first element
  }
  return result;
}


string ScrabbleAssistant::sortLetters(string s){

  sort(s.begin(), s.end());
  
  return s;
}


vector<string> ScrabbleAssistant::removeDuplicates(vector<string> words){
  vector<string> ret; int vecSize = words.size();
  HashTable<string, string> noDuplicates;
  // loop through the vector and if the word is not a key within our table,
  // add it to the table. This will remove all duplicates from the vector
  for(int i = 0; i < vecSize; i++){
    if(!noDuplicates.contains(words[i])){
      noDuplicates.insert(words[i], words[i]);
    }
  }

  ret = noDuplicates.getKeys();
  return ret;
}
