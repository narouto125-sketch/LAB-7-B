# Lab 07 - Part B: Patient Visit Timeline (Doubly Linked List)

Individual project: Hospital Management System (extended).

## Folder structure

| File | Purpose |
|------|---------|
| `main.cpp` | `main()` function and the menu-driven console interface |
| `VisitNode.h` | **Structure file** - the doubly linked node (`left` / `right`) |
| `VisitTimeline.h` | **Class file** - class declaration |
| `VisitTimeline.cpp` | **Class member function file** - all member function definitions |

`main.cpp` is linked to the other files through the header files (`#include "..."`).

## Compile and run

```
g++ main.cpp VisitTimeline.cpp -o program
./program          # on Windows: program.exe
```

## Real-world problem
A doctor reviews one patient's medical history as a timeline of visits. While reviewing, the doctor must move **back** to an earlier visit and **forward** to a later one, insert a missed visit record right after the visit being reviewed, and remove a wrongly entered visit.

## Why a doubly linked list?
- Navigation is needed in both directions, and each visit stores `left` (earlier visit) and `right` (later visit).
- A `current` pointer marks the visit under review; moving with `Next()` / `Previous()` is O(1).
- Inserting after or removing the current visit only re-links its neighbours; the previous node is reached directly through `left`, with no searching (a singly linked list would need a search).

## Node design
```cpp
struct VisitNode {
    int visitID;
    std::string visitDate;
    std::string diagnosis;
    VisitNode* left;    // earlier visit
    VisitNode* right;   // later visit
};
```

