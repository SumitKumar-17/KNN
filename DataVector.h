#include <iostream>
#include <vector>

using namespace std;

// The DataVector class is a simple class that represents a vector of double value data.
// It has a constructor that takes an integer argument, which is the dimension of the vector.
// It has a destructor, a copy constructor, and an assignment operator.
// It has a method setDimension that takes an integer argument and sets the dimension of the vector.
// It has overloaded operators for addition, subtraction, and dot product.
// It has a method print that prints the vector.
// It has a method norm that takes a DataVector argument and returns the Euclidean norm of the vector.
// It has a method dist that takes a DataVector argument and returns the Euclidean distance between the vectors.
// It has a method setComponent that takes an integer index and a double value and sets the value of the component at the given index.
// It has a method addComponent that takes a double value and adds it to the vector.
// The DataVector class is used in the kNearestNeighbors function to represent the test vector and the vectors in the dataset.
class DataVector
{
    vector<double> v; // vector of double values

public:
    DataVector(int dimension = 0);                  // constructor with default argument for dimension (0). This is a special member function of classes which initializes the object.
    ~DataVector();                                  // destructor .This is a special member function of classes which deletes the object if it is no longer required.
    DataVector(const DataVector &other);            // copy constructor. This is a special member function of classes which initializes the object with a copy of another object.
    DataVector &operator=(const DataVector &other); // assignment operator. This is a special member function of classes which assigns the value of one object to another object.
    void setDimension(int dimension);               // method to set the dimension of the vector. This is a member function of the class DataVector.
    DataVector operator+(const DataVector &other);  // overloaded operator for addition. This is a member function of the class DataVector.
    DataVector operator-(const DataVector &other);  // overloaded operator for subtraction. This is a member function of the class DataVector.
    double operator*(const DataVector &other);      // overloaded operator for dot product. This is a member function of the class DataVector.

    void print();                         // method to print the vector. This is a member function of the class DataVector.
    double norm(const DataVector &other); // method to calculate the Euclidean norm of the vector. This is a member function of the class DataVector.
    double dist(const DataVector &other); // method to calculate the Euclidean distance between two vectors. This is a member function of the class DataVector.

    void setComponent(int index, double value); // method to set the value of a component at a given index. This is a member function of the class DataVector.
    void addComponent(double value);            // method to add a value to the vector. This is a member function of the class DataVector.
};
