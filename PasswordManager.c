#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max length of info; max length of each credential
#define totalLength 90
#define partialLength 30

// AddAccount function will be used to add account credentials to info
void addAccount(char *PF, char *UN, char *PW);

// DeleteAccount will be used to delete accounts at a given index in info
void deleteAccount(int index);

// ModifyAccount will be used to modify an account at a given index in info
void modifyAccount(int index);

// ListAccounts will be used to list all account credentials in info; also returns total indices
int listAccounts();

// Define a struct for the linked list node
struct node {
    char info[totalLength];
    struct node *next;
};

// Linked list initialization
struct node *acc = NULL;
// PF = Platform; UN = Username; PW = Password
char PF[partialLength];
char UN[partialLength];
char PW[partialLength];

int main() {
    // Option will be used for user selection
    int option = 0;
    printf("Welcome to Account Manager!\n");

    while (option != 5) { // 5 terminates the application
        printf("\n1. Add account credentials to your file.\n2. Delete account credentials from your file\n");
        printf("3. Modify account credentials in your file.\n4. List all account credentials in your file.\n5. Close Account Manager.\n");
        printf("\nSelect which option you would like to choose from (1-2-3-4-5): ");
        scanf("%d", &option);

        if (option == 1) { // If the user selects to add account credentials
            printf("\nDesired Platform: ");
            scanf("%s", PF);
            printf("Desired Username: ");
            scanf("%s", UN);
            printf("Desired Password: ");
            scanf("%s", PW);

            // Send desired information to addAccount
            addAccount(PF, UN, PW);
            printf("\nAccount information saved!\n");
        
        } else if (option == 2){ // User selects to delete account
            if (acc == NULL){
                printf("\nAccount list is empty\n");
            } else {
                int index, comparison; // Index is user's chosen index; comparison will ensure that index is not out of bounds
                listAccounts(); // List accounts for user to select from
                printf("\nSelect which account you would like to delete (using their index number): ");
                scanf("%d", &index);
                comparison = listAccounts();
                if (index >= comparison){
                    printf("\nIndex out of bounds\n");
                } else {
                    deleteAccount(index); // Send index number of desired account to delete to corresponding function
                    printf("\nAccount information deleted!\n");
                }
            }

        } else if (option == 3){ // User modifies selected account
            if (acc == NULL){
                printf("\nAccount list is empty\n");
            } else {
                int index, comparison; // Index is user's chosen index; comparison will ensure that index is not out of bounds
                listAccounts(); // List accounts for user to select from
                printf("\nSelect which account you would like to modify (using their index number): ");
                scanf("%d", &index);
                comparison = listAccounts();
                if (index >= comparison){
                    printf("\nIndex out of bounds\n");
                } else {
                    modifyAccount(index); // Send index number of desired account to delete to corresponding function
                }
            }
        
        } else if (option == 4){ // User selects to  list accounts
            if (acc == NULL){
                printf("\nAccount list is empty\n");
            } else {
                printf("\nPlatorm - Username - Password\n");
                listAccounts();
            }
        } else if (option > 5){
            printf("\nInvalid option\n");
        }
    }
    // Free allocated memory when done
    while (acc != NULL) {
        struct node *temp = acc;
        acc = acc->next;
        free(temp);
    }
}

