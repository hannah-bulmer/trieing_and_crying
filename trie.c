#include <stdlib.h>
#include "trie.h"
#include <stdio.h>
#include <string.h>


// creates trie/trienode
struct trienode* trienode_create(void) {
  struct trienode *node = malloc(sizeof (struct trienode));
  node->word_end = false;
  for (int i = 0; i < 26; i ++) {
    node->children[i] = NULL;
  }
  return node;
}


struct trie *trie_create(void) {
  struct trie *t = malloc(sizeof (struct trie));
  t->root = trienode_create();
  return t;
}

// adds trie
void trie_add_node(const char *s, struct trienode *node) {
  for (int i = 0; s[i] != 0; i ++) {
    int loc = s[i] - 'a';
    if (node->children[loc] == NULL) {
      node->children[loc] = trienode_create();
    }
    node = node->children[loc];
  }
  node->word_end = true;
}


void trie_add(const char *s, struct trie *t) {
  trie_add_node(s, t->root);
}


// removes trie
void trienode_destroy (struct trienode *node);


void trie_remove_node (const char *s, struct trienode *node) {
  struct trienode *last_fork = node;
  for (int i = 0; s[i] != 0; i ++) {
    int loc = s[i] - 'a';
    for (int j = 0; j < 26; j ++) {
      if (node->children[j] != NULL && j != loc)
        last_fork = node->children[loc];
    }
    if (node->children[loc]->word_end) break;
  }
  trienode_destroy(last_fork);
  // go through trie
  // remember each last fork
  // go down to leaf
  // when reached leaf, call trienode_destroy() on the
  // last fork
}


void trie_remove(const char *s, struct trie *t) {
  trie_remove_node(s, t->root);
}


// trie_lookup
bool trienode_lookup(const char *s, const struct trienode *node) {
  for (int i = 0; s[i] != 0; i ++) {
    int loc = s[i] - 'a';
    if (node->children[loc] == NULL) {
      return false;
    }
    node = node->children[loc];
  }
  return (node->word_end);
}


bool trie_lookup(const char *s, const struct trie *t) {
  return trienode_lookup(s, t->root);
}


void trienode_destroy (struct trienode *node) {
  for (int i = 0; i < 26; i ++) {
    if (node->children[i] != NULL) {
      trienode_destroy(node->children[i]);
    }
  }
  free(node);
}

void trie_destroy(struct trie *t) {
  trienode_destroy(t->root);
  free(t);
}

//COUNTING
void trie_counter(const struct trienode *node, int *counter) {
  if (node->word_end) (*counter) ++;
  for (int i = 0; i < 26;i ++) {
    if (node->children[i] != NULL) {
      trie_counter(node->children[i], counter);
    }
  }
}


int trie_count (const struct trie * t) {
  int counter = 0;
  trie_counter(t->root, &counter);
  return counter;
}
// COUNTING COMPLETE



void trie_print(const struct trie *t) {

}


void tnode_to_aos(const struct trienode *tn, int loc,
                  char *str, int * counter, char ** aos) {
    if (tn->word_end == true){
    str[loc] = 0;
    char *word= malloc((loc+1) * sizeof(char));
    strcpy(word,str);
    aos[*counter] = word;
    ++ *counter;
    int continues = 0;
    for (int i = 0; i < 26; i++){
        if (tn->children[i] != NULL){
            str[loc] = 'a' + i;
            tnode_to_aos(tn->children[i], loc + 1, str, counter, aos);
        }
      }
  }
}

int trie_height(const struct trienode *node) {
  if (node == NULL) return 0;
    int height_so_far = 0;
    for (int i = 0; i < 26; ++ i){
        int challenger = trie_height(node->children[i]);
        if (challenger > height_so_far) {
            height_so_far = challenger;
        }
    }
    return height_so_far + 1;
}

char **trie_to_aos(const struct trie *t) {
  iif (t->root == NULL) return NULL;
    int numwords = trie_count(t);
    char ** aos = malloc(numwords * sizeof (char *));
    int maxlen = trie_height(t->root);
    int counter = 0;
    char * str = malloc((maxlen+1)*sizeof(char));
    tnode_to_aos(t->root, 0, str, &counter, aos);
    free(str);
    return aos;
}
