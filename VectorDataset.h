#include <iostream>
#include "DataVector.h"
#include <vector>
using namespace std;
// The VectorDataset class is a simple class that represents a dataset of DataVector objects.
// It has a constructor, a destructor, a copy constructor, and an assignment operator.
// It has a method readDataset that takes a string argument and reads the dataset from a file.
// It has a method getVector that takes an integer argument and returns the DataVector at the given index.
// It has a method size that returns the size of the dataset.
// It has a method clear that clears the dataset.
// It has a method push_back that takes a DataVector argument and adds it to the dataset.
// The VectorDataset class is used in the kNearestNeighbors function to represent the dataset.
// This class utilises the DataVector class to store the dataset.

class VectorDataset
{
    vector<DataVector> dataset; // vector of DataVector objects.The data type defined in the vector is DataVector. This is a member variable of the class VectorDataset.

public:
    VectorDataset();                                      // constructor of the VectorDataset class. It is a special member function of classes which initializes the object.
    ~VectorDataset();                                     // destructor of the VectorDataset class. It is a special member function of classes which deletes the object if it is no longer required.
    VectorDataset(const VectorDataset &other);            // copy constructor of the VectorDataset class. It is a special member function of classes which initializes the object with a copy of another object.
    VectorDataset &operator=(const VectorDataset &other); // assignment operator of the VectorDataset class. It is a special member function of classes which assigns the value of one object to another object.
    void readDataset(string filename);                    // This method reads the dataset from a file. It takes a string argument which is the name of the file.
    DataVector getVector(int index);                      // This method returns the DataVector at the given index. It takes an integer argument which is the index of the vector.
    int size();                                           // This method returns the size of the dataset.
    void clear();                                         // This method clears the dataset.
    void push_back(const DataVector &dataVector);         // This method adds a DataVector to the dataset. It takes a DataVector argument which is the vector to be added.
};