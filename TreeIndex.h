#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <algorithm>
#include "DataVector.h"
using namespace std;

//This class is used to store the data in the tree. 
//It is a simple class that stores the data and the index of the data in the original dataset.
class Node
{
public:
    bool isLeaf;  // True if this node is a leaf node
    int splitDim; // Dimension used to split the data
    vector<int> vectorIndices; // Indices of vectors stored in this node
    Node *leftChild;  // Pointer to the left child
    Node *rightChild;  // Pointer to the right child

    Node() : isLeaf(false), splitDim(0), leftChild(nullptr), rightChild(nullptr) {}  // Constructor
};

//This class is used to store the data in the tree.It is  the base class for the KDTreeIndex and RPTreeIndex classes.
//It is a singleton class that provides the interface for the KDTreeIndex and RPTreeIndex classes.
//The KDTreeIndex and RPTreeIndex classes are used to build the KDTree and RPTree respectively.
class TreeIndex
{
protected:
    TreeIndex() {}  // Constructor
    ~TreeIndex() {}  // Destructor

public:
    //These functions are pure virtual functions that must be implemented by the KDTreeIndex and RPTreeIndex classes.
    static TreeIndex &GetInstance();  // Get the instance of the TreeIndex class
    virtual void AddData(const vector<DataVector> &newDataset) = 0;  // Add data to the tree
    virtual void RemoveData(const vector<DataVector> &dataToRemove) = 0;  // Remove data from the tree
    virtual void MakeTree() = 0;  // Build the tree
    virtual void Search(const DataVector &testVector, int k) = 0; // Search the tree
};

//This is derived from the TreeIndex class and is used to build the KDTree.
//The KDTree is a binary tree that is used to store the data in a k-dimensional space.
//The KDTree is used to perform k-nearest neighbor search.
class KDTreeIndex : public TreeIndex
{
public:
    int M;  // Variable to store the Leaf size
    Node *root;  // Pointer to the root node which is the top node of the tree
    vector<DataVector> dataset;  // Vector to store the dataset.This vector contains the data that is used to build the tree.
    Node *getRoot() const  // Get the root node
    {
        return root;
    }
    static KDTreeIndex &GetInstance(int leafSize=200);  // Get the instance of the KDTreeIndex class
    void buildTree(Node *&node, const vector<int> &indices);  // Build the tree. This function is called recursively to build the tree.
    void MakeTree();  // Build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    std::function<bool(const DataVector &)> ChooseRule(const std::vector<int> &indices, int &splitDim); // Choose the rule to split the data. This function is used to choose the rule to split the data.
    void searchTree(Node *node, const DataVector &testVector, int k, vector<int> &nearestIndices, vector<double> &distances); // Search the tree. This function is used to search the tree.
    void AddData(const vector<DataVector> &newDataset);  // Add data to the tree. This function is used to add data to the tree. It calls the buildTree function to build the tree.
    void RemoveData(const vector<DataVector> &dataToRemove);  // Remove data from the tree. This function is used to remove data from the tree. It calls the buildTree function to build the tree.
    void Search(const DataVector &testVector, int k); // Search the tree. This function is used to search the tree. It calls the searchTree function to search the tree.
    void printNodeIndices(Node *node, int depth); // Print the indices of the nodes. This function is used to print the indices of the nodes in the tree. It is used for debugging purposes.

private:
    KDTreeIndex(int leafSize) : root(nullptr), M(leafSize) {} // Setting M to 200 as default. Constructor . This is a private constructor.
    ~KDTreeIndex() {}  // Destructor. This is a private destructor.
};

//This is derived from the TreeIndex class and is used to build the RPTree. 
//The RPTree is a binary tree that is used to store the data in a k-dimensional space.
//The RPTree is used to perform k-nearest neighbor search.
class RPTreeIndex : public TreeIndex
{
public:
    int M;  // Variable to store the Leaf size
    Node *root; // Pointer to the root node which is the top node of the tree. This is the entry point to the tree.
    vector<DataVector> dataset; // Vector to store the dataset. This vector contains the data that is used to build the tree. 
    Node *getRoot() const // Get the root node. This function is used to get the root node of the tree.
    {
        return root;
    }
    static RPTreeIndex &GetInstance(int leafSize=200); // Get the instance of the RPTreeIndex class. This function is used to get the instance of the RPTreeIndex class.
    void buildTree(Node *&node, const vector<int> &indices); // Build the tree. This function is called recursively to build the tree. 
    void MakeTree(); // Build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    std::function<bool(const DataVector &)> ChooseRule(const std::vector<int> &indices, int &splitDim); // Choose the rule to split the data. This function is used to choose the rule to split the data.
    void searchTree(Node *node, const DataVector &testVector, int k, vector<int> &nearestIndices, vector<double> &distances); // Search the tree. This function is used to search the tree.
    void AddData(const vector<DataVector> &newDataset); // Add data to the tree. This function is used to add data to the tree. It calls the buildTree function to build the tree.
    void RemoveData(const vector<DataVector> &dataToRemove); // Remove data from the tree. This function is used to remove data from the tree. It calls the buildTree function to build the tree.
    void Search(const DataVector &testVector, int k); // Search the tree. This function is used to search the tree. It calls the searchTree function to search the tree.
    void printNodeIndices(Node *node, int depth); // Print the indices of the nodes. This function is used to print the indices of the nodes in the tree. It is used for debugging purposes.

private:
    
    RPTreeIndex(int leafSize) : root(nullptr), M(leafSize) {} // Setting M to 200 as default. Constructor. This is a private constructor.
    ~RPTreeIndex() {}  // Destructor. This is a private destructor.
};
