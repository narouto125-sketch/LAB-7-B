#include "VisitTimeline.h"
#include <iostream>
using namespace std;

// ---------------------------------------------------------------
// Constructor: an empty list has no head, tail or current node
// ---------------------------------------------------------------
VisitTimeline::VisitTimeline()
{
    head = tail = current = nullptr;
}

// ---------------------------------------------------------------
// Add a node at the end (right side) of the list
// ---------------------------------------------------------------
void VisitTimeline::InsertRight(VisitNode* node)
{
    if (node == nullptr)
        return;

    node->left = tail;       // new node points back to the old last node
    node->right = nullptr;   // nothing comes after the new last node

    if (tail != nullptr)
        tail->right = node;  // old last node points forward to the new node
    else
        head = node;         // list was empty, so it is also the first node

    tail = node;             // new node is now the last node

    if (current == nullptr)  // first node ever added becomes the current one
        current = node;
}

// ---------------------------------------------------------------
// Move current one step to the right (O(1))
// ---------------------------------------------------------------
void VisitTimeline::Next()
{
    if (current != nullptr && current->right != nullptr)
        current = current->right;
    else
        cout << "No next visit.\n";
}

// ---------------------------------------------------------------
// Move current one step to the left (O(1))
// ---------------------------------------------------------------
void VisitTimeline::Previous()
{
    if (current != nullptr && current->left != nullptr)
        current = current->left;
    else
        cout << "No previous visit.\n";
}

// ---------------------------------------------------------------
// Display the node that current points to
// ---------------------------------------------------------------
void VisitTimeline::PrintCurrent()
{
    if (current == nullptr)
    {
        cout << "The visit timeline is empty.\n";
        return;
    }

    cout << "Current Visit: " << current->visitID << " - " << current->visitDate << " - " << current->diagnosis << endl;
}

// ---------------------------------------------------------------
// Insert a node immediately after the current node (4 links)
// ---------------------------------------------------------------
void VisitTimeline::InsertAfterCurrent(VisitNode* node)
{
    if (node == nullptr)
        return;

    // Empty list: inserting "after current" is the same as inserting at the end
    if (current == nullptr)
    {
        InsertRight(node);
        return;
    }

    node->left = current;            // 1. new node's left -> current
    node->right = current->right;    // 2. new node's right -> old next node

    if (current->right != nullptr)
        current->right->left = node; // 3. old next node's left -> new node
    else
        tail = node;                 // current was the tail, so new node is the tail

    current->right = node;           // 4. current's right -> new node
}

// ---------------------------------------------------------------
// Unlink the current node and return it (the caller deletes it)
// ---------------------------------------------------------------
VisitNode* VisitTimeline::RemoveCurrent()
{
    if (current == nullptr)
        return nullptr;

    VisitNode* removed = current;
    VisitNode* previous = current->left;
    VisitNode* next = current->right;

    // Connect the previous node directly to the next node
    if (previous != nullptr)
        previous->right = next;
    else
        head = next;          // removed node was the head

    if (next != nullptr)
        next->left = previous;
    else
        tail = previous;      // removed node was the tail

    // Move current to the next node if there is one, otherwise to the previous
    current = (next != nullptr) ? next : previous;

    // Detach the removed node completely
    removed->left = nullptr;
    removed->right = nullptr;
    return removed;
}

// ---------------------------------------------------------------
// Display all nodes from the head to the tail
// ---------------------------------------------------------------
void VisitTimeline::PrintForward()
{
    cout << "\nVisit Timeline (First to Last):\n";

    if (head == nullptr)
        cout << "(empty)\n";

    // Follow the 'right' pointers until we fall off the end
    for (VisitNode* node = head; node != nullptr; node = node->right)
    {
        cout << node->visitID << " - " << node->visitDate << " - " << node->diagnosis;
        if (node == current)
            cout << " [CURRENT]";   // mark the node being reviewed
        cout << endl;
    }
}

// ---------------------------------------------------------------
// Display all nodes from the tail to the head
// ---------------------------------------------------------------
void VisitTimeline::PrintBackward()
{
    cout << "\nVisit Timeline (Last to First):\n";

    if (tail == nullptr)
        cout << "(empty)\n";

    // Follow the 'left' pointers until we fall off the start
    for (VisitNode* node = tail; node != nullptr; node = node->left)
    {
        cout << node->visitID << " - " << node->visitDate << " - " << node->diagnosis;
        if (node == current)
            cout << " [CURRENT]";
        cout << endl;
    }
}

// ---------------------------------------------------------------
// Destructor: delete every node one by one
// ---------------------------------------------------------------
VisitTimeline::~VisitTimeline()
{
    VisitNode* node = head;
    while (node != nullptr)
    {
        VisitNode* next = node->right;   // save the next node before deleting this one
        delete node;
        node = next;
    }
}
