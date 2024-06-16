#include <iostream>
#include <vector>
#include "TreeIndex.h"

using namespace std;

int main()
{   
    cout<<"Enter the value of the leafSize for each Node: ";
    int leafSize;
    cin>>leafSize;
    KDTreeIndex &treeIndex_1 = KDTreeIndex::GetInstance(leafSize); // Get a reference to the KDTreeIndex instance
    RPTreeIndex &treeIndex_2 = RPTreeIndex::GetInstance(leafSize); // Get a reference to the RPTreeIndex instance
    // Read dataset from file

    cout<<"Reading the training dataset"<<endl;
    vector<DataVector> dataset_1;
    DataVector dataVector_1;
    dataVector_1.readDataset("test1.csv", dataset_1); 
    cout<<"Reading the training dataset completed"<<endl;
    
    cout<<"Reading the test dataset"<<endl;
    vector<DataVector> dataset_2;
    DataVector dataVector_2;
    dataVector_2.readDataset("test2.csv", dataset_2);
    cout<<"Reading the test dataset completed"<<endl;


    // cout<<"Checking the ADD and REMOVE function"<<endl;
    // vector<DataVector> dataset_3;
    // DataVector dataVector_3;
    // dataVector_3.readDataset("test3.csv", dataset_3);

    // // treeIndex_1.AddData(dataset_3);
    // // treeIndex_1.RemoveData(dataset_3);
    // // treeIndex_2.AddData(dataset_3);
    // // treeIndex_2.RemoveData(dataset_3);

    // cout<<"Checking the ADD and REMOVE function completed"<<endl;

    cout<<"1. KDTree"<<endl;
    cout<<"2. RPTree"<<endl;
    cout << "enter the choice: " ;

    
    int choice;
    cin >> choice;

    cout<<"Enter the number of nearest neighbour to be found: ";
    int k;
    cin>>k;

    if (choice == 1)
    {   
        cout<<"Making the KDTree"<<endl;
        treeIndex_1.AddData(dataset_1);

        //to check the added and removed dataset
        // treeIndex_1.AddData(dataset_3);
        // treeIndex_1.RemoveData(dataset_3);
        

        cout<<"Making the KDTree completed"<<endl;

        int value;
        cout<<"Enter the number of test cases: ";
        cin>>value;
        cout<<"Searching the KDTree"<<endl;
        for (int i = 0; i < value; i++)
        {
            treeIndex_1.Search(dataset_2[i], k);
        }
    }
    else
    {   cout<<"Making the RPTree"<<endl;
        treeIndex_2.AddData(dataset_1);

        //to check the added and removed dataset
        // treeIndex_2.AddData(dataset_3);
        // treeIndex_2.RemoveData(dataset_3);

        cout<<"Making the RPTree completed"<<endl;

        int value;
        cout<<"Enter the number of test cases: ";
        cin>>value;
        cout<<"Searching the RPTree"<<endl;
        for (int i = 0; i < value; i++)
        {
            treeIndex_2.Search(dataset_2[i], k);
        }
    }
    
    cout<<"Searching completed"<<endl;

    


    
    // Now you can perform operations on the KD tree, such as searching
    // int dimension = 7;                // Assume the dimension of the test vector is 784
    // DataVector testVector(dimension); // Assume you have a test vector

    // for (int i = 0; i < dimension; i++)
    // {
    //     // cout << "Enter the value of the " << i + 1 << "th dimension: ";
    //     // double x;
    //     // cin >> x;
    //     // testVector.setComponent(i, x);
    //     testVector.setComponent(i, -5);
    // }

    // Search for the nearest neighbors of the test vector

    // dataVector_2.readDataset("test2.csv", dataset_2);
    //  treeIndex_1.AddData(dataset_2);
    //  treeIndex_1.RemoveData(dataset_2);

    // treeIndex_1.Search(testVector, k);
       


    // // Print the indices of the nodes in the tree
    // if (choice == 1)
    // {
    //     Node *rootNode = treeIndex_1.getRoot(); // Assuming you have a method to get the root node
    //     if (rootNode != nullptr)
    //     {
    //         treeIndex_1.printNodeIndices(rootNode, 0);
    //     }
    //     else
    //     {
    //         cout << "Root node is null." << endl;
    //     }
    // }
    // else
    // {
    //     Node *rootNode = treeIndex_2.getRoot(); // Assuming you have a method to get the root node
    //     if (rootNode != nullptr)
    //     {
    //         treeIndex_2.printNodeIndices(rootNode, 0);
    //     }
    //     else
    //     {
    //         cout << "Root node is null." << endl;
    //     }
    // }

    return 0;
}
