#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CONTACTS 43
#define MAX_NUM_LENGTH 101

typedef struct {
    char name[MAX_NUM_LENGTH];  // Contact name
    char phone[MAX_NUM_LENGTH]; // Telephone number
} ContactInfo;

typedef struct {
    char nameAsNum[MAX_CONTACTS][MAX_NUM_LENGTH];
} T9NamesToNumbers;

const char *t9Map[] = {
    "0+",    // for 0
    "1",     // for 1
    "abc",   // for 2
    "def",   // for 3
    "ghi",   // for 4
    "jkl",   // for 5
    "mno",   // for 6
    "pqrs",  // for 7
    "tuv",   // for 8
    "wxyz"   // for 9
};

// Function to read contacts from stdin
int loadContacts(ContactInfo *contacts) {
    char buffer[MAX_NUM_LENGTH + 2]; // +2 for \n and \0
    int numContacts = 0;
    int errStatement = 0;
    int unauthorizedContact = 0;

    while (numContacts < MAX_CONTACTS) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

            if (strlen(buffer) > MAX_NUM_LENGTH) { //checking for disallowed long names
                errStatement++;
                unauthorizedContact++;

                if (strlen(buffer) != 102) { //ensures that the next parameter is not deleted if(..)
                    int character;
                    while ((character = getchar()) != '\n' && character != EOF); //removes the rest of the wrong line
                }
            }

            buffer[strcspn(buffer, "\n")] = '\0';  // Removes a new line
            strncpy(contacts[numContacts].name, buffer, sizeof(contacts[numContacts].name) - 1);
            contacts[numContacts].name[sizeof(contacts[numContacts].name) - 1] = '\0'; //ensures proper termination
        } else {
            break; // Exit if an error occurred
        }

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) { //checking for disallowed long phone numbers
            if (strlen(buffer) > MAX_NUM_LENGTH) {
                errStatement++;
                unauthorizedContact++;
                if (strlen(buffer) != 102) {
                    int character;
                    while ((character = getchar()) != '\n' && character != EOF);
                }
            }

            buffer[strcspn(buffer, "\n")] = '\0';  
            strncpy(contacts[numContacts].phone, buffer, sizeof(contacts[numContacts].phone) - 1);
            contacts[numContacts].phone[sizeof(contacts[numContacts].phone) - 1] = '\0'; 
        } else {
            break;
        }

        numContacts++; // Increases the number of contacts loaded
        
        if (unauthorizedContact > 0) { //ensures that wrong lines are overwritten
            unauthorizedContact = 0;
            numContacts--;
        }
    }

    if (errStatement > 0) {
        fprintf(stderr, "Error: %d inputs exceed the limit of 100 characters.\n", errStatement);
    }

    return numContacts;
}

// Function to split the argument into an array
char *splitNumbers(int argc, char *argv[]) {
    int index = 0;
    static char output[MAX_NUM_LENGTH];

    for (int idx1 = 1; idx1 < argc; idx1++) { //allows loading an argument with spaces (0420 775 694..)
        for (int idx2 = 0; argv[idx1][idx2] != '\0'; idx2++) {
            output[index] = argv[idx1][idx2];
            index++;

            if (index >= MAX_NUM_LENGTH - 1) {
                break;
            }
        }
    }

    output[index] = '\0'; //ensures proper termination
    return output;
}

// Function to convert names to t9 numerical representation
T9NamesToNumbers convertNamesToT9Numbers(ContactInfo *contacts, int numOfContacts) {
    T9NamesToNumbers result;

    for (int idx1 = 0; idx1 < numOfContacts; idx1++) {
        int index = 0;

        for (int idx2 = 0; contacts[idx1].name[idx2] != '\0' && index < MAX_NUM_LENGTH - 1; idx2++) { // goes through every character
            char currentChar = tolower(contacts[idx1].name[idx2]); // converting everything to lower case for comparison

            for (int mapIndex = 0; mapIndex < 10; mapIndex++) { // finds in which t9Map index the given character is
                if (strchr(t9Map[mapIndex], currentChar) != NULL) {
                    result.nameAsNum[idx1][index] = mapIndex + '0'; // + '0' to convert to asci value of the number
                                                                    // '0' represent 48 in ASCII. => '0' + number = the number given but as char
                    index++; 
                    break; // break when we find a matching index
                }
            }
        }
        result.nameAsNum[idx1][index] = '\0'; // ensures proper termination
    }

    return result;
}

// Function that does the comparison for the bonus
bool bonusComparison(char *userNumber, char *input) {
    int i = 0;
    int j = 0;

    while (userNumber[i] != '\0') {
        if (userNumber[i] == input[j]) {
            j++;
        }

        if (input[j] == '\0') {
            return true;
        }
        i++;
    }

    return false;
}

