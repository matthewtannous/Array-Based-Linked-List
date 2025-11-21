/*-- NodePool.h ----------------------------------------------------------------

    This header file defines the data type NodePool for processing node pools
    (collections of nodes) used to manage Array-based Lists.

    Basic operations are:
        Constructor: Constructs NodePool as a free list
        acquireNode: Acquire first free node
        releaseNode: Release previously used node
        setNode: Assigns both the data and next fields of a specific node.
        displayFree: Outputs the indices of all currently free nodes in the pool.
        displayInUse: Outputs the data of all nodes currently in use, starting
                      from a specified head index in a client-managed list.
        getNextOfNode: Retrieves the next index stored in a specific node.
        setNextOfNode: Updates the next index of a specific node.
        getNodeData: Returns the data stored in a specific node.


    Class Invariant:
        1. The node pool elements are stored in positions 0, 1,..., CAPACITY - 1
        2. freeHead stores the index of the first free node, or NULL_INDEX if
            all nodes are in use.
        3. Every free node is linked to the next free node through its 'next'
           field; used nodes are controlled by the client
           (e.g., as part of another list structure).
------------------------------------------------------------------------------*/
#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <iostream>
using namespace std;

const int CAPACITY = 10;
const int NULL_INDEX = -1;

template <typename ElementType>
class NodePool
{
private:
    /** Private class Node */
    class Node
    {
    public:
        /******** Member Functions ********/

        /***** Class constructors *****/
        Node();
        /*----------------------------------------------------------------------
            Construct a default Node object.

            Precondition:  None.
            Postcondition: A node object is constructed; next is initialized to
                           NULL_INDEX (default value); data contains a garbage
                           value.
        ----------------------------------------------------------------------*/

        Node(int next);
        /*----------------------------------------------------------------------
            Construct a Node object.

            Precondition:  0 <= next < CAPACITY or next == -1
            Postcondition: A node object is constructed; next is initialized
                           to next parameter; data contains a garbage value.
        ----------------------------------------------------------------------*/

        Node(ElementType data, int next);
        /*----------------------------------------------------------------------
            Construct a Node object.

            Precondition:  0 <= next < CAPACITY or next == -1
            Postcondition: A node object is constructed; next is initialized to
                           next parameter; data is initialized to data parameter.
        ----------------------------------------------------------------------*/

        /******** Data members ********/
        ElementType data; // node data
        int next;         // index of next element in node pool
    };

public:
    /******** Member Functions ********/

    /***** Class constructor *****/
    NodePool();
    /*--------------------------------------------------------------------------
        Construct a NodePool object.

        Precondition:  None.
        Postcondition: A default NodePool object is created as a free list;
                       each node points to the next node in the array,
                       except the last node which points to NULL_INDEX.
    --------------------------------------------------------------------------*/

    int acquireNode();
    /*--------------------------------------------------------------------------
        Acquire first free node from pool.

        Precondition:  None.
        Postcondition: If there is a free node in the pool, returns the index
                       of the free node and removes it from the free list.
                       Otherwise, returns NULL_INDEX.
    --------------------------------------------------------------------------*/

    bool releaseNode(int index);
    /*--------------------------------------------------------------------------
        Release previously used node.

        Precondition:  0 <= index < CAPACITY
        Postcondition: Release node at index, inserting it at the front of
                       the free list. Returns true if index is valid,
                       false otherwise.
    --------------------------------------------------------------------------*/

    void setNode(int index, const ElementType &data, int next);
    /*--------------------------------------------------------------------------
        Set the data and next fields of the node at the specified index.

        Precondition:  0 <= index < CAPACITY.
        Postcondition: The node at position 'index' has its data field set to
                       'data' and its next field set to 'next'.
------------------------------------------------------------------------------*/

    void displayFree(ostream &out) const;
    /*--------------------------------------------------------------------------
        Display all free nodes in the node pool.

        Precondition:  None.
        Postcondition: Outputs to the given ostream the indices of all nodes
                       currently in the free list, in the order they appear
                       starting from freeHead.
------------------------------------------------------------------------------*/

    void displayInUse(ostream &out, int firstUsed) const;
    /*--------------------------------------------------------------------------
        Display all nodes currently in use, starting from a given index.

        Precondition:  0 <= firstUsed < CAPACITY or firstUsed == -1
                       The client must ensure that nodes starting from
                       'firstUsed' form a valid linked structure using the
                       'next' fields.
        Postcondition: Outputs the data stored in each node starting from
                       'firstUsed', following next pointers until NULL_INDEX is
                       reached.
------------------------------------------------------------------------------*/

