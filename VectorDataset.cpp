#include <iostream>
#include "VectorDataset.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
// The implementation file for the VectorDataset class. It contains the definitions of the member functions of the class.
// The member functions of the class are defined using the scope resolution operator (::).
// The VectorDataset class is a simple class that represents a dataset of DataVector objects.
// All the member functions of the class are coded here.
// This class utilises the DataVector class to store the dataset.

// The constructor of the VectorDataset class is defined here. It is a special member function of classes which initializes the object.
VectorDataset::VectorDataset()
{
    dataset.clear(); // clear the dataset. This is not necessary as the dataset will be automatically destroyed when the object is destroyed.
}

// The destructor of the VectorDataset class is defined here. It is a special member function of classes which deletes the object if it is no longer required.
VectorDataset::~VectorDataset()
{
    dataset.clear(); // clear the dataset. This is not necessary as the dataset will be automatically destroyed when the object is destroyed.
}

// The copy constructor of the VectorDataset class is defined here. It is a special member function of classes which initializes the object with a copy of another object.
VectorDataset::VectorDataset(const VectorDataset &other) : dataset(other.dataset) {} // initialize the dataset with a copy of the dataset of the other object

// The assignment operator of the VectorDataset class is defined here. It is a special member function of classes which assigns the value of one object to another object.
VectorDataset &VectorDataset::operator=(const VectorDataset &other)
{
    if (this != &other) // check for self-assignment
    {
        dataset = other.dataset; // assign the dataset of the other object to the dataset of this object
    }
    return *this; // return a reference to this object
}

// The readDataset method of the VectorDataset class is defined here. It takes a string argument and reads the dataset from a file.
void VectorDataset::readDataset(const string filename)
{
    std::ifstream file(filename); // open the file
    if (!file.is_open())          // check if the file is open
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl; // print an error message. This is not necessary as the error will be handled by the calling function.
        return;
    }

    std::string line; // string to store each line of the file
    int i = 0;
    while (std::getline(file, line)) // read each line of the file
    {
        std::istringstream iss(line); // create a string stream from the line

        DataVector dataVector;

        double value;
        while (iss >> value)
        {
            dataVector.addComponent(value); // add the value to the vector
            char comma;                     // variable to store the comma
            if (iss >> comma && comma != ',')
            {
                std::cerr << "Error: Invalid CSV format" << std::endl; // print an error message. This is not necessary as the error will be handled by the calling function.
                dataset.clear();                                       // clear the dataset
                break;
            }
        }

        // add the vector to the dataset
        dataset.push_back(dataVector);

        // Statements to check if the dataset is being read correctly
        // cout << "DataVector " << i++ << " :";
        // dataVector.print();
        // cout << endl;
    }

    file.close(); // close the file
}

// The getVector method of the VectorDataset class is defined here. It takes an integer argument and returns the DataVector at the given index.
DataVector VectorDataset::getVector(int index)
{
    return dataset[index]; // return the DataVector at the given index
}

// The size method of the VectorDataset class is defined here. It returns the size of the dataset.
int VectorDataset::size()
{
    return dataset.size(); // return the size of the dataset
}

// The clear method of the VectorDataset class is defined here. It clears the dataset.
void VectorDataset::clear()
{
    dataset.clear(); // clear the dataset
}

// The push_back method of the VectorDataset class is defined here. It takes a DataVector argument and adds it to the dataset.
void VectorDataset::push_back(const DataVector &dataVector)
{
    dataset.push_back(dataVector); // add the DataVector to the dataset
}
