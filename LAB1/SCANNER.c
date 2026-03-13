#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;              
    int count;            
    struct Node *next;    
} Node;

Node *createNode(char ch) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    newNode->ch = ch;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void insertChar(Node **head, char ch) {
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->ch == ch) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }

    Node *newNode = createNode(ch);

    if (*head == NULL) {
        *head = newNode;
    } else {
        prev->next = newNode;
    }
}

void printChar(char ch) {
    if (ch == '\n') {
        printf("'\\n'");
    } else if (ch == '\t') {
        printf("'\\t'");
    } else if (ch == ' ') {
        printf("' '");
    } else {
        printf("'%c'", ch);
    }
}

void printList(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printChar(current->ch);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("\n");
}

void printListWithCount(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printChar(current->ch);
        printf("  count = %d\n", current->count);
        current = current->next;
    }
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE *fp;
    int c;
    Node *head = NULL;

    fp = fopen("main.c", "r");
    if (fp == NULL) {
        printf("cannot open main.c\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        insertChar(&head, (char)c);
    }

    fclose(fp);

    printf("Output:\n");
    printList(head);

    freeList(head);
    return 0;
}