    int getNextOfNode(int index) const;
    /*---------------------------------------------------------------------------
        Retrieve the next index stored in the node at the specified position.

        Precondition:  0 <= index < CAPACITY.
        Postcondition: Returns the value of nodePool[index].next.
---------------------------------------------------------------------------*/

    void setNextOfNode(int index, int next);
    /*---------------------------------------------------------------------------
        Update the next field of the node at the specified index.

        Precondition:  0 <= index < CAPACITY.
        Postcondition: The node at 'index' has its next field updated to the
                       specified 'next' value (which may be another valid index
                       or NULL_INDEX).
---------------------------------------------------------------------------*/

    ElementType getNodeData(int index) const;
    /*---------------------------------------------------------------------------
        Retrieve the data stored in the node at the specified index.

        Precondition:  0 <= index < CAPACITY.
        Postcondition: Returns the ElementType data stored in nodePool[index].
---------------------------------------------------------------------------*/

private:
    Node nodePool[CAPACITY]; // Pool nodes containing data
    int freeHead;            // Index of first free node in the linked free list

}; // end of class declaration

/**************** FUNCTION DEFINITIONS ****************************************/

// Definition of Node no-arg constructor
template <typename ElementType>
NodePool<ElementType>::Node::Node()
    : next(NULL_INDEX) {} // data is garbage

// Definition of Node constructor with one parameter next
template <typename ElementType>
NodePool<ElementType>::Node::Node(int next)
    : next(next) {} // data is garbage

// Definition of Node constructor with two parameters data and next
template <typename ElementType>
NodePool<ElementType>::Node::Node(ElementType data, int next)
    : data(data), next(next) {}

// Definition of NodePool constructor
template <typename ElementType>
NodePool<ElementType>::NodePool() : freeHead(0)
{
    // Link all nodes into a free list
    for (int i = 0; i < CAPACITY - 1; i++)
        nodePool[i].next = i + 1;

    nodePool[CAPACITY - 1].next = NULL_INDEX; // last node points to NULL
    freeHead = 0;                             // free list starts at node 0
}

// Definition of acquireNode()
template <typename ElementType>
int NodePool<ElementType>::acquireNode()
{
    if (freeHead == NULL_INDEX)
        return NULL_INDEX; // no free nodes

    int index = freeHead;              // take first free node
    freeHead = nodePool[index].next;   // move head to next free node
    nodePool[index].next = NULL_INDEX; // disconnect from free list
    return index;
}

// Definition of releaseNode()
template <typename ElementType>
bool NodePool<ElementType>::releaseNode(int index)
{
    if (index < 0 || index >= CAPACITY)
        return false; // invalid index

    // Insert node at the front of the free list
    nodePool[index].next = freeHead;
    freeHead = index;
    return true;
}

// Definition of setNode()
template <typename ElementType>
void NodePool<ElementType>::setNode(int index, const ElementType &data, int next)
{
    nodePool[index].data = data; // change data of node at index
    nodePool[index].next = next; // change next of node at index
}

// Definition of displayFree()
template <typename ElementType>
void NodePool<ElementType>::displayFree(ostream &out) const
{
    if (freeHead == NULL_INDEX) // NodePool is full
    {
        out << "List is full. No free nodes.\n";
    }
    else
    {
        out << "Free nodes: ";
        // Loop through entire free list
        for (int i = freeHead; i != NULL_INDEX; i = nodePool[i].next)
        {
            out << i;                           // index of the node in nodePool array
            if (nodePool[i].next != NULL_INDEX) // check if not last element
            {
                out << ", ";
            }
        }
    }
}

// Definition of displayInUse()
template <typename ElementType>
void NodePool<ElementType>::displayInUse(ostream &out, int firstUsed) const
{
    // Loop through the nodePool array starting from given index
    for (int i = firstUsed; i != NULL_INDEX; i = nodePool[i].next)
    {
        out << nodePool[i].data;            // display data
        if (nodePool[i].next != NULL_INDEX) // check if not last element
        {
            out << ", ";
        }
    }
}

// Definition of getNextOfNode()
template <typename ElementType>
int NodePool<ElementType>::getNextOfNode(int index) const
{
    return nodePool[index].next; // Get the next of node at index
}

// Definition of setNextOfNode()
template <typename ElementType>
void NodePool<ElementType>::setNextOfNode(int index, int next)
{
    // Set the next of node at index to next parameter
    nodePool[index].next = next;
}

// Definition of getNodeData()
template <typename ElementType>
ElementType NodePool<ElementType>::getNodeData(int index) const
{
    return nodePool[index].data; // get data of node at index
}

#endif
