#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_WORDS (354935)
#define INPUT_WORD_SIZE (45)

void read_trie(char *fill){

  FILE *file = fopen("../trie_file.txt", "r");
  char word[INPUT_WORD_SIZE];

  int word_count = 0;

  fill[word_count] = malloc(INPUT_WORD_SIZE);

  while (fgets(fill[word_count], INPUT_WORD_SIZE, file) != NULL)
  {
      fputs(fill[word_count], stdout);
      //fputs()
      word_count++;
      fill[word_count] = malloc(INPUT_WORD_SIZE);
  }

  for (int i = 0; i < NUMBER_OF_WORDS; i++)
  {
      if(debug(fill[i]) != 1){
          break;
      }
      printf("\n%s\n", fill[i]);

  }

}

int main(){

  char *read_trie_from_file[INPUT_WORD_SIZE];
  read_trie(read_trie_from_file);
}
