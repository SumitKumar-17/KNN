#include "DataVector.h"
using namespace std;
// This is the implementation file for the DataVector class. It contains the definitions of the member functions of the class.
// The DataVector class is a simple class that represents a vector of double value data.
// All the member functions of the class are coded here. The member functions are defined using the scope resolution operator (::).

// The constructor of the DataVector class takes an integer argument, which is the dimension of the vector.
DataVector::DataVector(int dimension)
{
    v.resize(dimension); // resize the vector to the given dimension
}

// The destructor of the DataVector class is defined here. It is a special member function of classes which deletes the object if it is no longer required.
DataVector::~DataVector()
{
    v.clear(); // clear the vector. This is not necessary as the vector will be automatically destroyed when the object is destroyed.
}

// The copy constructor of the DataVector class is defined here. It is a special member function of classes which initializes the object with a copy of another object.
DataVector::DataVector(const DataVector &other) : v(other.v) {} // initialize the vector with a copy of the vector of the other object

// The assignment operator of the DataVector class is defined here. It is a special member function of classes which assigns the value of one object to another object.
DataVector &DataVector::operator=(const DataVector &other)
{
    if (this != &other) // check for self-assignment
    {
        v = other.v; // assign the vector of the other object to the vector of this object
    }
    return *this; // return a reference to this object
}

// The setDimension method of the DataVector class is defined here. It takes an integer argument and sets the dimension of the vector.
void DataVector::setDimension(int dimension)
{
    v.clear();           // clear the vector.  This is not necessary as the vector will be automatically resized when the object is resized.
    v.resize(dimension); // resize the vector to the given dimension.
}

// The overloaded operator for addition of the DataVector class is defined here. It takes a DataVector argument and returns the sum of the vectors.
DataVector DataVector::operator+(const DataVector &other)
{
    if (v.size() != other.v.size()) // check if the vectors have th same dimension
    {
        cout << "Error: vectors must have the same dimension" << endl; // print an error message. This is not necessary as the error will be handled by the calling function.
        return DataVector();                                           // return an empty vector
    }
    else
    {
        DataVector result; // create a new vector to store the result
        for (int i = 0; i < v.size(); i++)
        {
            result.v.push_back(v[i] + other.v[i]); // add the components of the vectors and store the result in the new vector
        }
        return result; // return the result. This is not necessary as the result will be automatically copied when returned.
    }
}

// The overloaded operator for subtraction of the DataVector class is defined here. It takes a DataVector argument and returns the difference of the vectors.
DataVector DataVector::operator-(const DataVector &other)
{
    if (v.size() != other.v.size()) // check if the vectors have th same dimension
    {
        cout << "Error: vectors must have the same dimension" << endl; // print an error message. This is not necessary as the error will be handled by the calling function.
        return DataVector();                                           // return an empty vector
    }
    else
    {
        DataVector result; // create a new vector to store the result
        for (int i = 0; i < v.size(); i++)
        {
            result.v.push_back(v[i] - other.v[i]); // subtract the components of the vectors and store the result in the new vector
        }
        return result;
    }
}

// The overloaded operator for dot product of the DataVector class is defined here. It takes a DataVector argument and returns the dot product of the vectors.
double DataVector::operator*(const DataVector &other)
{
    if (v.size() != other.v.size())
    {                                                                  // check if the vectors have the same dimension
        cout << "Error: vectors must have the same dimension" << endl; // print an error message. This is not necessary as the error will be handled by the calling function.
        return 0;
    }
    else
    {
        double result = 0; // initialize the result to 0
        for (int i = 0; i < v.size(); i++)
        {
            result += v[i] * other.v[i]; // add the product of the components of the vectors to the result.We are using the overloading of the * operator to multiply the components of the vectors.
        }
        return result;
    }
}

// The print method of the DataVector class is defined here. It prints the vector.
void DataVector::print() const
{
    cout << "<"; // print the components of the vector
    for (int i = 0; i < v.size() - 1; i++)
    {
        cout << v[i] << ","
             << " ";
    }
    cout << v[v.size() - 1];
    cout << ">";
    cout << endl;
}

// The norm method of the DataVector class is defined here. It takes a DataVector argument and returns the Euclidean norm of the vector.
double DataVector::norm(const DataVector &other)
{
    return sqrt((*this) * (*this)); // return the square root of the dot product of the vector with itself
}

