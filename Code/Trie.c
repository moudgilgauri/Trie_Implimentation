#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Trie.h"

#define childnode 256

struct TrieNode
{
    char word;
    struct TrieNode *children[childnode];
    bool isEnd;
    char *meaning;
};
struct TrieNode *createNode(char w)
{
    struct TrieNode *root = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    root->isEnd = false;
    root->word = w;
    root->meaning = (char *)malloc(1000*sizeof(char));

    for(int i =0;i<childnode;i++)
    {
        root->children[i] = NULL;
    }
    return root;
};


void assign_meaning(struct TrieNode *root , char *mean)
{
    int l = strlen(mean);
    int i = 0;
    for(i = 0; i < l; i++)
    {
        root->meaning[i] = mean[i];
    }

    root->meaning[i] = '\0';
}



void addWord(struct TrieNode *root , char *str , int pos , char *mean)
{
    /* At the end of string make that node's isEnd = true representing that the word ends at that node
    and assign meaning to that last node.  */
    if(str[pos] == '\0')
    {

        if(root->isEnd == true)
        {
            assign_meaning(root , mean);
            printf("Meaning for word '%s' Added.\n" , str);
        }
        else
        {
            root->isEnd = true;
            assign_meaning(root , mean);
            printf("'%s' added in your dictionary along with its meaning. \n" , str);
        }
        return;
    }


    int i = str[pos];

    // making a child node.
    struct TrieNode *child;

    // if root already has a child at i then put that node in child.
    if(root->children[i] != NULL)
    {
        child = root->children[i];
    }

    /* else create a new node for child by calling createNode function
    and put that node in root's children array. */
    else
    {
        child = createNode(str[pos]);
        root->children[i] = child;
    }

    // call addWord recursively with child as next root , and pos as pos+1 to insert next character of word.
    addWord(child , str , pos + 1 , mean);
}


bool searchWord(struct TrieNode *root , char *str , int pos)
{
    // if reached at end of string.
    if(str[pos] == '\0')
    {
        // if isEnd for that node is true means that a words ends there ,hence return true.
        if(root->isEnd == true)
        {
            return true;
        }

        // else return false.
        else
        {
            return false;
        }
    }

    // store ascii value of current character in i.
    int i = str[pos];

    // if root has no child at i then return false.
    if(root->children[i] == NULL)
    {
        return false;
    }

    // else make a child node and store root's child at i in child node
    struct TrieNode *child;
    child = root->children[i];

    /* calling searchWord recursively , passing that child node as next root and pos as pos +1 to search for next character.  */
    return searchWord(child , str , pos + 1);
}

void deleteWord(struct TrieNode *root , char *str , int pos)
{

    if(str[pos] == '\0')
    {
        if(root->isEnd == true)
        {
            printf("'%s' deleted from your dictionary. \n" , str);
            root->isEnd = false;
        }
        else
        {
            printf("There is no such word present in the dictionary to be deleted. \n");
        }
	return;
    }


    struct TrieNode *child;
    int i = str[pos];
    if(root->children[i] != NULL)
    {
        child = root->children[i];
    }
    else
    {
        printf("There is no such word present in the dictionary to be deleted. \n");
        return;
    }
    deleteWord(child , str , pos + 1);

    if(child->isEnd == false)
    {
        for(int i = 0 ; i < childnode ; i++)
        {
            if(child->children[i] != NULL)
            {
                return;
            }
        }

        free(child);
        root->children[i] = NULL;
        return;
    }

}

struct TrieNode *searchPrefix(struct TrieNode *root , char *str , int pos)
{
    // if reached at end of word then return root which is node of last character for that word.
    if(str[pos] == '\0')
    {
        printf("Suggestions to auto-complete '%s' are : \n" , str);
        return root;
    }

    // store ascii value of current character in index.
    int index = str[pos];

    // if root has no child at that index then return NULL.
    if(root->children[index] == NULL)
    {
        printf("No auto-complete '%s' \n found" , str);
        return NULL;
    }

    // make a child node and assign root's child at that index to it.
    struct TrieNode *child = root->children[index];

    /* calling searchPrefix function recursively with child node as next root and
    pos as pos+1 to search for next character. */
    struct TrieNode *result = searchPrefix(child , str , pos + 1);

