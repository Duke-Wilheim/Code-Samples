// Assignment: ASU CSE310 HW#3 Spring 2024
// Name: William Young
// ASU ID: 1223300156
// ASU Email Address: wyoung8@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

//only include the necessary header file
//----
#include <iostream>
#include <iomanip>
#include <string>
#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);


int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;

	//declare any other variables in case you need them
	//----

    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				//Add your own code
				//----
				heap1 = new MaxHeap(capacity);

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				//Add your own code
				//----
				// Call the destructor explicitly to delete the existing heap
    			delete heap1;
				//re-initialize it with capacity 5
				//Add your own code
				//----
				heap1 = new MaxHeap(5);
				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr)
				{
                    cout << "\nEmpty heap, can NOT extract max" << endl;
				}
                else
                {
                    //Add your own code
                    //----
					cout << "Before extract heap max operation:" << endl;
        			heap1->printHeap();
        			heap1->extractHeapMax();
        			cout << "After extract heap max operation:" << endl;
        			heap1->printHeap();
                }
				break;

			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: "<<endl;
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer

				//Add your own code
				//----
				if (heap1 == nullptr)
				{
					cout << "Car with VIN: " << vin << " is NOT found" << endl;
				}
				else
				{
					int index = heap1->isFound(vin);
					if (index != -1)
					{
						cout << "Car with VIN: " << vin << " is found" << endl;
					}
					else
					{
						cout << "Car with VIN: " << vin << " is NOT found" << endl;
					}
				}
				break;

			case 'I':	//Insert a Car
				cout << "\nEnter the car model: "<<endl;
				cin >> model;

				cout << "Enter the car make: "<<endl;
				cin >> make;

				cout << "Enter the car VIN: "<<endl;
				cin >> vin;

				cout << "Enter the car price: " <<endl;
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer
				//Add your own code
				//----
				if (heap1 == nullptr)
						{
							cout << "Car \"" << model << " " << make << "\" is NOT added" << endl;
						}
						else
						{
							bool success = heap1->heapInsert(vin, model, make, price);
							if (success)
							{
								cout << "Car \"" << model << " " << make << "\" is added" << endl;
							}
							else
							{
								cout << "Car \"" << model << " " << make << "\" is NOT added" << endl;
							}
						}
				break;

			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

				//Add your own code
				//----
				if (heap1 == nullptr)
				{
					cout << "Heap is not initialized." << endl;
				}
				else
				{
					// Check if the new VIN is less than or equal to the old VIN
					if (newVIN <= vin)
					{
						cout << "Increase VIN error: new vin is smaller than current vin" << endl;
					}
					else
					{
						// Check if the old VIN exists in the heap1
						int oldIndex = heap1->isFound(vin);
						if (oldIndex == -1)
						{
							cout << "The old VIN you try to increase does not exist" << endl;
						}
						else
						{
							// Check if the new VIN already exists in the heap1
							int newIndex = heap1->isFound(newVIN);
							if (newIndex != -1)
							{
								cout << "The new VIN you entered already exists, increase VIN operation failed" << endl;
							}
							else
							{
								cout << "Before increase VIN operation:" << endl;
								heap1->printHeap();

								// Increase VIN operation
								Car newCar;
								newCar.vin = newVIN;
								heap1->heapIncreaseVIN(oldIndex, newCar);

								cout << "Car with old VIN: " << vin << " is increased to new VIN: " << newVIN << endl;
								cout << "After increase VIN operation:" << endl;
								heap1->printHeap();
							}
						}
					}
				}
			
				break;

			case 'M':	//get maximum node

			    //Add your own code
				//----
				if (heap1 == nullptr || heap1->getSize() == 0)
					{
						cout << "Empty heap, can NOT get max node" << endl;
					}
					else
					{
						Car maxCar = heap1->getHeapMax();
						cout << "\nThe maximum heap node is:" << endl;
						cout << left;
						cout << setw(8) << maxCar.vin
							<< setw(12) << maxCar.model
							<< setw(12) << maxCar.make
							<< setw(8) << fixed << setprecision(2) << maxCar.price << endl;
					}
				break;

			case 'P':	//Print heap1 contents

			    //Add your own code
				//----
				if (heap1 == nullptr || heap1->getSize() == 0)
				{
					cout << "Empty heap, no elements" << endl;
				}
				else
				{
					heap1->printHeap();
				}

				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				//Add your own code
				//----
				heapSort(heap1);
				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
    //Add your own code
	//----
	if (oneMaxHeap == nullptr || oneMaxHeap->getSize() == 0)
    {
        cout << "Empty heap." << endl;
        return;
    }

    int heapSize = oneMaxHeap->getSize();
    Car* sortedArray = new Car[heapSize]; // Array to store the sorted elements

    // Extract elements from the max heap1 and place them in the sorted array
    for (int i = heapSize - 1; i >= 0; --i)
    {
        sortedArray[i] = oneMaxHeap->getHeapMax(); // Extract max element
        oneMaxHeap->extractHeapMax(); // Remove max element from the heap
    }

    // Print the sorted array
    for (int i = 0; i < heapSize; ++i)
    {
        Car currentCar = sortedArray[i];
		cout << left;
        cout << setw(8) << currentCar.vin
             << setw(12) << currentCar.model
             << setw(12) << currentCar.make
             << setw(8) << fixed << setprecision(2) << currentCar.price << endl;
    }

    delete[] sortedArray; // Free the memory allocated for the sorted array
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
