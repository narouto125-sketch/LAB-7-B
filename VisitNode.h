#ifndef VISIT_NODE_H
#define VISIT_NODE_H

#include <string>

// ==================================================================
// STRUCTURE FILE
// One node = one visit. A doubly linked list node holds TWO links:
//   left  -> the previous node
//   right -> the next node
// so the list can be walked in both directions.
// ==================================================================
struct VisitNode
{
    int visitID;                 // unique ID
    std::string visitDate;       // main text field
    std::string diagnosis;         // extra detail
    VisitNode* left;            // previous visit (nullptr for the first node)
    VisitNode* right;           // next visit (nullptr for the last node)

    // Constructor: fills the data and starts with no neighbours
    VisitNode(int id, std::string name, std::string extra)
    {
        visitID = id;
        visitDate = name;
        diagnosis = extra;
        left = nullptr;
        right = nullptr;
    }
};

#endif
