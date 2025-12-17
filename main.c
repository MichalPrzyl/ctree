#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
  NODE_FILE,
  NODE_DIR
} NodeType;


typedef struct Node{
  char name[64];
  NodeType type;

  struct Node* parent;

  struct Node* children;
  struct Node* next;
} Node;


Node* create_node(const char* name, NodeType type){
  Node* node = malloc (sizeof(Node));
  if (!node){
    perror("malloc problem");
    exit(1);
  }

  strncpy(node->name, name, sizeof(node->name));
  node->name[sizeof(node->name) - 1] = '\0';

  node->type = type;
  node->parent = NULL;
  node->children = NULL;
  node->next = NULL;

  return node;
}

int main(){
  Node *root = create_node("/", NODE_DIR);

  printf("root: %s\n", root->name);
  free(root);
  return 0;
}
