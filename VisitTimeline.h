#ifndef VISIT_LIST_H
#define VISIT_LIST_H

#include "VisitNode.h"

// ==================================================================
// CLASS FILE - doubly linked list (declarations only)
// The definitions of the member functions are in VisitTimeline.cpp
// ==================================================================
class VisitTimeline
{
private:
    VisitNode* head;      // first node in the visit timeline
    VisitNode* tail;      // last node in the visit timeline
    VisitNode* current;   // node currently being reviewed

public:
    VisitTimeline();                                  // constructor
    ~VisitTimeline();                                 // destructor (frees all nodes)

    // Copying is disabled: two lists must never share the same nodes
    VisitTimeline(const VisitTimeline&) = delete;
    VisitTimeline& operator=(const VisitTimeline&) = delete;

    void InsertRight(VisitNode* node);             // add at the end
    void InsertAfterCurrent(VisitNode* node);      // add right after the current node
    VisitNode* RemoveCurrent();                    // unlink and return the current node

    void Next();                                // move current to the right
    void Previous();                            // move current to the left

    void PrintCurrent();                        // show the current node
    void PrintForward();                        // first -> last
    void PrintBackward();                       // last -> first
};

#endif
