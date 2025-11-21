/*-- List.h --------------------------------------------------------------------
    This header file defines the template class ArrayBasedList for managing a
    singly linked list using an array-based NodePool.

    Basic operations are:
        Constructor: Constructs an empty list.
        isEmpty: Check if list is empty.
        insertAtPosition: insert node with data in the list at specified
                          position.
        deleteAtPosition: delete node at specified position.
        search: Search for specified data in the list.
        display: print list content.
        displayFreeNodes: print free nodes' positions in the NodePool.

    Class Invariant:
        1. The list elements are stored in positions 0, 1,..., CAPACITY - 1
        2. first stores the index of the first node in the list, or NULL_INDEX
           if list is empty.
        3. All used nodes are linked together through their 'next' data field,
           except the last node which points to NULL_INDEX.
------------------------------------------------------------------------------*/

#ifndef ARRAYBASEDLIST_H
#define ARRAYBASEDLIST_H

#include <iostream>
#include "nodePool.h"

using namespace std;

template <typename ElementType>
class ArrayBasedList
{
public:
    /******** Member Functions ********/

    /***** Class constructor *****/
    ArrayBasedList();
    /*--------------------------------------------------------------------------
        Construct an empty ArrayBasedList

        Precondition:  None.
        Postcondition: An empty ArrayBasedList is contructed; first is
                       initialized to NULL_INDEX, nodePool is initialized to a
                       default NodePool.
    --------------------------------------------------------------------------*/

    // ~ArrayBasedList(); // not needed (same for copy-constructor and assignement operator)

    bool isEmpty() const;
    /*----------------------------------------------------------------------
        Check if the list is empty.

        Precondition:  None
        Postcondition: Returns true if the list has no elements, false otherwise.
------------------------------------------------------------------------------*/

    bool insertAtPosition(const ElementType &value, int position,
                          bool forced = false);
    /*--------------------------------------------------------------------------
        Insert a new element at a specified position in the list.

        Precondition:
            position is an integer between 0 and CAPACITY - 1.
            There is at least one free node in the NodePool.

        Postcondition:
            The element 'value' is inserted at the given 'position'.
            If the list is not full, insertion happens and returns true.
            If the list is full and insertion is not forced, insertion does not
                happen and returns false.
            If the list is full and insertion is forced, insertion removes the
                first element in the list and then inserts the element and
                returns true.

        Notes:
            Position 0 inserts at the beginning.
            If the list is empty, only position 0 is valid.
------------------------------------------------------------------------------*/

    bool deleteAtPosition(int position);
    /*--------------------------------------------------------------------------
        Delete the element at the specified position in the list.

        Precondition:
            position is an integer between 0 and CAPACITY - 1.
            The list is not empty.

        Postcondition:
            The element at 'position' is removed from the list.
            The node is returned to the NodePool.
            Returns true if deletion is successful, false if position is
                invalid or list is empty.
------------------------------------------------------------------------------*/

    int search(const ElementType &data) const;
    /*--------------------------------------------------------------------------
        Search for the first occurrence of a value in the list.

        Precondition:  None

        Postcondition:
            Returns the logical position of the first node containing 'data'.
            Returns NULL_INDEX if the value is not found.
------------------------------------------------------------------------------*/

    void display(ostream &out) const;
    /*--------------------------------------------------------------------------
        Display all elements in the list in order.

        Precondition:  None

        Postcondition:
            Outputs all elements starting from the head to 'out'.
            If the list is empty, outputs "List is empty".
------------------------------------------------------------------------------*/

    void displayFreeNodes(ostream &out) const;
    /*--------------------------------------------------------------------------
        Display the indices of free nodes in the NodePool.

        Precondition:  None
        Postcondition: Outputs the list of free node indices managed by NodePool.
------------------------------------------------------------------------------*/

private:
    NodePool<ElementType> nodePool; // NodePool object to store data
    int first;                      // first element in the list

}; // end of class declaration

// Definition of constructor
template <typename ElementType>
ArrayBasedList<ElementType>::ArrayBasedList() : first(NULL_INDEX) {}

// Definition of isEmpty()
template <typename ElementType>
bool ArrayBasedList<ElementType>::isEmpty() const
{
    return first == NULL_INDEX;
}

