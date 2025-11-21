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

            result = list.insertAtPosition(value, position, false);
            cout << (result ? "Inserted Successfully."
                            : "Insertion Failed.")
                 << endl;
            break;

        case 2: // Force Insert
            cout << "Enter The Position: ";
            position = getInput();
            cout << "Enter the value you want to insert: ";
            cin >> value;

            list.insertAtPosition(value, position, true);
            cout << "Inserted Successfully.\n";
            break;

        case 3: // Delete
            cout << "Enter position to delete: ";
            position = getInput();

            result = list.deleteAtPosition(position);

            cout << (result ? "Deleted Successfully."
                            : "Deletion failed.")
                 << endl;
            break;

        case 4: // Search
            cout << "Enter value to search for:";
            cin >> value;
            position = list.search(value);
            if (position != -1)
                cout << "Found at position " << position << endl;
            else
                cout << "Not Found" << endl;
            break;

        case 5: // Display list
            cout << "\nList contents: " << list;
            break;

        case 6: // Check if empty
            cout << (list.isEmpty() ? "List is empty. "
                                    : "List is not empty.")
                 << endl;
            break;

        case 7: // Display free nodes
            list.displayFreeNodes(cout);
            break;

        case 8: // Exit
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
         << "1. Insert at Position (Does not insert if list is full)\n"
         << "2. Force Insert at Position"
         << " (Deletes first element if list is full)\n"
         << "3. Delete at Position\n"
         << "4. Search for a Value\n"
         << "5. Display List\n"
         << "6. Check if List is Empty\n"
         << "7. display free Nodes\n"
         << "8. Exit\n"
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
