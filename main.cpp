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
    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    // method to delete first value in the list
    void delete_val(string value) {
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

    // method to remove first node
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;
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

    // method to print list
    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;

    }

    // Destructor to clean up the list when it's no longer needed.
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

};

// Function to load names from file into a vector
vector<string> loadNames(const string& filename) {
    vector<string> names;
    ifstream file(filename);
    string name;
    while (getline(file, name)) {
        names.push_back(name);
    }
    return names;
}

// main function
int main() {
    srand(time(0)); // Seed for randomness
    DoublyLinkedList queue;
    vector<string> names = loadNames("names.txt");

    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; ++i) {
        queue.push_back(names[rand() % names.size()]);
        cout << "    " << names.back() << " joined the line" << endl;
    }

    for (int timeStep = 1; timeStep <= 20; ++timeStep) {
        cout << "Time step #" << timeStep << ":" << endl;

        // Check if a customer is to be served (40% probability)
        if (rand() % 100 < 40 && queue.getSize() > 0) {
            string servedCustomer = q

    
    return 0;
}