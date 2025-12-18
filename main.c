#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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

bool check_if_children_is_valid(Node* pwd, Node* child){
  return true;
}

Node* find_child(Node* dir, const char* name){
  if (dir->type != NODE_DIR) return NULL;
  Node *curr = dir->children;
  while(curr){
    if(strcmp(curr->name, name) == 0){
      return curr;
    }
    curr = curr->next;
  }
}



Node* try_to_change_directory(char *target, Node* pwd){
  Node *found = find_child(pwd, target);
  if (found != NULL){
    return found;
  }
  else{
    return NULL;
  }
}


void get_all_children(Node* pwd){
  //printf("getting all children\n");
  Node *temporary = pwd->children;
  while (temporary != NULL){
    printf("%s\n", temporary->name);
    temporary = temporary->next;
  }
}

void get_pwd_path(Node* pwd, char *path, size_t size){
  Node *curr = pwd;
  const char *list[30];
  int count = 0;
  
  while (curr->parent){
    list[count] = curr->name;
    //printf("adding %s to list\n", curr->parent->name);
    count++;
    curr = curr->parent;
  }

  // for(int i =0; i < count; i++){
  //   printf("list[count%d]: %s\n", i, list[i]);
  // }

  // show whole list...
  //printf("--------------\n");
  //for(int i = 0; i < count; i++){
  //  printf("trying to read from i=%d\n", i);
  //  printf("+list[%d]: %s+\n", i, list[i]);
  //}
  //printf("--------------\n");


  
  // trzeba to policzyć jakoś
  //char whole_path[1024] = {0};
  path[0] = '\0';
  strcat(path, "/");
  
  for(int i = count -1; i >= 0; i--){
    strcat(path, list[i]);
    strcat(path, "/");
    //printf("Adding '%s' to path\n", list[i]);
  }
 

/*
/home/user
pwd = user
*/
      
}

int main(){
  Node* root = create_node("/", NODE_DIR);
  Node* home = create_node("home", NODE_DIR);
  Node* user = create_node("user", NODE_DIR);
  Node* file = create_node("notes.txt", NODE_FILE);
  Node* file_2 = create_node("games.txt", NODE_FILE);
  Node* file_3 = create_node("secret.txt", NODE_FILE);
  Node* pwd = root;
  //Node *pwd = malloc

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
  
  printf("Starting program...\n");
  char cmd[256];
  while(1){
    fgets(cmd, sizeof(cmd), stdin);
    //printf("entered cmd: %s\n", cmd);
    if (strcmp(cmd, "pwd\n") == 0){
      printf("%s\n", pwd->name);
    }
    if (strcmp(cmd, "whoami\n") == 0){
      printf("j0ker\n");
    }
    if (strcmp(cmd, "ls\n") == 0){
      get_all_children(pwd);
    }
    if (strncmp(cmd, "cd", 2) == 0){
      //printf("cmd: %s\n", cmd);
      char *children_string = cmd + 3;
      cmd[strcspn(cmd, "\n")] = '\0';

      Node *temp_again = NULL;
      if (strcmp(children_string, "..") == 0){
        temp_again = pwd->parent;
      }
      else{
	temp_again = try_to_change_directory(children_string, pwd);
      }
      
      if (temp_again == NULL){
	//printf("temp again is null");
      }
      else{
	//printf("temp again is not null");
	pwd = temp_again;
      }
    }
    char path[1024];
    get_pwd_path(pwd, path, sizeof(path));
    
       
    printf("%s $ ", path);
    //printf("path is: %s\n ", path);
  }

  free_tree(root);
  return 0;
}
