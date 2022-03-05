#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Trie.h"

void meaning_input(char *str)
{
    int len = 0;
    char ch;
    ch = getchar();

    while(ch = getchar())
    {
        if(ch == '\n')
	 {
	    str[len] = '\0';
	    break;
	 }
	else
	 str[len++] = ch;

    }
}

void word_input(char *str)
{
    scanf("%s" , str);
}


int main()
{
    // Creating Root Node for Trie.
    struct TrieNode *root = createNode('\0');


    printf("Enter 1. to insert a word. \nEnter 2. to search a word. \nEnter 3. to delete a word. \n");
    printf("Enter 4. to auto-complete a word.\nEnter 5. to print meaning of a word.\n");




    while(1)
    {
        printf("\nEnter your choice of operation : \n");
        int choice;
        scanf("%d" , &choice);

	// switch case.
        switch(choice)
        {

            case 1:
            {
                char word[256];
                char meaning[1000];
                printf("Enter a word to add \n");
                word_input(word);

                printf("Enter its meaning \n");
                meaning_input(meaning);

                addWord(root , word , 0 , meaning);
                break;
            }


            case 2:
            {
                char word[256];
                printf("Enter a word to search. \n");
                word_input(word);

                bool find = searchWord(root , word , 0);
                if(find == true)
                {
                    printf("'%s' is present in your Dictionary. \n" , word);
                }
                else
                {
                    printf(" '%s' is not added in  your Dictionary. \n" , word);
                }
                break;
            }

	    // case 3 to delete a word.
            case 3:
            {
                char word[256];
                printf("Enter the word you want to delete. \n");
                word_input(word);

                deleteWord(root , word , 0);
                break;
            }

	    // case 4 to print suggestions for the word to be auto-completed.
            case 4:
            {
                char word[256];
                printf("Enter a word to auto-complete. \n");
                word_input(word);

                autoComplete(root , word);
                break;
            }

	    // case 5 to print meaning of a word.
            case 5:
            {
                char word[256];
                printf("Enter the word \n");
                word_input(word);

                print_meaning(root , word , 0);
                break;
            }

            // case 6 to print all words with meaning.
            case 6:
            {
                get_trie(root);
                break;
            }

	    // default case to exit.
            default:
            {
                printf("Exiting! \n");

		// goto statement to go out of while loop.
                goto EndWhile;
            }
        }
    }


    EndWhile: ;

    return 0;
}
