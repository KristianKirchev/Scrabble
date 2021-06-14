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

int longest_word = 0;

int insert_trie_node(struct trie_node_t *root, char *word){
    struct trie_node_t *tmp = root;

    if(sizeof(word) - 1 > longest_word){
      longest_word = sizeof(word);
    }

    int i;

    for(i = 0; i < strlen(word); i++){
        //printf("%c\n", word[i]);
        if(tmp->children[(word[i] - 'a')] == NULL){
            tmp->children[(word[i] - 'a')] = create_trie_node();
            tmp->children[(word[i] - 'a')]->letter = word[i];
        }
            tmp = tmp->children[(word[i] - 'a')];
    }
    tmp->is_leaf = 1;
    return 1;
}

void print_level(struct trie_node_t* root, int level){
    if (root == NULL){
        return;
    }
    if (level == 1){
        if(root->letter == NULL){
            printf("0 ");
        }
        printf("%c ", root->letter);

    }
    else{
        int i;
        for(i = 0; i < 26; i++){
            print_level(root->children[i], level-1);
        }
    }
}

void print_trie(struct trie_node_t *root){
    if(root == NULL){
        return;
    }
    int i;
    for(i = 0; i < 8; i++){
        print_level(root, i);
        printf("\n");
    }
    return;
}

int main()
{
    struct trie_node_t *root = malloc(sizeof(struct trie_node_t));
    root = create_trie_node();
    insert_trie_node(root, "apple");
    insert_trie_node(root, "applew");
    insert_trie_node(root, "and");
    insert_trie_node(root, "ant");
    insert_trie_node(root, "bike");
    printf("Trie:\n");
    print_trie(root);

    printf("\n");
    return 0;
}
