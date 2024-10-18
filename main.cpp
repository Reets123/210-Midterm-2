// Midterm #2
// COMSC-210 - Ibrahim Alatig 

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // Constants for potential use in other parts of the program.

// DoublyLinkedList class
class DoublyLinkedList {
private:
    struct Node { // Node structure representing a single node in the list.
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
    };

    Node* head; // pointer to the first node
    Node* tail; // pointer to the last node

public:
    // Constructor for initializing an empty list.
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // method to insert a new node
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return; // if not exit the method
        }

        Node* newNode = new Node(value); // Create a new node with the given value.
        
        // If the list is empty
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        // Traverse to the specified position
        for (int i = 0; i < position && temp; ++i) {
            temp = temp->next;
        }

        // If position exceeds list size
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // Insert the new node
        newNode->next = temp->next; // new node's next to the current node's 
        
        newNode->prev = temp; // new node's previous to current node.
        
        if (temp->next) // If current node has a next node.
            temp->next->prev = newNode;
        else
            tail = newNode; // Update if we're adding at the end.
        
        temp->next = newNode; // Link current node next to the new node
    }

    // method to delete first value in the list
    void delete_val(int value) {
        if (!head) return; // if list empty exit

        Node* temp = head;
        // Search for the value to delete
        while (temp && temp->data != value)
            temp = temp->next;

        // If value not found
        if (!temp) return;

        // Update links to remove the node from the list
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        // Adjust connections to remove the found node.
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;  // Free memory of removed node.
    }

    // method to delte a node
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) { // If we need to delete the first position.
            pop_front();
            return;
        }

        Node* temp = head; // start from head
        
        for (int i = 1; i < pos; i++) { // find the node at position
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            temp = temp->next;
        }

        // If position doesn't exist
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        
        // Adjust connections to remove the node
        if (!temp->next) {
            pop_back();
            return;
        }

        // Update links to remove the node from the list
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // Method to add a node at the end of the list.
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // method to add node at beginning 
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // method to remove first node
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;// Temporarily hold the current head.
        
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Method to remove the last node in the list.
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = tail;
        
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Destructor to clean up the list when it's no longer needed.
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // method to print list
    void print() {
        Node* current = head;
        
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Method to print the list in reverse order.
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        
        cout << endl;
    }
};

// main function
int main() {

    
    return 0;
}