#include <iostream>
#include <string>
#include "VisitTimeline.h"
using namespace std;

// ---------------------------------------------------------------
// Read an integer safely (re-asks if the user types letters)
// ---------------------------------------------------------------
int ReadInt(const string& prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value))
    {
        cin.clear();                  // clear the error state
        cin.ignore(1000, '\n');       // throw away the bad input
        cout << "Invalid input. " << prompt;
    }
    cin.ignore(1000, '\n');           // remove the leftover newline
    return value;
}

// ---------------------------------------------------------------
// Read a full line of text (spaces allowed)
// ---------------------------------------------------------------
string ReadText(const string& prompt)
{
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

// ---------------------------------------------------------------
// Ask the user for the details of one visit and build a node
// ---------------------------------------------------------------
VisitNode* ReadNode()
{
    int id = ReadInt("Enter Visit ID: ");
    string name = ReadText("Enter Visit Date: ");
    string extra = ReadText("Enter Diagnosis: ");
    return new VisitNode(id, name, extra);
}

// ---------------------------------------------------------------
// Print the menu
// ---------------------------------------------------------------
void ShowMenu()
{
    cout << "\n========================================\n";
    cout << "   PATIENT VISIT TIMELINE SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Display Current Visit\n";
    cout << "2. Move to Next Visit\n";
    cout << "3. Move to Previous Visit\n";
    cout << "4. Insert Visit at the End\n";
    cout << "5. Insert Visit After Current Visit\n";
    cout << "6. Remove Current Visit\n";
    cout << "7. Display Timeline from First to Last\n";
    cout << "8. Display Timeline from Last to First\n";
    cout << "9. Exit\n";
}

int main()
{
    VisitTimeline list;

    // Start with a predefined visit timeline so the menu can be tried immediately
    list.InsertRight(new VisitNode(501, "05-Jan-2026", "Fever and cough"));
    list.InsertRight(new VisitNode(502, "19-Jan-2026", "Throat infection follow-up"));
    list.InsertRight(new VisitNode(503, "02-Feb-2026", "Blood test review"));

    int choice = 0;

    // Keep showing the menu until the user chooses Exit
    do
    {
        ShowMenu();
        choice = ReadInt("Enter your choice: ");

        switch (choice)
        {
        case 1:   // show the current node
            list.PrintCurrent();
            break;

        case 2:   // move right
            list.Next();
            list.PrintCurrent();
            break;

        case 3:   // move left
            list.Previous();
            list.PrintCurrent();
            break;

        case 4:   // add at the end
            list.InsertRight(ReadNode());
            cout << "Visit added at the end.\n";
            break;

        case 5:   // add right after the current node
            list.InsertAfterCurrent(ReadNode());
            cout << "Visit inserted after the current visit.\n";
            break;

        case 6:   // remove the current node
        {
            VisitNode* removed = list.RemoveCurrent();
            if (removed == nullptr)
                cout << "The visit timeline is empty. Nothing to remove.\n";
            else
            {
                cout << "Removed: " << removed->visitDate << endl;
                delete removed;   // the caller frees the removed node
                list.PrintCurrent();
            }
            break;
        }

        case 7:   // forward traversal
            list.PrintForward();
            break;

        case 8:   // backward traversal
            list.PrintBackward();
            break;

        case 9:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 9.\n";
        }
    } while (choice != 9);

    return 0;   // destructor frees all remaining nodes
}
