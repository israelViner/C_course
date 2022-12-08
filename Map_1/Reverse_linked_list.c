#include <stdio.h>
#include <stdlib.h>

//#define 0 NULL

// Link list node
struct Node {
	int data;
	struct Node* next;
};

// Function to add a new node
void insert(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));	
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

// Function to print linked list
void printList(struct Node* head)
{
	struct Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

//The main task
static void reverse(struct Node** head_ref)
{
	struct Node* temp = *head_ref;
	(*head_ref) = NULL;
	while (temp != NULL)
	{
		insert(head_ref, temp->data);
		temp = temp->next;
	}
	
}

int main()
{
	// Start with the empty list
	struct Node* head = NULL;
	insert(&head, 20);
	insert(&head, 4);
	insert(&head, 15);
	insert(&head, 85);
	printf("The linked list is:\n");
	printList(head);
	printf("\n\nThe reverse linked list is:\n");
	reverse(&head);
	printList(head);
	printf("\n\n\n");
}
