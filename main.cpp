// COMSC-210 | Lab 21 | Christine Susic

#include <iostream>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int SIZE = 15; //array size 15
const int MIN = 1, MAX = 20; // age range 1-20
const int MIN1 = 0, MAX1 = SIZE - 1; //array 0-14
const int MIN2 = 5, MAX2 = 20; //goat objects 5-20

class Goat {
private:
    int age;
    string name, color;
    string names[SIZE] = { "Angela", "Barry", "Cynthia", "Delilah", "Eli",
                           "Francis", "Ginny", "Hector", "Isiah", "Jasper",
                           "Kendall", "Lenny", "Martha", "Nicole", "Opal" };
    string colors[SIZE] = { "Red", "Orange", "Yellow", "Green", "Blue",
                           "Purple", "Pink", "Brown", "Black", "White",
                           "Periwinkle", "Burgundy", "Rose", "Grey", "Cyan" };
public:
    //default constructor
    Goat() {
        age = (rand() % (MAX-MIN+1) + MIN);
        int rand1 = (rand() % (MAX1-MIN1+1) + MIN1);
        name = names[rand1];
        int rand2 = (rand() % (MAX1-MIN1+1) + MIN1);
        color = colors[rand2];
    }
    //parameter constructor
    Goat(int a, string n, string c) {
        age = a;
        name = n;
        color = c;
    }
    //setters and getters
    int getAge()            { return age; }
    void setAge(int a)      { age = a; }
    string getName()        { return name; }
    void setName(string n)  { name = n; }
    string getColor()       { return color; }
    void setColor(string c) { color = c; }
    //print
    void display() const {
        Goat data;
        cout << "\t";
        cout << data.getName() << " (" << data.getColor();
        cout << ", " << data.getAge() << ")" << endl;   
    }
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
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
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat g) {
        if (!head) return; // Empty list

        Node* temp = head;
        //while (temp && temp->data != g)
            //temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty";
        };
        while (current) {
            current->data.display();
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty";
        };
        while (current) {
            current->data.display();
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    //declarations
    srand(time(0));
    
    //DoublyLinkedList object
    DoublyLinkedList d;
    Goat g;
    
    int random = (rand() % (MAX2-MIN2+1) + MIN2);//random range 5-20
    for (int i = 0; i < random; ++i) {
        d.push_back(Goat());
    }
    
    //output
    cout << "Forward: " << endl;
    d.print();
    cout << "Backward: " << endl;
    d.print_reverse();
    cout << endl;
    
    //DoublyLinkedList list;
    //int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    //for (int i = 0; i < size; ++i)
        //list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    //cout << "List forward: ";
    //list.print();

    //cout << "List backward: ";
    //list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    d.~DoublyLinkedList();
    cout << "List forward: ";
    d.print();

    return 0;
}

