#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie_node_t{
    char letter;
    int is_leaf;
    struct trie_node_t *children[26];
};

struct trie_node_t *create_trie_node(){
    struct trie_node_t *new_node = malloc(sizeof(struct trie_node_t));
    new_node->is_leaf = 0;
    new_node->letter = NULL;
    for(int i = 0; i < 26; i++){
        new_node->children[i] = NULL;
    }
    return new_node;
}

int insert_trie_node(struct trie_node_t *root, char *word){
    struct trie_node_t *tmp = root;
    int i;

    for(i = 0; i < strlen(word); i++){
        if(tmp->children[(word[i] - 'a')] == NULL){
            tmp->children[(word[i] - 'a')] = create_trie_node();
            tmp->children[(word[i] - 'a')]->letter = word[i];
        }
            tmp = tmp->children[(word[i] - 'a')];
    }
    tmp->is_leaf = 1;
    return 1;
}

void random_word(struct trie_node_t *root, int letters, char *word){
    struct trie_node_t *current = root;
    int random_index;
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < letters; i++){

        int not_null[26];
        int index_number = 0;

        for(int j = 0; j < 26; j++){

            if(current->children[j] != NULL){

                not_null[index_number] = j;
                index_number++;
            }
        }

        if(index_number > 0){

            random_index = (rand() % index_number);
            //printf("random index is %d\n", random_index);

            current = current->children[not_null[random_index]];
            //printf("za sega raboti\n");
            word[i] = current->letter;

        }

        else{
            word[i] = 'a' + (rand() % 26);
        }
    }
    return;
}

void shuffle(char *word, int letters){

    char temp;
    int rand_index;

    for(int i = 0; i < letters; i++){

        rand_index = (rand() % (letters - i)) + i;
        temp = word[i];
        word[i] = word[rand_index];
        word[rand_index] = temp;
    }

    return;
}

int main()
{
    struct trie_node_t *root = malloc(sizeof(struct trie_node_t));
    root = create_trie_node();
    int letters;
    printf("how many letters? ");
    scanf("%d", &letters);
    char word[letters];

    insert_trie_node(root, "screwdriver");
    insert_trie_node(root, "pen");
    insert_trie_node(root, "pencil");
    insert_trie_node(root, "turkey");
    insert_trie_node(root, "joseph");
    insert_trie_node(root, "calendar");
    insert_trie_node(root, "goodbye");
    insert_trie_node(root, "zebra");

    random_word(root, letters, word);
    shuffle(word, letters);

    for(int i = 0; i < letters; i++){
        printf("%c ", word[i]);
    }
}