    // returning the node of last character of the prefix which is matched.
    return result;
}

void printautocomplete(struct TrieNode *root , char *str , char *ans , int fill)
{
    // if root's isEnd is true means that a word ends there.
    if(root->isEnd == true)
    {
        // put NULL character at end of completed word.
        ans[fill] = '\0';

        // print the prefix and the completed part of word.
        printf("%s%s \n" , str , ans);
    }

    // iterate over all the children of root.
    for(int i = 0 ; i < childnode ; i++)
    {
        // if root has a child at a particular index.
        if(root->children[i] != NULL)
        {
            // fill that child's data in ans string to auto complete it.
            ans[fill] = root->children[i]->word;

            /* recursively call printautocomplete function with child node at that particular
            index as root , updated ans string and fill=fill+1 to fill next character. */
            printautocomplete(root->children[i] , str , ans , fill + 1);

            /* put NULL character at fill position as while backtracking the ans string will
            show the updated part as strings in C are passed by reference , hence to make it original
            again put NULL character at that fill index . */
            ans[fill] = '\0';
        }
    }
}
void autoComplete(struct TrieNode *root , char *character)
{
    /* calling searchPrefix function to search for the prefix word. It returns
    node of last character of the prefix if it is present and NULL if it is not present */
    struct TrieNode *temp = searchPrefix(root , character , 0);

    // making an empty string.
    char str[childnode];

    // if temp is not NULL then pass temp as root in printautocomplete function to autoComplete the word.
    if(temp != NULL)
    {
        printautocomplete(temp , character , str , 0);
    }

}


void print_meaning(struct TrieNode *root , char *str , int pos)
{
    // if reached at end of word then print its meaning.
    if(str[pos] == '\0')
    {
	// if root's isEnd is true means that word is present , hence print its meaning.
        if(root->isEnd == true)
        {
            printf("The meaning of '%s' : %s \n" , str , root->meaning);
        }

	// else that word is not present.
        else
        {
            printf("There is no such word present in your dictionary \n");
        }
        return;
    }

    // store ascii value of current character in index.
    int index = str[pos];

    // if root has no child at that index then just return.
    if(root->children[index] == NULL)
    {
        printf("There is no such word present in your Trie dictionary \n");
        return;
    }

    // make a child node and assign root's child at that index to it.
    struct TrieNode *child = root->children[index];

    /* recursively call print_meaning function with child node as root and pos=pos+1 to check
    if next character of word whose meaning is to print is present in Trie or not. */
    print_meaning(child , str , pos + 1);
}
void print_all_words_with_meaning(struct TrieNode *root , char *str , int pos)
{
    // if isEnd of root is true means a word ends at this node.
    if(root->isEnd == true)
    {
        // put NULL character at end of current string.
        str[pos] = '\0';

        // print that string and its meaning.
        printf("Word : %s , Meaning : %s\n" , str , root->meaning);
    }

    // iterate over all the children of root.
    for(int i = 0 ; i < childnode ; i++)
    {
        // if root has a child at that particular index.
        if(root->children[i] != NULL)
        {
            // store that child's data in str string.
            str[pos] = root->children[i]->word;

            /* recursively call print_all_words_with_meaning function with child node at that particular
            index as root , updated str string and pos=pos+1 to fill next character. */
            print_all_words_with_meaning(root->children[i] , str , pos + 1);

            /* put NULL character at pos position as while backtracking the str string will
            show the updated part as strings in C are passed by reference , hence to make it original
            again put NULL character at that pos index . */
            str[pos] = '\0';
        }
    }
}


void get_trie(struct TrieNode *root)
{
    // create an empty string.
    char str[childnode];

    // to check if Trie dictionary is empty or not , check if root has atleast one child or not.
    bool isEmpty = true;
    for(int i = 0 ; i < childnode ; i++)
    {
        if(root->children[i] != NULL)
        {
            isEmpty = false;
            break;
        }
    }

    // if Trie dictionary is not empty.
    if(!isEmpty)
    {
        printf("All words with their meaning are : \n");
        // call print_all_words_with_meaning function.
        print_all_words_with_meaning(root, str , 0);
    }

    // else if its empty.
    else
    {
        printf("Your Dictionary is empty \n");
    }

    return;
}

