#include <stdio.h>
#include <stdlib.h>

// struct for each node of list
struct node {
  int data;
  struct node* next;
};

// function returns pointer to newly created node with given data
struct node* create_node(int data) {
  struct node* new_node = malloc(sizeof(struct node));
  new_node->next = 0;
  new_node->data = data;
  return new_node;
}

// function prints linked list element by element
void print_list(struct node* head) {
  while (head->next != 0) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("%d\n", head->data);
}

// function adds a new node after given predecessor
struct node* insert_node(struct node* predecessor, struct node* new_node) {
  // if predecessor already has next element, we should reassign it to new node
  if (predecessor->next != 0) new_node->next = predecessor->next;
  predecessor->next = new_node;
}

// function removes node given by pointer from list by searching
int delete_node(struct node* head, struct node* to_delete) {
  while (head->next != to_delete && head->next != 0) {
    head = head->next;
  }
  head->next = to_delete->next;
  int to_return = to_delete->data;
  free(to_delete);
  return to_return;
}

// function removes node given by data from list by searching
int delete_node_value(struct node* head, int data) {
  struct node* cur;
  while (cur->data != data && cur->next != 0) {
    cur = cur->next;
  }
  if (cur->data == data) return delete_node(head, cur);
  return 0;
}

int main() {
  struct node* linked_list = create_node(1);

  struct node* el = create_node(10);
  struct node* el1 = create_node(100);
  struct node* el2 = create_node(1000);
  struct node* el3 = create_node(10000);
  struct node* el4 = create_node(100000);

  insert_node(linked_list, el);  // 1 -> 10
  insert_node(el, el1);          // 1 -> 10 -> 100
  insert_node(el, el2);          // 1 -> 10 -> 1000 -> 100
  insert_node(el2, el3);         // 1 -> 10 -> 1000 -> 10000 -> 100
  insert_node(el2, el4);         // 1 -> 10 -> 1000 -> 100000 -> 10000 -> 100

  delete_node_value(linked_list,
                    100000);  // 1 -> 10 -> 1000 -> 10000 -> 100

  delete_node(linked_list, el);  // 1 -> 1000 -> 10000 -> 100

  print_list(linked_list);
}