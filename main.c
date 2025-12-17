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


void add_child(Node* parent, Node*child){
  if (!parent || !child) return;

  if (parent->type != NODE_DIR){
    printf("Error: Cannot add child to file '%s'\n", parent->name);
    return;
  }

  child->parent = parent;

  child->next = parent->children;
  parent->children = child;

}


void free_tree(Node* node){
  if (!node) return;
  Node* curr = node->children;
  while (curr != NULL){
    Node* next = curr->next;
    free_tree(curr);
    curr = next;
  }

  free(node);
  
}

int main(){
  Node* root = create_node("/", NODE_DIR);
  Node* home = create_node("home", NODE_DIR);
  Node* user = create_node("user", NODE_DIR);
  Node* file = create_node("notes.txt", NODE_FILE);
  Node* file_2 = create_node("games.txt", NODE_FILE);
  Node* file_3 = create_node("secret.txt", NODE_FILE);

  add_child(root, home);
  add_child(home, user);
  add_child(user, file);
  add_child(user, file_2);
  add_child(user, file_3);

  printf("root -> %s\n", root->children->name);
  printf("home -> %s\n", home->children->name);

  // temporary pointer
  Node *curr = user->children;
  
  while(curr != NULL){
    printf("user -> %s\n", curr->name);
    curr = curr->next;
  }

  free_tree(root);
  return 0;
}
