#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *createNode(int value) {
    Node *toAdd = malloc(sizeof(Node));

    toAdd->value = value;
    toAdd->next = NULL;

    return toAdd;
}

Node *addFront(Node *head, Node *toAdd) {
    toAdd->next = head;

    return toAdd;
}

Node *addBack(Node *head, Node *toAdd) {
    if (head == NULL) {
        // List is empty, toAdd = head
        head = toAdd;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = toAdd;
    }
    return head;
}

Node *addAfter(Node *head, Node *toAdd, int position) {
    if (head == NULL) {
        head = toAdd;
    } else {
        int positionCounter = 0;
        Node *current = head;

        while (current != NULL) {
            if (position == positionCounter) {
                toAdd->next = current->next;
                current->next = toAdd;
            }

            if (current->next == NULL) {
                current->next = toAdd;
                return head;
            }

            positionCounter++;
            current = current->next;
        }
    }

    return head;
}

Node *addAfterLess(Node *head, Node *toAdd) {
    if (head == NULL) {
        head = toAdd;

        return head;
    }

    if (head->value >= toAdd->value) {
        toAdd->next = head;

        return toAdd;
    }

    int nextValue = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->next != NULL) {
            nextValue = current->next->value;
        } else {
            current->next = toAdd;

            return head;
        }

        if (nextValue > toAdd->value) {
            // Insert before the older date
            toAdd->next = current->next;
            current->next = toAdd;

            return head;
        } else {
            // Iterate to the next element
            current = current->next;
        }
    }

    return toAdd;
}

Node *addAfterBigger(Node *head, Node *toAdd) {
    if (head == NULL) {
        head = toAdd;

        return head;
    }

    if (head->value <= toAdd->value) {
        toAdd->next = head;

        return toAdd;
    }

    int nextValue = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->next != NULL) {
            nextValue = current->next->value;
        } else {
            current->next = toAdd;

            return head;
        }

        if (nextValue < toAdd->value) {
            // Insert before the older date
            toAdd->next = current->next;
            current->next = toAdd;

            return head;
        } else {
            // Iterate to the next element
            current = current->next;
        }
    }

    return toAdd;
}

Node *reverse(Node *head){
    // Add to front until head == NULL
    Node *current = head;
    Node *new = NULL;

    while (head != NULL) {
        head = head->next;
        current->next = new;
        new = current;
        current = head;
    }

    return new;
}

/*
 * Returns 0 when value is not found
 * Returns 1 when value is found
 */
int searchValue(Node *head, int sValue) {
    int found = 0;
    Node *current = head;

    while (current != NULL) {
        if (current->value == sValue) {
            found = 1;
        }

        current = current->next;
    }

    return found;
}

Node *printList(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d", current->value);

        if (current->next != NULL) {
            printf(" -> ");
        }

        current = current->next;
    }
}

void freeList(Node *head) {
    // Check if head is NULL - list can't be free'd exit with 1 - error
    if (head == NULL) {
        printf("List is empty!");
        exit(1);
    }

    Node *current = NULL;
    while (head != NULL) {
        current = head;
        head = head->next;

        free(current);
    }
}

Node *deleteNodesWithValue(Node *head, int value) {
    Node *current = head;
    Node *newList = NULL;
    Node *toAdd = NULL;

    while (current != NULL) {
        if (current->value != value) {
            toAdd = createNode(current->value);
            newList = addBack(newList, toAdd);
        }

        current = current->next;
    }

    freeList(head);

    return newList;
}

Node *deleteOddNumbers(Node *head) {
    Node *current = head;
    Node *newList = NULL;
    Node *toAdd = NULL;

    while (current != NULL) {
        if ((current->value % 2) == 0) {
            toAdd = createNode(current->value);
            newList = addBack(newList, toAdd);
        }

        current = current->next;
    }

    freeList(head);

    return newList;
}

Node *deleteEvenNumbers(Node *head) {
    Node *current = head;
    Node *newList = NULL;
    Node *toAdd = NULL;

    while (current != NULL) {
        if ((current->value % 2) != 0) {
            toAdd = createNode(current->value);
            newList = addBack(newList, toAdd);
        }

        current = current->next;
    }

    freeList(head);

    return newList;
}

Node *incrementValues(Node *head) {
    Node *current = head;

    while (current != NULL) {
        current->value++;

        current = current->next;
    }

    return head;
}

Node *decrementValues(Node *head) {
    Node *current = head;

    while (current != NULL) {
        current->value--;

        current = current->next;
    }

    return head;
}

int getListSize(Node *head) {
    int listSize = 0;
    Node *current = head;

    while (current != NULL) {
        listSize++;

        current = current->next;
    }

    return listSize;
}



int sumValues(Node *head) {
    int sum = 0;
    Node *current = head;

    while (current != NULL) {
        sum += current->value;

        current = current->next;
    }

    return sum;
}

double calculateAverage(Node *head) {
    int listSize = getListSize(head);
    int valueSums = sumValues(head);

    double lfAverage = (double) valueSums / listSize;

    return lfAverage;
}

int main() {
    Node *testList = NULL;

    Node *aNode = createNode(3);
    Node *backNode = createNode(10);
    Node *c = createNode(16);
    Node *afterNode = createNode(17);

    testList = addAfterLess(testList, c);
    testList = addAfterLess(testList, aNode);
    testList = addAfterLess(testList, backNode);

    testList = addAfterLess(testList, afterNode);

    printList(testList);
    printf("\n");

    testList = deleteEvenNumbers(testList);

    printList(testList);

    freeList(testList);
    return 0;
}