// Definition of insertAtPosition()
template <typename ElementType>
bool ArrayBasedList<ElementType>::insertAtPosition(const ElementType &value,
                                                   int position, bool forced)
{
    if (position < 0 || position >= CAPACITY) // Invalid index
    {
        return false;
    }
    if (first == NULL_INDEX) // List is empty
    {
        if (position == 0) // Insert at beginning of empty list
        {
            first = nodePool.acquireNode();             // get free node and assign it to first
            nodePool.setNode(first, value, NULL_INDEX); // set data of first node
            return true;
        }
        else // Can not insert in the middle (or end) of an empty list
        {
            return false;
        }
    }
    else // List is not empty
    {
        if (position == 0) // Insert at beginning of non-empty list
        {
            int newNode = nodePool.acquireNode(); // get free node
            if (newNode == NULL_INDEX)            // list is full
            {
                if (forced) // replace data of first node with new data (faster than removing node at 0 then inserting node at 0)
                {
                    nodePool.setNodeData(first, value); // change data of first
                    return true;
                }
                else
                {
                    return false;
                }
            }
            // set data of first node and let it point to old first
            nodePool.setNode(newNode, value, first);
            first = newNode; // set first to newNode
            return true;
        }
        else // Insert in non-empty list
        {
            int temp = first; // To traverse the list
            int count = 1;    // Counter to stop at position - 1
            // Loop until either the end of the list or we are at position - 1
            while (nodePool.getNextOfNode(temp) != NULL_INDEX && count < position)
            {
                temp = nodePool.getNextOfNode(temp);
                count++;
            }

            if (count < position) // position not reached (list is too small)
            {
                return false;
            }

            int newNode = nodePool.acquireNode(); // get free node
            if (newNode == NULL_INDEX)            // list is full
            {
                if (forced) // free first then set newNode to it (THERE IS A BETTER WAY TO DO IT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
                {
                    int other = first; // temporary index for deletion
                    // point first to the second element in the list
                    first = nodePool.getNextOfNode(first);

                    temp = nodePool.getNextOfNode(temp);
                    newNode = other;
                }
                else
                {
                    return false;
                }
            }

            // temp is now the index which we must insert after
            // Set next of newNode to be the next of temp (place newNode before the next of temp)
            nodePool.setNode(newNode, value, nodePool.getNextOfNode(temp));

            // Change temp to point to newNode (place newNode after temp)
            nodePool.setNextOfNode(temp, newNode);
            return true;
        }
    }
}

// Definition of deleteAtPosition()
template <typename ElementType>
bool ArrayBasedList<ElementType>::deleteAtPosition(int position)
{
    // Check if list is empty or invalid position
    if (first == NULL_INDEX || position < 0 || position >= CAPACITY)
    {
        return false;
    }

    if (position == 0) // delete first element in the list
    {
        int temp = first; // temporary index for deletion
        // point first to the second element in the list
        first = nodePool.getNextOfNode(first);

        nodePool.releaseNode(temp); // delete temp (old first)
        return true;
    }
    else
    {
        int count = 1;    // Counter to stop at position - 1
        int temp = first; // To traverse the list

        // Loop until either the end of the list or we are at position - 1
        while (nodePool.getNextOfNode(temp) != NULL_INDEX && count < position)
        {
            temp = nodePool.getNextOfNode(temp);
            count++;
        }

        // temp is now the index which we must delete after

        int deleted = nodePool.getNextOfNode(temp); // index of node to be deleted
        if (deleted == NULL_INDEX)                  // temp is the last node, we cannot delete after it
        {
            return false;
        }

        // point temp to the node 2 positions after it
        nodePool.setNextOfNode(temp, nodePool.getNextOfNode(deleted));

        nodePool.releaseNode(deleted); // delete node at position
        return true;
    }
}

// Definition of search()
template <typename ElementType>
int ArrayBasedList<ElementType>::search(const ElementType &data) const
{
    int position = 0; // logical position of node with data in the list

    // Loop through the entire list
    for (int i = first; i != NULL_INDEX; i = nodePool.getNextOfNode(i))
    {
        if (nodePool.getNodeData(i) == data) // found data
        {
            return position;
        }
        position++; // increment logical position
    }

    // data not found
    return NULL_INDEX;
}

// Definition of display()
template <typename ElementType>
void ArrayBasedList<ElementType>::display(ostream &out) const
{
    if (first == NULL_INDEX) // list is empty
    {
        out << "List is empty";
    }
    else
    {
        // call nodePool method to display elements in order starting from
        // first index
        nodePool.displayInUse(out, first);
    }
    out << endl;
}

// Definition of displayFreeNodes()
template <typename ElementType>
void ArrayBasedList<ElementType>::displayFreeNodes(ostream &out) const
{
    nodePool.displayFree(out); // call nodePool method to display free nodes
}

// Overload operator<< to display list elements
template <typename ElementType>
ostream &operator<<(ostream &out, ArrayBasedList<ElementType> list)
{
    list.display(out);
    return out;
}

#endif
