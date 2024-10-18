// Midterm #2
// COMSC-210 - Ibrahim Alatig 

//     DoublyLinkedList          
// -----------------------
//  - head: Node*                     
// - tail: Node*                     
// ---------------------
// + DoublyLinkedList()              
// + push_back(value: string)        
// + front(): string                 
// + pop_front(): void               
// + pop_back(): void                
// + delete_val(value: string): void  
// + getSize(): int                  
// + randCustomer(): string          
// + print(): void                   
// + ~DoublyLinkedList()             

//      Node            
//----------------------
// - data: string             
// - prev: Node*              
// - next: Node*              
//--------------------
// + Node(val: string, p: Node*, n: Node*) |

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// DoublyLinkedList class
class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public: 
    // Constructor to initialize an empty doubly linked list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Method to add a new node at the end of the list
    void push_back(string value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Method to get the data of the first node
    string front() {
        return head ? head->data : "";
    }
    // Method to remove the first node from the list
    void pop_front() {
        if (!head) {
            return;
        }
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Method to remove the last node from the list
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Method to remove value from the list
    void delete_val(string value) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    // method to get current size of list
    int getSize() {
        Node* temp = head;
        int count = 0;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Method to randomly select a customer from list
    string randCustomer() {
        if (!head) return "";
        int index = rand() % getSize();
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    // method to print from list
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

    // Destructor to clean up all nodes in the list
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

// Main function
int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for randomness
    DoublyLinkedList queue;
    vector<string> names = loadNames("names.txt");

    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; ++i) { // Initially adding 5 customers
        string newCustomer = names[rand() % names.size()];
        queue.push_back(newCustomer);
        cout << "    " << newCustomer << " joined the line." << endl;
    }

    for (int timeStep = 1; timeStep <= 20; ++timeStep) {
        cout << "Time step #" << timeStep << ":" << endl;

        // Check if a customer is served (40% probability)
        if (rand() % 100 < 40 && queue.getSize() > 0) {
            string servedCustomer = queue.front();
            queue.pop_front();
            cout << "    " << servedCustomer << " is served." << endl;
        }

        // Check if a new customer joins (60% probability)
        if (rand() % 100 < 60) {
            string newCustomer = names[rand() % names.size()];
            queue.push_back(newCustomer);
            cout << "    " << newCustomer << " joined the line." << endl;
        }

        // Check if the last customer leaves (20% probability)
        if (queue.getSize() > 0 && rand() % 100 < 20) {
            string leavingCustomer = queue.randCustomer();
            queue.delete_val(leavingCustomer);
            cout << "    " << leavingCustomer << " left the line before being served." << endl;
        }

        // Check if any particular customer leaves (10% probability)
        if (queue.getSize() > 0 && rand() % 100 < 10) {
            string leavingCustomer = queue.randCustomer();
            queue.delete_val(leavingCustomer);
            cout << "    " << leavingCustomer << " left the line." << endl;
        }

        // VIP customer joining (10% probability)
        if (rand() % 100 < 10) {
            string vipCustomer = names[rand() % names.size()] + " (VIP)";
            queue.push_back(vipCustomer);
            cout << "    " << vipCustomer << " joins the front of the line." << endl;
        }

        // Print current state of the line
        cout << "Resulting line: ";
        queue.print();
    }

    return 0;
}