/*-- main.cpp ------------------------------------------------------------------
  Interactive tester for ArrayBasedList<T> and NodePool<T>.

  This menu-driven program allows the user to test:
    • Insert in the list
    • Delete from the list
    • Search for a value
    • Display the list
    • Check if list is empty
    • Show free and used nodes inside NodePool
    • Sort the list
    • Get the list size


 * Precondition: None. Program begins execution with no required initial state.

 * Postcondition: All Allocations and Deallocations occur within the fixed pool;
     Program terminates normally and returns 0.

  All memory allocation happens inside a fixed-size NodePool.

  NOTES:
    The program assumes all values to be inserted into the list are of type
        ElementType.
    This program needs to run on a newer version of C++ in order to properly
        use the function stoi()
------------------------------------------------------------------------------*/

#include <iostream>
#include "NodePool.h"
#include "ArrayBasedList.h"

typedef int ElementType;

void displayMenu();
/*------------------------------------------------------------------------------
    Display the menu of actions to perform on the list

    Precondition:  None.
    Postcondition: Menu is displayed.
------------------------------------------------------------------------------*/

void displayInsertMenu();
/*------------------------------------------------------------------------------
    Display the menu of insert actions to perform on the list

    Precondition:  None.
    Postcondition: Insert menu is displayed.
------------------------------------------------------------------------------*/

void displayDeleteMenu();
/*------------------------------------------------------------------------------
    Display the menu of delete actions to perform on the list

    Precondition:  None.
    Postcondition: Delete menu is displayed.
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
        ElementType value, target;
        bool result;

        switch (choice)
        {
        case 1: // Insert
            // Get position
            displayInsertMenu();

            // Get type of insertion from user (3 total choices)
            do
            {
                choice = getInput();
                if (choice < 1 || choice > 3)
                {
                    cerr << "Choice must be 1, 2 or 3\n";
                }
            } while (choice < 1 || choice > 3);

            switch (choice)
            {
            case 1: // Insert at position
                cout << "Enter The Position: ";
                position = getInput();
                // Get value
                cout << "Enter the value you want to insert: ";
                cin >> value;

                // Insert
                result = list.insertAtPosition(value, position, false);
                cout << (result ? "Inserted Successfully."
                                : "Insertion Failed.")
                     << endl;
                break;

            case 2: // Insert Before Value
                // Get value to insert before
                cout << "Enter the value before which you want to insert the new node: ";
                cin >> target;

                // Get new value
                cout << "Enter the new value to insert: ";
                cin >> value;

                // Insert
                result = list.insertBeforeValue(value, target, false);
                cout << (result ? "Inserted Successfully."
                                : "Insertion failed.")
                     << endl;
                break;

            case 3: // Insert After value
                // Get value to insert after
                cout << "Enter the value after which you want to insert the new node: ";
                cin >> target;

                // Get new value
                cout << "Enter the new value to insert: \n";
                cin >> value;

                // Insert
                result = list.insertAfterValue(value, target, false);
                cout << (result ? "Inserted Successfully."
                                : "Insertion failed.")
                     << endl;
                break;
            }
            break;

        case 2: // Force Insert
            displayInsertMenu();

            // Get type of insertion from user (3 total choices)
            do
            {
                choice = getInput();
                if (choice < 1 || choice > 3)
                {
                    cerr << "Choice must be 1, 2 or 3";
                }
            } while (choice < 1 || choice > 3);

            switch (choice)
            {
            case 1: // Insert at position
                // Get position
                cout << "Enter The Position: ";
                position = getInput();
                // Get value
                cout << "Enter the value you want to insert: ";
                cin >> value;

                // Insert
                result = list.insertAtPosition(value, position, true);
                cout << (result ? "Inserted Successfully."
                                : "Insertion Failed.")
                     << endl;
                break;

            case 2: // Insert Before Value
                // Get value to insert before
                cout << "Enter the value before which you want to insert the new node: ";
                cin >> target;

                // Get new value
                cout << "Enter the new value to insert: \n";
                cin >> value;

                // Insert
                result = list.insertBeforeValue(value, target, true);
                cout << (result ? "Inserted Successfully."
                                : "Insertion failed.")
                     << endl;
                break;

            case 3: // Insert After value
                // Get value to insert after
                cout << "Enter the value after which you want to insert the new node: ";
                cin >> target;

                // Get new value
                cout << "Enter the new value to insert: \n";
                cin >> value;

                // Insert
                result = list.insertAfterValue(value, target, true);
                cout << (result ? "Inserted Successfully."
                                : "Insertion failed.")
                     << endl;
                break;
            }
            break;

        case 3: // Delete
            displayDeleteMenu();

            // Get type of deletion from user (4 total choices)
            do
            {
                choice = getInput();
                if (choice < 1 || choice > 4)
                {
                    cerr << "Choice must be 1, 2, 3 or 4\n";
                }
            } while (choice < 1 || choice > 4);
            switch (choice)
            {
            case 1: // Delete at position
                // Get position
                cout << "Enter position to delete: ";
                position = getInput();

                // Delete
                result = list.deleteAtPosition(position);

                cout << (result ? "Deleted Successfully."
                                : "Deletion failed.")
                     << endl;
                break;
            case 2: // Delete before value
                cout << "Enter the value which you want to delete the node before: ";
                cin >> target;

                result = list.deleteBeforeValue(target);
                cout << (result ? "Deleted Successfully."
                                : "Deletion failed.")
                     << endl;
                break;

            case 3: // Delete value
                cout << "Enter the value you want to delete: ";
                cin >> value;
                result = list.deleteValue(value);
                cout << (result ? "Deleted Successfully."
                                : "Deletion Failed")
                     << endl;
                break;

            case 4: // Delete after value
                cout << "Enter the value after which you want to delete the next node: ";
                cin >> target;

                result = list.deleteAfterValue(target);
                cout << (result ? "Deleted Successfully."
                                : "Deletion failed.")
                     << endl;
                break;
            }
            break;

        case 4: // Search
            // Get value
            cout << "Enter value to search for: ";
            cin >> value;

            // Search for value
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

        case 7: // Display size
            cout << "List size: " << list.size() << endl;
            break;

        case 8: // Display free nodes
            list.displayFreeNodes(cout);
            break;

        case 9: // sort
            list.sort();
            cout << "List has been sorted.\n";
            break;

        case 10: // Exit
            cout << "Exiting program..." << endl;
            return 0;

        default: // Invalid choice
            cerr << "Invalid option.try again.\n";
        }
    }
    return 0;
}

// Definition of displayMenu()
void displayMenu()
{
    cout << "\n=== Array-Based List Tester ===\n"
         << "1.  Insert (Does not insert if list is full)\n"
         << "2.  Force insert"
         << " (Deletes first element if list is full)\n"
         << "3.  Delete\n"
         << "4.  Search for a Value\n"
         << "5.  Display List\n"
         << "6.  Check if List is Empty\n"
         << "7.  Get list size\n"
         << "8.  display free Nodes\n"
         << "9.  Sort List\n"
         << "10. Exit\n"
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

void displayInsertMenu()
{
    cout << "\n=== Insert Menu ===\n"
         << "1. Insert at position\n"
         << "2. Insert before value\n"
         << "3. Insert after value\n"
         << "Choose an option: ";
}

void displayDeleteMenu()
{
    cout << "\n=== Delete Menu ===\n"
         << "1. Delete at position\n"
         << "2. Delete before value\n"
         << "3. Delete value\n"
         << "4. Delete after value\n"
         << "Choose an option: ";
}
