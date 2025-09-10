// ASU CSE310 Spring 2024 Assignment #1
// Name: William Young  
// ASU ID: 1223300156
// Description: This program creates a LinkedList of Cars. It stores a cares vin, price, model, and make.
//              It has 8 functions that manipulate the list in some way ie: adding a car or removing one by it's vin.
//              It has a destuctor that deletes the linked list and clears the memory.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Car represents a Car information
struct Car
{
    string model, make;
    int vin;            //vehicle identification number
    double price;
    struct Car* next;
};

//class LinkedList will contains a linked list of Cars
class LinkedList
{
    private:
        struct Car* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findCar(int aVin);
        bool addCar(string model, string make, int vin, double price);
        bool removeByVin(int aVin);
        bool removeByModelAndMake(string model, string make);
        bool changeCarInfo(int aVin, string newModelAndMake);
        bool updateCarPrice(int aVin, double newPrice);
        void printCarListByMake(string make);
        void printCarList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    //add your own code
    //----
    head = NULL;
    
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	//add your own code
    //----
    int carCount = 0;  // Initialize carCount to 0

    // Iterate through the linked list and delete each node
    Car* current = head;
    Car* next;
    while (current != nullptr) //Iterates through the list and deletes the current node until the list is empty
    {
        next = current->next;  // Save the next pointer
        delete current;        // Delete the current node
        current = next;        // Move to the next node
        carCount++;            // Increment carCount
    }

    head = nullptr;  // Set head to nullptr after deleting all nodes

    // Print the number of nodes deleted
    cout << "The number of deleted Car is: " << carCount << "\n";
}

//A function to identify if the parameterized Car is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
	//add your own code
    //----
    Car* current = head;
    while (current != NULL)
    {
        if (current->vin == aVin)
            return true;
        current = current->next;
    }
    return false;
}

//Creates a new Car and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Cars by their make and model, i.e.
//first by make, if two cars have same makes, then we will list them by model. Note: each Car
//has a unique vin, the vehicle identification number, but may have the same make and model.
//In case two Cars have same make and model, they should be inserted according to the
//increasing order of their vins.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
     //if the Car already exist, return false
     //add your own code
     //----
     if (findCar(vin))
    {
        cout << "Duplicated Car. Not added.\n";
        return false;
    }

    //add your own code
    //----
    //creates new car
    Car* newCar = new Car;
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    newCar->next = NULL;

    //maintains order of cars and returns true

    //inserts the new car alphabetically based on make, model, and vin
    if (head == nullptr || (make < head->make) || (make == head->make && model < head->model) ||
        (make == head->make && model == head->model && vin < head->vin))
    {
        newCar->next = head;
        head = newCar;
    }
    else
    {
        Car* current = head;
        Car* previous = nullptr;

    //adjusts list to account for new car
        while (current != nullptr && (make > current->make || (make == current->make && model > current->model) ||
                                       (make == current->make && model == current->model && vin > current->vin)))
        {
            previous = current;
            current = current->next;
        }

        newCar->next = current;
        previous->next = newCar;
    }

    return true; 
}

//Removes the specified Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
 {
	//add your own code
    //----
    //Check if the list is empty
    if (head == nullptr)
    {
        return false;
    }

    Car* current = head;
    Car* previous = nullptr;

    //Check if the Car to be removed is the first node
    if (current->vin == aVin)
    {
        head = current->next;
        delete current;
        return true;
    }

    //Search for the Car in the middle or at the end
    while (current != nullptr && current->vin != aVin)
    {
        previous = current;
        current = current->next;
    }

    //Check if the Car was not found
    if (current == nullptr)
    {
        return false;
    }

    //Remove the Car from the list and return true
    previous->next = current->next;
    delete current;
    return true;
 }

