// Assignment: ASU CSE310 HW#3 Spring 2024
// Your Name: William Young
// ASU ID: 1223300156
// ASU Email address: wyoung8@asu.edu
// Description: Implements a max heap data structure to store Car objects and provides operations to manipulate the heap, 
//              including sorting cars by VIN in increasing order.
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
    private:
    struct Car* carArr;	//an array of Cars
    int capacity, size;

	public:
    MaxHeap(int capacity);
    ~MaxHeap();

	Car* getCarArr();
	int getSize();
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
 	//Add your own code
 	//----
	this -> capacity = capacity;
	size=0;
	carArr = new Car[capacity];
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	//Add your own code
 	//----
	int carCount = size;
	delete[] carArr;
	cout << "\nThe number of deleted cars is: " << carCount << endl;
}

//This is the accessor of the instance variable carArr.
Car* MaxHeap::getCarArr()
{
	return carArr;
}

//This is the accessor of the instance variable size.
int MaxHeap::getSize()
{
	return size;
}

//This is the accessor of the instance variable capacity.
int MaxHeap::getCapacity()
{
	return capacity;
}

//Given a aVin, this method returns the Car object's index inside the carArr if it find a Car with the specific aVin; otherwise it should return -1.
int MaxHeap::isFound(int aVin)
{
	for (int i = 0; i < size; i++){
		if (carArr[i].vin == aVin){
			return i;
		}
	}
	return -1;
}

//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
	if (index < 0 || index >= size)
    {
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }

    //Add your own code
    //----
    //----
	// Update the VIN of the Car object
    carArr[index].vin = oneCarWithNewVIN.vin;

	// Fix the heap property 
    while (index > 0 && carArr[parent(index)].vin < carArr[index].vin)
    {
        // Swap the Car object with its parent
        swap(carArr[index], carArr[parent(index)]);
        index = parent(index); 
    }

    return true; 

}

//Add your own code to finish other functions
//----
//----
//creates a new Car ojbect and inserts it inside the heap. updates the size and return true; otherwise return false. 
bool MaxHeap::heapInsert(int vin, string model, string make, double price)
{
	// Check if the heap has reached its capacity
    if (size == capacity)
    {
        // Double the capacity
        capacity *= 2;
        
        // Dynamically reallocate memory for the heap with doubled capacity
        Car* newCarArr = new Car[capacity];

        // Copy existing elements to the new array
        for (int i = 0; i < size; ++i) {
            newCarArr[i] = carArr[i];
        }

        // Delete the old array
        delete[] carArr;

        // Update the carArr pointer to point to the new array
        carArr = newCarArr;

        // Show message on screen
        cout << "\nReach the capacity limit. Double the capacity.\nThe new capacity now is " << capacity << endl;
    }

    // Create a new Car object with the provided information
    Car newCar;
    newCar.vin = vin;
    newCar.model = model;
    newCar.make = make;
    newCar.price = price;
    for (int i = 0; i < size; i++){
		if (carArr[i].vin == newCar.vin){
            cout << "Duplicated Car. Not added" <<endl;
			return false;
		}
	}
    
    // Insert the new Car object as the right-most node of the last level 
    carArr[size].vin = -10000; // Set dummy VIN value for the new Car
    carArr[size].model = model;
    carArr[size].make = make;
    carArr[size].price = price;
    size++; // Increment the size of the heap
    

    // Increase the VIN of the dummy Car to the new VIN
    heapIncreaseVIN(size - 1, newCar);

    return true;
}

//Creates heap from binary tree
void MaxHeap::heapify(int index)
{
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    // Find the largest among index, its left child, and its right child
    if (left < size && carArr[left].vin > carArr[largest].vin)
    {
        largest = left;
    }

    if (right < size && carArr[right].vin > carArr[largest].vin)
    {
        largest = right;
    }

    // If the largest is not the current index, swap with the largest and heapify the affected subtree
    if (largest != index)
    {
        swap(carArr[index], carArr[largest]);
        heapify(largest);
    }
}

//This is the accessor for the root of the heap, it returns the largest Car object (also root) of the max-heap. 
Car MaxHeap::getHeapMax()
{
    if (size <= 0) {
        // Returning a default-constructed Car object if the heap is empty
        return Car();
    }

    return carArr[0]; // Return the root of the heap
}

//This function extracts the root of the heap. Basically we replace the root by the last node of the heap, 
//then call heapify( ) to "float-down" the newly added root, we then decrease the size of the heap by 1. 
void MaxHeap::extractHeapMax()
{
    if (size <= 0)
    {
        return;
    }

    // Replace the root by the last node of the heap
    carArr[0] = carArr[size - 1];

    // Decrease the size of the heap
    size--;

    // Heapify the root to float it down
    heapify(0);
}

//Given a parent node's index, this function returns its left child's index inside the 1D array
int MaxHeap::leftChild(int parentIndex)
{
    return 2 * parentIndex + 1;
}

//Given a parent node's index, this function returns its right child's index inside the 1D array.
int MaxHeap::rightChild(int parentIndex)
{
    return 2 * parentIndex + 2;
}

//Given a node's index, this function returns its parent node's index inside the 1D array.
int MaxHeap::parent(int childIndex)
{
    return (childIndex - 1) / 2;
}

//This function uses the breadth-frist traversal to print out the contents of the heap.
void MaxHeap::printHeap()
{
    if (size == 0)
    {
        cout << "Empty heap, no elements" << endl;
        return;
    }

    cout << "\nHeap capacity = " << capacity << endl;
    cout << "\nHeap size = " << size << "\n" << endl;

    // Print Car objects in the heap
    for (int i = 0; i < size; ++i)
    {
        Car oneCar = carArr[i];
		cout << left;
        cout << setw(8) << oneCar.vin
             << setw(12) << oneCar.model
             << setw(12) << oneCar.make
             << setw(8) << fixed << setprecision(2) << oneCar.price << endl;
    }
}
