#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Type Definitions ////////////////////////////////////////////////////////////////////////////////

typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode {
  int value;
  LinkedListNode *next;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Management ///////////////////////////////////////////////////////////////////////////////

// Create a new linked list with a given value
LinkedListNode* LinkedList_new(int value) {
  LinkedListNode *head = malloc(sizeof(LinkedListNode));
  head->value = value;
  head->next = NULL;
  return head;
}

// Free all the nodes in a linked list
LinkedListNode* LinkedList_free(LinkedListNode *head) {
  if (head == NULL) return NULL;

  LinkedListNode *current = head;
  LinkedListNode *toDelete = NULL;

  while (current != NULL) {
    toDelete = current;
    current = current->next;
    free(toDelete);
  }

  return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutation ////////////////////////////////////////////////////////////////////////////////////////

// Add a value to the start of the linked list
LinkedListNode* LinkedList_prepend(LinkedListNode *head, int value) {
  LinkedListNode *newHead = LinkedList_new(value);
  newHead->next = head;
  return newHead;
}

// Add a value to the end of the linked list
LinkedListNode* LinkedList_append(LinkedListNode *head, int value) {
  if (head == NULL) return NULL;

  LinkedListNode *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = LinkedList_new(value);

  return head;
}

// Remove a value from the start of the linked list
LinkedListNode* LinkedList_pull(LinkedListNode *head, int *shiftedValue) {
  if (head == NULL) return NULL;

  *shiftedValue = head->value;

  LinkedListNode *toDelete = head;
  head = head->next;
  toDelete->next = NULL;
  LinkedList_free(toDelete);

  return head;
}

// Remove a value from the end of the linked list
LinkedListNode* LinkedList_pop(LinkedListNode *head, int *poppedValue) {
  if (head == NULL) return NULL;

  LinkedListNode *current = head;
  LinkedListNode *prior = NULL;
  while (current->next != NULL) {
    prior = current;
    current = current->next;
  }

  *poppedValue = current->value;

  if (prior != NULL) {
    prior->next = LinkedList_free(current);
  } else {
    head = LinkedList_free(head);
  }

  return head;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Query ///////////////////////////////////////////////////////////////////////////////////////////

// Determines whether a value exists in the list
bool LinkedList_contains(LinkedListNode *head, int value) {
  LinkedListNode *current = head;
  while (current != NULL) {
    if (current->value == value) return true;
    current = current->next;
  }

  return false;
}

// Determines the number of nodes in the list
int LinkedList_length(LinkedListNode *head) {
  int result = 0;
  LinkedListNode *current = head;
  while (current != NULL) {
    current = current->next;
    result++;
  }

  return result;
}

// Prints the list to the console
void LinkedList_print(LinkedListNode *head) {
  LinkedListNode *current = head;
  while (current != NULL) {
    printf("(%d)->", current->value);
    current = current->next;
  }
  printf("NULL");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Tests ///////////////////////////////////////////////////////////////////////////////////////////

LinkedListNode *buildTest() {
  LinkedListNode *head = LinkedList_new(42);
  head = LinkedList_append(head, 43);
  head = LinkedList_append(head, 44);
  return head;
}

void test_prepend() {
  printf("Running test: prepend\n");
  LinkedListNode *head = LinkedList_new(42);
  head = LinkedList_prepend(head, 43);
  head = LinkedList_prepend(head, 44);
  LinkedList_print(head); printf("    should be    (44)->(43)->(42)->NULL\n");

  head = LinkedList_free(head);
  printf("\n");
}

void test_append() {
  printf("Running test: append\n");
  LinkedListNode *head = buildTest();
  LinkedList_print(head); printf("    should be    (42)->(43)->(44)->NULL\n");

  head = LinkedList_free(head);
  printf("\n");
}

void test_pull() {
  printf("Running test: pull\n");
  LinkedListNode *head = buildTest();

  int value = 0;
  head = LinkedList_pull(head, &value);
  printf("%d    should be    42\n", value);
  LinkedList_print(head); printf("    should be    (43)->(44)->NULL\n");
  head = LinkedList_pull(head, &value);
  printf("%d    should be    43\n", value);
  LinkedList_print(head); printf("    should be    (44)->NULL\n");
  head = LinkedList_pull(head, &value);
  printf("%d    should be    44\n", value);
  LinkedList_print(head); printf("    should be    NULL\n");

  head = LinkedList_free(head);
  printf("\n");
}

void test_pop() {
  printf("Running test: pop\n");
  LinkedListNode *head = buildTest();

  int value = 0;
  head = LinkedList_pop(head, &value);
  printf("%d    should be    44\n", value);
  LinkedList_print(head); printf("    should be    (42)->(43)->NULL\n");
  head = LinkedList_pop(head, &value);
  printf("%d    should be    43\n", value);
  LinkedList_print(head); printf("    should be    (42)->NULL\n");
  head = LinkedList_pop(head, &value);
  printf("%d    should be    42\n", value);
  LinkedList_print(head); printf("    should be    NULL\n");

  head = LinkedList_free(head);
  printf("\n");
}

void test_contains() {
  printf("Running test: contains\n");
  LinkedListNode *head = buildTest();

  printf("%s    should be    true\n", LinkedList_contains(head, 43) ? "true" : "false");
  printf("%s    should be    false\n", LinkedList_contains(head, 90) ? "true" : "false");

  head = LinkedList_free(head);
  printf("\n");
}

void test_length() {
  printf("Running test: length\n");
  LinkedListNode *head = buildTest();

  printf("%d    should be    3\n", LinkedList_length(head));
  
  head = LinkedList_free(head);
  printf("\n");
}

int main() {
  test_prepend();
  test_append();
  test_pull();
  test_pop();
  test_contains();
  test_length();
}