//Removes the given Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Cars with
//the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
	//add your own code
    //----
    //Check if the list is empty
    if (head == nullptr)
    {
        cout << "No such Car found.";
        return false;
    }

    Car* current = head;
    Car* previous = nullptr;
    bool removed = false;

    while (current != nullptr)
    {
        //Check if the current Car matches the specified model and make
        if (current->model == model && current->make == make)
        {
            //Remove the Car from the list
            if (previous == nullptr)
            {
                //Removing the first node
                head = current->next;
                delete current;
                current = head;  
            }
            else
            {
                //Removing a node in the middle or at the end
                previous->next = current->next;
                delete current;
                current = previous->next;  
            }

            removed = true;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (removed)
    {
        return true;
    }
    else
    {
        cout << "No such Car found.";
        return false;
    }

}

//Modifies the data of the given Car. Return true if it modifies successfully and
//false otherwise. Note: after changing a Car model and make, the linked list must still
//maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
   //split newModelAndMake string to get model and make accordingly
   //add your own code
   //----
    size_t spacePos = newModelAndMake.find(' ');
    if (spacePos == string::npos)
    {
        return false;
    }

    string newModel = newModelAndMake.substr(0, spacePos);
    string newMake = newModelAndMake.substr(spacePos + 1);

   //add your own code
   //----
   // Search for the Car with the specified VIN
    Car* current = head;
    Car* previous = nullptr;

    while (current != nullptr && current->vin != aVin)
    {
        previous = current;
        current = current->next;
    }

    // Check if the Car with the specified VIN was found
    if (current == nullptr)
    {
        return false;
    }

    // Update the Car's model and make
    current->model = newModel;
    current->make = newMake;

    // Reorganize the linked list to maintain alphabetical order
    if (previous == nullptr || (newMake < head->make) || (newMake == head->make && newModel < head->model))
    {
        // The Car is already in the correct position or needs to be moved to the beginning
        
    }
    else
    {
        // Remove the Car from its current position
        previous->next = current->next;

        // Insert the Car into the correct position
        Car* temp = head;
        Car* tempPrevious = nullptr;

        while (temp != nullptr && (newMake > temp->make || (newMake == temp->make && newModel > temp->model)))
        {
            tempPrevious = temp;
            temp = temp->next;
        }

        if (tempPrevious == nullptr)
        {
            // Insert at the beginning
            current->next = head;
            head = current;
        }
        else
        {
            // Insert in the middle or at the end
            current->next = temp;
            tempPrevious->next = current;
        }
    }

    
    return true;
}


bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
	//add your own code
    //----
    // Search for the Car with the specified VIN
    Car* current = head;

    while (current != nullptr && current->vin != aVin)
    {
        current = current->next;
    }

    // Check if the Car with the specified VIN was found
    if (current == nullptr)
    {
        cout << "Car is NOT inside the list, cannot change its price.\n";
        return false;
    }

    // Update the Car's price
    current->price = newPrice;
    return true;
}

//Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    //add your own code
    //----
// Check if the list is empty
    if (head == nullptr)
    {
        cout << "The list is empty.\n";
        return;
    }

    Car* temp = head;
    bool carsFound = false;

    // Traverse through the linked list
    while (temp != nullptr)
    {
        // Check if the current Car has the specified make
        if (temp->make == make)
        {
            // Print the Car information
            cout << left    << setw(12) << temp->model
                << left    << setw(12) << temp->make
                << right   << setw(8) << temp->vin
                << setw(10) << fixed << setprecision(2) << temp->price << "\n";
                carsFound = true;
        }

        temp = temp->next;  // Move to the next node
    }

    // Check if no Cars with the specified make were found
    if (!carsFound)
    {
        cout << "No Cars with the specified make found.\n";
    }
 }

//Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    //add your own code
    //----
// Check if the list is empty
    if (head == nullptr)
    {
        cout << "The list is empty.\n";
        return;
    }

    Car* temp = head;

    // Traverse through the linked list
    while (temp != nullptr)
    {
        // Print the Car information
        cout << left    << setw(12) << temp->model
             << left    << setw(12) << temp->make
             << right   << setw(8) << temp->vin
             << setw(10) << fixed << setprecision(2) << temp->price << "\n";

        temp = temp->next;  // Move to the next node
    }
}
