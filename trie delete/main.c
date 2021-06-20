#include <stdio.h>
#include <stdlib.h>

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
        //printf("%c\n", word[i]);
        if(word[i] >= 'a' && word[i] <= 'z'){

            if(tmp->children[(word[i] - 'a')] == NULL){
                tmp->children[(word[i] - 'a')] = create_trie_node();
                tmp->children[(word[i] - 'a')]->letter = word[i];
            }
            tmp = tmp->children[(word[i] - 'a')];
        }
    }
    tmp->is_leaf = 1;
    return 1;
}

int has_Child(struct trie_node_t *root){

    for(int i = 0; i < 26; i++){

        if (root->children[i] != NULL){
            return 1;
        }
    }

    return 0;
}

void delete_Trie(struct trie_node_t *root){

    int not_null[26];
    int index_number = 0;

    for(int i = 0; i < 26; i++){

        if(root->children[i] != NULL){

            not_null[index_number] = i;
            index_number++;
        }
    }

    if(index_number > 0){
        for(int i = 0; i < index_number; i++){
            delete_Trie(root->children[not_null[i]]);
        }
    }

    //printf("root = %c\n", root->letter);
    free(root);
    root = NULL;
    return;
}

void is_Empty(struct trie_node_t *trie){

    for(int i = 0; i < 26; i++){
        if(trie->children[i] != NULL){
            printf("It's not empty\n");
            return;
        }
    }
    printf("It's empty\n");
    return;
}

int main()
{
    struct trie_node_t *root = malloc(sizeof(struct trie_node_t));
    root = create_trie_node();

    is_Empty(root);

    insert_trie_node(root, "one");
    insert_trie_node(root, "two");
    insert_trie_node(root, "three");
    insert_trie_node(root, "four");
    insert_trie_node(root, "five");


    is_Empty(root);
    delete_Trie(root);
    is_Empty(root);

    return 0;
}