void addAccount(char *PF, char *UN, char *PW) {
    // Concatenate PF, UN, and PW, separated by "-"
    char temp[totalLength];
    snprintf(temp, totalLength, "%s-%s-%s", PF, UN, PW);

    // Create a new temporary node
    struct node *newNode = malloc(sizeof(struct node));

    // Copy the concatenated string to the info field of the new node
    strncpy(newNode->info, temp, sizeof(newNode->info) - 1);
    newNode->info[sizeof(newNode->info) - 1] = '\0';  // Ensure null-termination

    // Set the next pointer of the new node to NULL
    newNode->next = NULL;

    // If the linked list is empty, set the head to the new node
    if (acc == NULL) {
        acc = newNode;
    } else {
        // Otherwise, traverse to the end of the linked list and insert the new node
        struct node *current = acc;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteAccount(int index){
    if (index == 1) {
        // Special case: deleting the head of the list
        struct node *temp = acc;
        acc = acc->next;
        free(temp);
        return;
    }

    int i = 1;  // Start counting from 1
    struct node *current = acc;

    // Traverse to the node before the desired index
    while (i < index - 1) {
        current = current->next;
        i++;
    }
    // Delete the node at the given index
    struct node *temp = current->next;
    current->next = temp->next;
    free(temp);
}

void modifyAccount(int index){
    int i = 1;  // Start counting from 1
    struct node *current = acc;

    // Traverse to the node before the desired index
    while (i < index) {
        current = current->next;
        i++;
    } int choice; // User choice to select which attribute to modify
    const char split = '-'; // Char split will be used to separate information into 3 categories

    // Use strtok to get the first token
    char *token = strtok(current->info, &split);

    char PF[partialLength];
    char UN[partialLength];
    char PW[partialLength];

    // Copy the 3 separate string categories into PF; UN; PW (later to reassemble info-string)
    strncpy(PF, token, sizeof(PF) - 1);
    PF[sizeof(PF) - 1] = '\0'; // Ensure null-termination

    // Use strtok to get the second token
    token = strtok(NULL, &split);

    strncpy(UN, token, sizeof(UN) - 1);
    UN[sizeof(UN) - 1] = '\0'; // Ensure null-termination

    // Use strtok to get the third token
    token = strtok(NULL, &split);

    strncpy(PW, token, sizeof(PW) - 1);
    PW[sizeof(PW) - 1] = '\0'; // Ensure null-termination

    // User selects to modify UN or PW
    printf("\nModify (1) the username | Modify (2) the password | Modify (3) both: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char temp[partialLength];
        printf("\nWhat would you like your new username to be? ");
        scanf("%s", temp);
        temp[sizeof(temp) - 1] = '\0'; // Ensure that the final character is null
        strncpy(UN, temp, sizeof(UN) - 1);
        UN[sizeof(UN) - 1] = '\0'; // Ensure null-termination
    } else if (choice == 2) {
        char temp[partialLength];
        printf("\nWhat would you like your new password to be? ");
        scanf("%s", temp);
        temp[sizeof(temp) - 1] = '\0'; // Ensure that the final character is null
        strncpy(PW, temp, sizeof(PW) - 1);
        PW[sizeof(PW) - 1] = '\0'; // Ensure null-termination
    } else if (choice == 3) {
        // Change username first
        char tempUN[partialLength];
        printf("\nWhat would you like your new username to be? ");
        scanf("%s", tempUN);
        tempUN[sizeof(tempUN) - 1] = '\0'; // Ensure that the final character is null
        strncpy(UN, tempUN, sizeof(UN) - 1);
        UN[sizeof(UN) - 1] = '\0'; // Ensure null-termination

        // Change password next
        char tempPW[partialLength];
        printf("\nWhat would you like your new password to be? ");
        scanf("%s", tempPW);
        tempPW[sizeof(tempPW) - 1] = '\0'; // Ensure that the final character is null
        strncpy(PW, tempPW, sizeof(PW) - 1);
        PW[sizeof(PW) - 1] = '\0'; // Ensure null-termination
    } else {
        printf("Invalid choice.\n");
        return;
    }
    // Concatenate PF, UN, and PW, separated by "-"
    char temp[totalLength];
    snprintf(temp, totalLength, "%s-%s-%s", PF, UN, PW);
    strncpy(current->info, temp, sizeof(current->info) - 1); // Ensure info ends with null
    current->info[sizeof(current->info) - 1] = '\0'; // Ensure null-termination
    printf("\nYour new account information is: %s\n", current->info);
}

int listAccounts() {
    int loop = 1;
    // Use a local variable to traverse the linked list
    struct node *current = acc;
    // Loop through the linked list and print each account information
    while (current != NULL) {
        printf("%d: %s\n", loop, current->info);
        loop++;
        current = current->next;
    } return loop;
}