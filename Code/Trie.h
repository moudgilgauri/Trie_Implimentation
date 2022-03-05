#include <stdbool.h>

// Function to return an object of Trie , which is basically one Node of Trie. ( Time Complexity -> O(Child size) )
struct TrieNode *createNode(char);

// Function to assign meaning to a word entered in Trie dictionary. ( Time Complexity -> O(Meaning size) )
void assign_input(struct TrieNode *, char *);

// Function to insert a word with its meaning in Trie dictionary. ( Time Complexity -> O(Word size) )
void addWord(struct TrieNode * , char * , int , char *);

// Function to search a word in Trie dictionary. ( Time Complexity -> O(Word size) )
bool searchWord(struct TrieNode * , char * , int);

// Function to delete a word from Trie dictionary. ( Time Complexity -> O(Word size) )
void deleteWord(struct TrieNode * , char * , int);

// Helper Function to provide suggestions to auto-complete a prefix word from words in Trie dictionary. (Time Complexity -> near about O(Trie size x Words size) )
void autoComplete(struct TrieNode * , char *);

// Function to search the prefix word from Trie dictionary for auto-completing it. ( Time Complexity -> O(Word size) )
struct TrieNode *searchPrefix(struct TrieNode * , char * , int);

// Function to print all the suggestions for auto-completing a prefix word from words in Trie dictionary.  (Time Complexity -> near about O(Trie size x Words size) )
void printautocomplete(struct TrieNode * , char * , char * , int);

// Function to print meaning of a word present in Trie dictionary. ( Time Complexity -> O(Word size) )
void print_meaning(struct TrieNode * , char * , int);

// Helper Function to get all words with their meaning present in Trie dictionary. (Time Complexity -> near about O(Trie size x Words size) )
void get_trie(struct TrieNode *);

// Function to print all words with their meaning present in Trie dictionary. (Time Complexity -> near about O(Trie size x Words size) )
void print_all_words_with_meaning(struct TrieNode * , char * , int);



