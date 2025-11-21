/*-- main.cpp ------------------------------------------------------------------
  Interactive tester for ArrayBasedList<T> and NodePool<T>.

  This menu-driven program allows the instructor to test:
    • Insert at position
    • Delete at position
    • Search for a value
    • Display the list
    • Check if list is empty
    • Show free and used nodes inside NodePool

 * Precondition: None. Program begins execution with no required initial state.

 * Postcondition: All Allocations and Deallocations occur within the fixed pool;
     Program terminates normally and returns 0.

  All memory allocation happens inside a fixed-size NodePool.
------------------------------------------------------------------------------*/

#include <iostream>
#include "NodePool.h"
#include "ArrayBasedList.h"

typedef string ElementType;

void displayMenu();
/*------------------------------------------------------------------------------
    Display the menu of actions to perform on the list

    Precondition:  None.
    Postcondition: Menu is displayed.
------------------------------------------------------------------------------*/

int getInput();
/*------------------------------------------------------------------------------
    Get positive integer from user.

    Precondition:  None.
    Postcondition: A positive integer is returned, which determines the user's
                   choice.
------------------------------------------------------------------------------*/

using namespace std;

int main()
{
    ArrayBasedList<ElementType> list; // List to perform operations on
    int choice;                       // User's choice

    // Keep running until the user inputs 7 (the exit option)
    while (true)
    {
        displayMenu(); // display choice menu

        choice = getInput(); // get choice from user

        // Declare variables used for list operations
        int position;
        ElementType value;
        bool result;
        switch (choice)
        {
        case 1: // Insert
            cout << "Enter The Position: ";
            position = getInput();
            cout << "Enter the value you want to insert: ";
            cin >> value;

            result = list.insertAtPosition(value, position);
            cout << (result ? "Inserted Successfully." : "Insertion Failed.") << endl;
            break;

        case 2: // Delete
            cout << "Enter position to delete: ";
            position = getInput();

            result = list.deleteAtPosition(position);

            cout << (result ? "Deleted Successfully." : "Deletion failed.") << endl;
            break;

        case 3: // Search
            cout << "Enter value to search for:";
            cin >> value;
            position = list.search(value);
            if (position != -1)
                cout << "Found at position " << position << endl;
            else
                cout << "Not Found" << endl;
            break;

        case 4: // Display list
            cout << "\nList contents: " << list;
            break;

        case 5: // Check if empty
            cout << (list.isEmpty() ? "List is empty. " : "List is not empty.") << endl;
            break;

        case 6: // Display free nodes
            cout << "\nFree Nodes: ";
            list.displayFreeNodes(cout);
            break;

        case 7: // Exit
            cout << "Exiting program..." << endl;
            return 0;

        default: // Invalid choice
            cout << "Invalid option.try again.\n";
        }
    }
    return 0;
}

// Definition of displayMenu()
void displayMenu()
{
    cout << "\n=== Array-Based List Tester ===\n"
         << "1. Insert at Position\n"
         << "2. Delete at Position\n"
         << "3. Search for a Value\n"
         << "4. Display List\n"
         << "5. Check if List is Empty\n"
         << "6. display free Nodes\n"
         << "7. Exit\n"
         << "Choose an option: ";
}

int getInput()
{
    string input;
    int choice;
    while (true)
    {
        cin >> input;
        try
        {
            choice = stoi(input);
            if (choice >= 0)
            {
                return choice;
            }
            else
            {
                cerr << "ERROR: Please input a positive integer.\n";
            }
        }
        catch (invalid_argument &error)
        {
            cerr << "ERROR: Please input a postive integer.\n";
        }
    }
}
