#include <iostream> // for the input and output
#include <string>   // for using string variables
#include <limits>   // for handling input errors
#include <memory>   // for future smart pointer use if needed

using namespace std;

// CLASS DEFINITIONS
// ------------------

// Base class for all Plants
class Plant {
public:
    // Constructor sets all the plant details
    Plant(string plantName, string growMonths, string waterFreq,
          double avgSize, string tempRange, double price)
        : name(plantName), bestMonths(growMonths), watering(waterFreq),
          size(avgSize), temp(tempRange), price(price) {}

    // Virtual function to display plant info
    virtual void print() const {
        cout << "Plant: " << name << "\n  Best Months: " << bestMonths
             << "\n  Watering: " << watering << "\n  Avg Size: " << size << "cm"
             << "\n  Temp Range: " << temp << "\n  Price: $" << price << endl;
    }

    // Getter for name
    string getName() const { return name; }

    // Getter for price
    double getPrice() const { return price; }

    // Virtual destructor to allow proper cleanup
    virtual ~Plant() {}

protected:
    // Plant attributes
    string name, bestMonths, watering, temp;
    double size;
    double price;
};

// Derived class for Vegetables
class Vegetable : public Plant {
public:
    // Constructor passes values to Plant constructor
    Vegetable(string n, string m, string w, double s, string t, double p)
        : Plant(n, m, w, s, t, p) {}

    // Overridden print function
    void print() const override {
        cout << "[Vegetable]\n";
        Plant::print();
    }
};

// Derived class for Fruits
class Fruit : public Plant {
public:
    // Constructor passes values to Plant constructor
    Fruit(string n, string m, string w, double s, string t, double p)
        : Plant(n, m, w, s, t, p) {}

    // Overridden print function
    void print() const override {
        cout << "[Fruit]\n";
        Plant::print();
    }
};

// Node structure for linked list
struct Node {
    Plant* plant; // pointer to Plant object
    Node* next;   // pointer to next Node

    // Node constructor
    Node(Plant* p) : plant(p), next(nullptr) {}
};

// Class that manages the list of plants
class PlantManager {
private:
    Node* head; // start of the linked list

    // Recursive function to delete the list
    void deleteList(Node* node) {
        if (node != nullptr) {
            deleteList(node->next); // delete the next node
            delete node->plant;     // delete the plant data
            delete node;            // delete the node itself
        }
    }

public:
    // Constructor initializes empty list
    PlantManager() : head(nullptr) {}

    // Destructor deletes the whole list
    ~PlantManager() {
        deleteList(head);
    }

    // Add a new plant to the list
    void addPlant(Plant* plant) {
        Node* newNode = new Node(plant); // create new node
        if (head == nullptr) { // if list is empty
            head = newNode;
        } else { // otherwise, add to end
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display all plants
    void displayAll() const {
        Node* temp = head;
        while (temp != nullptr) {
            temp->plant->print(); // call print function
            cout << "-------------------\n";
            temp = temp->next;
        }
    }

    // Search for a plant by name
    void searchByName(const string& name) const {
        Node* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->plant->getName() == name) { // if names match
                cout << "Plant found:\n";
                temp->plant->print();
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No plant with name '" << name << "' found.\n";
        }
    }

    // Sort the plants by price (bubble sort)
    void sortByPrice() {
        if (!head) return; // nothing to sort if list is empty
        bool swapped;
        do {
            swapped = false;
            Node* temp = head;
            while (temp->next != nullptr) {
                if (temp->plant->getPrice() > temp->next->plant->getPrice()) {
                    swap(temp->plant, temp->next->plant); // swap plants
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped); // keep sorting until no swaps
    }
};

// MAIN FUNCTION
int main() {
    PlantManager manager; // create manager object

    // Add some plants to the list
    manager.addPlant(new Vegetable("Lettuce", "March-May", "Every 2 days", 5, "10-18°C", 1.5));
    manager.addPlant(new Fruit("Strawberry", "April-June", "Every 3 days", 8, "15-22°C", 2.0));
    manager.addPlant(new Vegetable("Carrot", "Feb-Apr", "Every 4 days", 10, "8-16°C", 1.2));
    manager.addPlant(new Fruit("Tomato", "May-Aug", "Daily", 15, "18-27°C", 2.5));
    manager.addPlant(new Vegetable("Spinach", "Feb-Mar", "Every 2 days", 6, "5-18°C", 1.8));
    manager.addPlant(new Fruit("Blueberry", "May-Jul", "Every 3 days", 12, "16-21°C", 3.0));
    manager.addPlant(new Vegetable("Zucchini", "June-Aug", "Every 2 days", 20, "20-25°C", 2.3));

    // Display all plants
    cout << "\n-- All Plants --\n";
    manager.displayAll();

    // Sort plants by price and display
    cout << "\n-- Sorted by Price --\n";
    manager.sortByPrice();
    manager.displayAll();

    // Ask user to search for a plant
    cout << "\n-- Search by Name --\n";
    string searchName;
    cout << "Enter plant name to search: ";
    getline(cin, searchName); // get full line input

    if (!searchName.empty()) {
        manager.searchByName(searchName); // perform search
    } else {
        cout << "Invalid input. Search aborted.\n";
    }

    return 0; // end program
}