// Function that compares names with the given argument
int *compareWithNames(T9NamesToNumbers name, char *input, int numOfContacts, bool bonus) {
    static int users[MAX_CONTACTS];
    int index = 0;

    for (int i = 0; i < numOfContacts; i++) {
        if ((bonus == true && bonusComparison(name.nameAsNum[i], input) == true) || // with bonus
            (bonus == false && strstr(name.nameAsNum[i], input) != NULL)) {         // without bonus
            users[index] = i;
            index++;
        }
    }

    users[index] = -1;
    return users;
}

// Function that compares phone numbers with the given argument
int *compareWithNumbers(ContactInfo *contacts, char *input, int numOfContacts, bool bonus) {
    static int users[MAX_CONTACTS];
    int index = 0;
    char localInput[MAX_NUM_LENGTH];

    strcpy(localInput, input); // localInput overwrite protection

    for (int i = 0; i < numOfContacts; i++) {
        if (contacts[i].phone[0] == '+' && localInput[0] == '0') { // makes +420.. numbers work
            localInput[0] = '+';
        } else if (contacts[i].phone[0] == '0' && localInput[0] == '+') { // makes numbers with 0 work again
            localInput[0] = '0';
        }

        if ((bonus == true && bonusComparison(contacts[i].phone, input) == true) || //with bonus
            (bonus == false && strstr(contacts[i].phone, localInput) != NULL)) {    //without bonus
            users[index] = i;
            index++;
        }
    }

    users[index] = -1;
    return users;
}

// Function to check if the index is already in the finalArray
int isAlreadyInArray(int *array, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return 1; // It's already there :)
        }
    }
    return 0; // it's not there :(
}

// Function for output all compared contacts
void finalComparison(ContactInfo *contacts, int *foundNumbers, int *foundUsers) {
    int finalArray[MAX_CONTACTS];
    int index = 0;

    // add users from foundUsers
    for (int idx = 0; foundUsers[idx] != -1 && index < MAX_CONTACTS; idx++) {
        if (!isAlreadyInArray(finalArray, index, foundUsers[idx])) {
            finalArray[index] = foundUsers[idx];  // saves the user's index in an array
            index++;
        }
    }

    // add users from foundNumbers, if they aren't there yet
    for (int idx = 0; foundNumbers[idx] != -1 && index < MAX_CONTACTS; idx++) {
        if (!isAlreadyInArray(finalArray, index, foundNumbers[idx])) { // using function isAlreadyInArray() to check the occurrence of the index
            finalArray[index] = foundNumbers[idx]; // saves the user's index in an array
            index++;
        }
    }

    if (index == 0) { // when no contact was found
        printf("Not found");
    } else {
        for (int idx = 0; idx < index; idx++) {
            printf("%s, %s\n", contacts[finalArray[idx]].name, contacts[finalArray[idx]].phone);  // printing the result
        }
    }
}

// Function for listing some errors
int errorStatements(int argc, char *input) {
    if (argc == 1) {
        fprintf(stderr, "Error: No input parameters provided.\n");
        return 0;  // All contacts should be listed, so let's continue
    }

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            fprintf(stderr, "Error: Input contains non-numeric characters.\n");
            return 1;  // Returns an error code
        }
    }

    return 0;
}

// Function that detects if the bonus is active
bool isBonus(char **argv[], int *argc) {
    //**argv[] is a pointer to an array where each element points to another pointer that points to a char
    // (thanks to this, I can directly change the argv)
    if (*argc > 1) {
        if ((*argv)[1][0] == '-' && (*argv)[1][1] == 's') {
            (*argv)++;  // Move the pointer to argv, this omits the first parameter
            (*argc)--;  // Reducing the number of arguments
            return true;
        }
    }

    return false;
}

// Main Function
int main(int argc, char *argv[]) {
    bool bonus = isBonus(&argv, &argc);
    ContactInfo contacts[MAX_CONTACTS]; // Pole pro uchování kontaktů
    char *inputNumbers = splitNumbers(argc, argv); // Spojení argumentů na vstupu

    if (errorStatements(argc, inputNumbers)) { // pokud se vratila return 1
        return 1;
    }

    // Načtení kontaktů
    int numOfContacts = loadContacts(contacts);

    // Převod jmen na T9 čísla
    T9NamesToNumbers t9Results = convertNamesToT9Numbers(contacts, numOfContacts);

    // Srovnání podle telefonních čísel a jmen
    int *foundNumbers = compareWithNumbers(contacts, inputNumbers, numOfContacts, bonus);
    int *foundUsers = compareWithNames(t9Results, inputNumbers, numOfContacts, bonus);

    // Finální porovnání a výpis
    finalComparison(contacts, foundNumbers, foundUsers);

    return 0;
}