// The dist method of the DataVector class is defined here. It takes a DataVector argument and returns the Euclidean distance between the vectors.
double DataVector::dist(const DataVector &other) const
{
    if (v.size() != other.v.size())
    {
        throw std::invalid_argument("Vectors must be of the same dimension");
    }
    double distance = 0.0;
    for (size_t i = 0; i < v.size(); ++i)
    {
        distance += std::pow(v[i] - other.v[i], 2);
    }

    return std::sqrt(distance);
    // return the square root of the dot product of the difference of the vectors with itself
}

// The setComponent method of the DataVector class is defined here. It takes an integer index and a double value and sets the value of the component at the given index.
void DataVector::setComponent(int index, double value)
{
    if (index >= 0 && index < v.size()) // check if the index is within the range of the vector
    {
        v[index] = value; // set the value of the component at the given index
    }
    else
    {
        cout << "Error: Index out of range" << endl; // print an error message. This is not necessary as the error will be handled by the calling function.
    }
}

// The addComponent method of the DataVector class is defined here. It takes a double value and adds it to the vector.
void DataVector::addComponent(double value)
{
    v.push_back(value); // add the value to the vector
}

// The getComponent method of the DataVector class is defined here. It takes an integer index and returns the value of the component at the given index.
double DataVector::getComponent(int index) const
{
    if (index >= 0 && index < v.size()) // check if the index is within the range of the vector
    {
        return v[index]; // return the value of the component at the given index
    }

    else
    {   
        // cout<<":"<<index <<":"<<v.size()<<":"<<endl;
        // cout << "Error: Index out of range-1" << endl; // print an error message. This is not necessary as the error will be handled by the calling function.
        return 0;
    }
}

// The getDimension method of the DataVector class is defined here. It returns the dimension of the vector.
int DataVector::getDimension() const
{
    return v.size();
}

double DataVector::getMedian(int dimension) const
{
    if (dimension < 0 || dimension >= v.size())
    {
        throw std::out_of_range("Dimension out of range");
    }

    // Make a copy of the vector elements along the specified dimension
    vector<double> dimValues(v.size());
    for (size_t i = 0; i < v.size(); ++i)
    {
        dimValues[i] = v[i];
    }

    // Sort the copied vector
    sort(dimValues.begin(), dimValues.end());

    // If the size of the dimension is odd, return the middle element
    // Otherwise, return the average of the two middle elements
    size_t midIndex = dimValues.size() / 2;
    if (dimValues.size() % 2 == 1)
    {
        return dimValues[midIndex];
    }
    else
    {
        return (dimValues[midIndex - 1] + dimValues[midIndex]) / 2.0;
    }
}

void DataVector::readDataset(const string &filename, vector<DataVector> &dataset)
{
    // cout<<"reading"<<endl;
    std::ifstream file(filename); // open the file
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line; // string to store each line of the file
    while (std::getline(file, line))
    {

        // cout<<"readline"<<endl;
        std::istringstream iss(line); // create a string stream from the line

        DataVector dataVector;

        double value;
        while (iss >> value)
        {
            dataVector.addComponent(value); // add the value to the vector

            char comma; // variable to store the comma
            if (iss >> comma && comma != ',')
            {
                std::cerr << "Error: Invalid CSV format" << std::endl;
                dataset.clear(); // clear the dataset
                break;
            }
        }

        // add the vector to the dataset
        //  dataVector.print();
        dataset.push_back(dataVector);
    }

    file.close(); // close the file
}

bool DataVector::operator==(const DataVector &other) const
{
    // Compare the data vectors element-wise
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] != other.v[i])
        {
            return false;
        }
    }

    return true;
}

void DataVector::randomize()
{
    // Randomize the components of the vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (double &component : v)
    {
        component = dis(gen);
    }
}

double DataVector::dot(const DataVector &other) const
{
    double result = 0.0;
    int dimension = min(getDimension(), other.getDimension());
    for (int i = 0; i < dimension; ++i)
    {
        result += v[i] * other.getComponent(i);
    }
    return result;
}

void DataVector::normalize()
{
    double norm = 0.0;
    for (double component : v)
    {
        norm += component * component;
    }
    norm = std::sqrt(norm);
    for (double &component : v)
    {
        component /= norm;
    }
}
