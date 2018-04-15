#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

int main(void) {
  struct trie *t = trie_create();
  assert(t);
  char command[11];
  char s[100];
  while (scanf("%s", command) == 1 && strcmp(command, "exit")) {
    if (!strcmp(command,"add")) {
      assert(scanf("%s", s) == 1);
      trie_add(s, t);
    } else if (!strcmp(command, "remove")) {
      assert(scanf("%s", s) == 1);
      printf("Removing %s\n", s);
      trie_remove(s, t);
    } else if (!strcmp(command, "find")) {
      assert(scanf("%s", s) == 1);
      printf("Searching for %s\n", s);
      if (trie_lookup(s,t) == 0) printf("Not found\n");
      else printf("Found\n");
    } else if (!strcmp(command, "print")) {
      trie_print(t);
    } else if (!strcmp(command, "sort")) {
      //
    } else if (!strcmp(command, "count")) {
      printf("There are %d words in the trie\n", trie_count(t));
    } else {
      printf("unexpected command: %s\n", command);
      break;
    }
  }
  trie_destroy(t);
  return(0);
}
