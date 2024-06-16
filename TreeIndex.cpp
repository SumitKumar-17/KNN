#include <bits/stdc++.h>
#include <random>
#include "TreeIndex.h"
using namespace std;

// Initialize random number generator. 
std::random_device rd; // Obtain a random number from hardware
std::mt19937 gen(rd()); // Seed the generator
std::uniform_real_distribution<double> dis(-1.0, 1.0); // Define the range of the random number generator

//KD Tree implementation
//This function is used to add data to the tree. It calls the buildTree function to build the tree.
void KDTreeIndex::AddData(const vector<DataVector> &newDataset)
{
    // dataset.clear();

    // This is used to add the new dataset to the existing dataset. This is done by appending the new dataset to the existing dataset.
    dataset.insert(dataset.end(), newDataset.begin(), newDataset.end());

    // newDataset[1].print();
    
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {
        delete root;  // Delete the root node. 
        root = nullptr; // Set the root node to null.
    }

    // Make the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    MakeTree();
}

//This function is used to remove data from the dataset. 
void KDTreeIndex::RemoveData(const vector<DataVector> &dataToRemove)
{   
    // This is used to remove the data from the dataset. 
    //This is done by iterating through the dataToRemove vector and removing the data from the dataset.
    for(const DataVector &data : dataToRemove)
    {   
        // This is used to iterate through the dataset and remove the data from the dataset.
        for(int i = 0; i < dataset.size(); i++)
        {   
            // This is used to check if the data is present in the dataset. If it is present, then remove it from the dataset.
            if(dataset[i] == data){
                dataset.erase(dataset.begin() + i); // Remove the data from the dataset. 
                break; // Break the loop as the data has been removed to stop searching for that vector in the dataset to save time.
            }
        }
    }
    
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {
        delete root; // Delete the root node.
        root = nullptr; // Set the root node to null.
    }

    // Make the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    MakeTree();
}

//This function is used to search the tree. It calls the searchTree function to search the tree.
void KDTreeIndex::Search(const DataVector &testVector, int k)
{
    // Check if the dataset is empty
    if (dataset.empty())
    {
        cout << "Error: empty dataset" << endl;
        return;
    }

    // Initialize containers to store nearest neighbor indices and their distances
    vector<int> nearestIndices; // Vector to store the nearest neighbor indices
    vector<double> distances;  // Vector to store the distances of the nearest neighbors

    // Start searching from the root of the KD tree
    searchTree(root, testVector, k, nearestIndices, distances);  // Search the tree. This function is used to search the tree.

    // Print the nearest neighbors found
    cout << "Nearest neighbors:" << endl;
    for (int i = 0; i < nearestIndices.size(); ++i)
    {   
        //Prints the nearest neighbors found.
        //It prints the index of the nearest neighbor and the distance of the nearest neighbor from the test vector.
        cout << "Neighbor " << i + 1 << ": Index = " << nearestIndices[i] << endl;
        //", Distance = " << distances[i] << endl;
        // cout<<"Vector: ";
        // dataset[nearestIndices[i]].print();
        cout<<endl;
    }
}

//This function is used to search the tree. It calls the searchTree function to search the tree.
void KDTreeIndex::searchTree(Node* node, const DataVector& testVector, int k, vector<int>& nearestIndices, vector<double>& distances) {
    if (node == nullptr) {
        return;  // Return if the node is null.
    }
    
    // This is used to store the nodes in the tree. 
    stack<Node*> path;

    // This is used to store the current node in the tree.
    Node* current = node;

    // Traverse down the tree to find the leaf node closest to the test vector
    while (current != nullptr) {
        path.push(current);  // Push the current node to the stack.
        if (current->vectorIndices.empty()) {
            // Handle the case where the node has no vector indices
            current = nullptr; // Set the current node to null.
        } else if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
            current = current->leftChild; // Set the current node to the left child of the current node.
        } else {
            current = current->rightChild; // Set the current node to the right child of the current node.
        }
    }

    // Set the initial best distance to infinity
    double bestDistance = numeric_limits<double>::infinity();

    // This is used to store the best node.
    Node* bestNode = nullptr;

    // Initialize a set to keep track of the indices that have been added to the nearest neighbors 
    unordered_set<int> addedIndices;

    // Traverse back up the tree to find potential nearest neighbors
    while (!path.empty()) {
        current = path.top(); // Set the current node to the top of the stack.
        path.pop(); // Pop the top of the stack.

        // Calculate the distance between the test vector and each vector in the current node
        for (int index : current->vectorIndices) {
            if (index < dataset.size()) { // Ensure index is within bounds
                double distance = testVector.dist(dataset[index]); // Calculate the distance between the test vector and the vector in the current node.
                if (nearestIndices.size() < k) {
                    
                    // If the index is not already added, add it to the nearest indices and distances vectors.
                    if (addedIndices.find(index) == addedIndices.end()) {
                        nearestIndices.push_back(index);
                        distances.push_back(distance);
                        addedIndices.insert(index);
                    }
                    
                    // If the distance is less than the best distance, set the best distance to the distance and set the best node to the current node.
                    if (distance < bestDistance) {
                        bestDistance = distance;
                        bestNode = current;
                    }


                }
                // If the nearestIndices vector is full, then check if the distance is less than the best distance.
                 else {
                     if (distance < bestDistance) {
                        // If index is not already added, add it and remove the last index
                        if (addedIndices.find(index) == addedIndices.end()) {
                            // Remove the last index from the nearestIndices and distances vectors.
                            addedIndices.erase(nearestIndices.back());
                            nearestIndices.pop_back();
                            distances.pop_back();
                            nearestIndices.push_back(index);
                            distances.push_back(distance);
                            addedIndices.insert(index);
                            bestDistance = distance;
                            bestNode = current;
                        }
                    }
                }
            }
        }

        // Calculate the distance between the test vector and the splitting hyperplane
        if (!current->vectorIndices.empty()) {
            // Calculate the distance between the test vector and the splitting hyperplane
            double splitDistance = abs(testVector.getComponent(current->splitDim) - dataset[current->vectorIndices[0]].getComponent(current->splitDim));

            // If the distance to the splitting hyperplane is less than the best distance, search the other side of the tree
            if (splitDistance < bestDistance) {
                if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
                    current = current->rightChild;  // Set the current node to the right child of the current node.
                } else {
                    current = current->leftChild; // Set the current node to the left child of the current node.
                }
                while (current != nullptr) {
                    path.push(current); // Push the current node to the stack.
                    if (current->vectorIndices.empty()) {
                        // Handle the case where the node has no vector indices
                        current = nullptr;
                    } else if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
                        current = current->leftChild;  // Set the current node to the left child of the current node.
                    } else {
                        current = current->rightChild;  // Set the current node to the right child of the current node.
                    }
                }
            }
        }
    }

    // Sort the nearest neighbors by distance
    vector<pair<int, double>> nearestPairs;
    for (int i = 0; i < nearestIndices.size(); ++i) {
        nearestPairs.push_back(make_pair(nearestIndices[i], distances[i]));  // Push the nearest indices and distances to the nearestPairs vector.
    }
    // Sort the nearestPairs vector by distance.
    sort(nearestPairs.begin(), nearestPairs.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second < b.second;
    });

    // Update the nearest indices and distances
    for (int i = 0; i < nearestPairs.size(); ++i) {
        nearestIndices[i] = nearestPairs[i].first; // Set the nearestIndices vector to the nearestPairs vector.
        distances[i] = nearestPairs[i].second; // Set the distances vector to the nearestPairs vector.
    }
}

//This function is used to build the tree. It calls the buildTree function to build the tree.
void KDTreeIndex::buildTree(Node *&node, const std::vector<int> &indices)
{   
    if (indices.empty())
    {
        // Handle the case where the indices vector is empty
        return;
    }

    if (indices.size() < M)
    {
        // If the number of vectors in this node is less than M, make it a leaf
        node->isLeaf = true;
        return;
    }

    // Choose the split rule for this node
    int splitDim;
    // Choose the rule to split the data. This function is used to choose the rule to split the data.
    auto Rule = ChooseRule(indices, splitDim);
    
    // Set the vector indices of the node to the indices vector.
    node->vectorIndices = indices;
    

    // Partition the indices based on the split rule
    vector<int> leftIndices, rightIndices;
    for (int index : indices)
    {   
        // Partition the indices based on the split rule
        if (Rule(dataset[index]))
        {  
            leftIndices.push_back(index);  // Push the index to the leftIndices vector.
        }
        else
        {
            rightIndices.push_back(index);  // Push the index to the rightIndices vector.
        }
    }
    // cout<<leftIndices.size()<<endl;
     if (leftIndices.empty() || rightIndices.empty())
    {
        // Handle the case where one of the partitions is empty
        return;
    }

    // Recursively build the left and right subtrees
    node->splitDim = splitDim;  // Set the splitDim of the node to the splitDim.
    node->leftChild = new Node();  // Create a new node and set it to the leftChild of the node.
    node->rightChild = new Node();  // Create a new node and set it to the rightChild of the node.
    buildTree(node->leftChild, leftIndices); // Recursively build the left subtree. This function is called recursively to build the tree.
    buildTree(node->rightChild, rightIndices); // Recursively build the right subtree. This function is called recursively to build the tree.
}

//This function is used to choose the rule to split the data. It is used to choose the rule to split the data.
std::function<bool(const DataVector &)> KDTreeIndex::ChooseRule(const std::vector<int> &indices, int &splitDim) {
    if (indices.empty()) {
        throw std::invalid_argument("Empty subset"); // Throw an exception if the indices vector is empty.
    }
    
    // This is used to store the number of dimensions in the dataset.
    int numDims = dataset[indices[0]].getDimension();  // Get the dimension of the dataset.
    vector<double> maxVals(numDims, numeric_limits<double>::lowest());  // Vector to store the maximum values of the dataset.
    vector<double> minVals(numDims, numeric_limits<double>::max());  // Vector to store the minimum values of the dataset.

    // Calculate the minimum and maximum values for each dimension
    for (int index : indices) {
        // Calculate the minimum and maximum values for each dimension
        for (int i = 0; i < numDims; ++i) {
            // Calculate the minimum and maximum values for each dimension
            double val = dataset[index].getComponent(i); // Get the component of the dataset.
            if (val > maxVals[i]) {
                maxVals[i] = val; // Set the maximum value of the dataset to the val.
            }
            if (val < minVals[i]) {
                minVals[i] = val; // Set the minimum value of the dataset to the val.
            }
        }
    }
    
    // This is used to store the split dimension. 
    double maxSpread = numeric_limits<double>::lowest(); // Set the maximum spread to the lowest value.

    // Calculate the spread for each dimension and choose the dimension with the maximum spread
    for (int i = 0; i < numDims; ++i) {
        // Calculate the spread for each dimension and choose the dimension with the maximum spread
        double spread = maxVals[i] - minVals[i];

        // If the spread is greater than the maximum spread, set the maximum spread to the spread and set the split dimension to the current dimension.
        if (spread > maxSpread) {
            maxSpread = spread;
            splitDim = i;
        }
    }

    // Calculate the median value for the chosen dimension
    vector<double> dimVals;

    // This is used to store the median value for the chosen dimension.
    for (int index : indices) {
        dimVals.push_back(dataset[index].getComponent(splitDim)); // Push the component of the dataset to the dimVals vector.
    }

    // Sort the dimVals vector
    sort(dimVals.begin(), dimVals.end());

    // This is used to store the median value for the chosen dimension.
    double median = dimVals[dimVals.size() / 2];

    // Return the splitting rule as a lambda function
    return [splitDim, median](const DataVector& vec) {
        return vec.getComponent(splitDim) <= median; 
    };
}

//This function is used to build the tree. It calls the buildTree function to build the tree.
void KDTreeIndex::MakeTree()
{   
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {
        delete root; // Delete the root node.
        root = nullptr; // Set the root node to null.
    }

    // If the dataset is not empty, then build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    if (!dataset.empty())
    {
        vector<int> indices(dataset.size()); // Vector to store the indices of the dataset.
        iota(indices.begin(), indices.end(), 0); // Fill indices with 0, 1, 2, ..., n-1
        root = new Node();  // Create a new node and set it to the root node.
        buildTree(root, indices); // Build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    }
}

//This function is used to get the instance of the KDTreeIndex class. 
KDTreeIndex &KDTreeIndex::GetInstance(int leafSize)
{
    static KDTreeIndex instance(leafSize); // Create a static instance of the KDTreeIndex class.The leafSize is taken as the parameter while calling the constructor.
    return instance; // Return the instance of the KDTreeIndex class.
}

//This function is used to print the indices of the nodes in the tree. It is used for debugging purposes.
void KDTreeIndex::printNodeIndices(Node *node, int depth)
{   
    // If the node is null, then print the message.
    if (node == nullptr)
    {   // Print the message.
        if (depth == 0)
        {   
            // Print the message.
            cout << "Root node is nullptr" << endl;
        }
        else
        {   
            // Print the message.
            cout << "Node at depth " << depth << " is nullptr" << endl;
        }
        return;
    }
    
    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    printNodeIndices(node->leftChild, depth + 1);

    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    if (node->vectorIndices.size())
    {   
        // Print the indices of the nodes in the tree. It is used for debugging purposes.
        cout << "Indices in this node: ";

        // Print the indices of the nodes in the tree. It is used for debugging purposes.
        for (int index : node->vectorIndices)
        {   
            // Print the indices of the nodes in the tree. It is used for debugging purposes.
            cout << index << " ";
        }
        cout << endl;
    }

    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    printNodeIndices(node->rightChild, depth + 1);
}

//This function is a uniform random number generator. It is used to generate a random number between the given range.
double uniform_random(double min, double max)
{   
    // This is a uniform random number generator. It is used to generate a random number between the given range.
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

//RP Tree implementation
//This function is used to add data to the tree. It calls the buildTree function to build the tree.
void RPTreeIndex::AddData(const vector<DataVector> &newDataset)
{
    // dataset.clear();

    // This is used to add the new dataset to the existing dataset. This is done by appending the new dataset to the existing dataset.
    dataset.insert(dataset.end(), newDataset.begin(), newDataset.end());

    // newDataset[1].print();
    
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {   
        // If the root node is not null, then delete the root node and set it to null.
        delete root; // Delete the root node.
        root = nullptr; // Set the root node to null.
    }

    // Make the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    MakeTree();
}

//This function is used to remove data from the dataset. 
void RPTreeIndex::RemoveData(const vector<DataVector> &dataToRemove)
{   
    // This is used to remove the data from the dataset.
    for(const DataVector &data : dataToRemove)
    {   
        // This is used to iterate through the dataset and remove the data from the dataset.
        for(int i = 0; i < dataset.size(); i++)
        {   
            // This is used to check if the data is present in the dataset. If it is present, then remove it from the dataset.
            if(dataset[i] == data){
                dataset.erase(dataset.begin() + i);  // Remove the data from the dataset.
                break; // Break the loop as the data has been removed to stop searching for that vector in the dataset to save time.
            }
        }
    }
    
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {
        delete root;  // Delete the root node.
        root = nullptr; // Set the root node to null.
    }

    // Make the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    MakeTree();
}

//This function is used to search the tree. It calls the searchTree function to search the tree. 
void RPTreeIndex::Search(const DataVector &testVector, int k)
{
    // Check if the dataset is empty
    if (dataset.empty())
    {
        cout << "Error: empty dataset" << endl;
        return; // Return if the dataset is empty.
    }

    // Initialize containers to store nearest neighbor indices and their distances
    vector<int> nearestIndices;
    // Vector to store the nearest neighbor indices
    vector<double> distances;

    // Start searching from the root of the RP tree
    searchTree(root, testVector, k, nearestIndices, distances);

    // Print the nearest neighbors found. 
    //It prints the index of the nearest neighbor and the distance of the nearest neighbor from the test vector.
    cout << "Nearest neighbors:" << endl;
    for (int i = 0; i < nearestIndices.size(); ++i)
    {
        cout << "Neighbor " << i + 1 << ": Index = " << nearestIndices[i] <<endl;
        //  ", Distance = " << distances[i] << endl;
        // cout<<"Vector: ";
        // dataset[nearestIndices[i]].print();
        cout<<endl;
    }
}

//This function is used to search the tree. It calls the searchTree function to search the tree.
void RPTreeIndex::searchTree(Node* node, const DataVector& testVector, int k, vector<int>& nearestIndices, vector<double>& distances) {
    if (node == nullptr) {
        return;  // Return if the node is null.
    }
    
    // This is used to store the nodes in the tree.
    stack<Node*> path;
    // This is used to store the current node in the tree.
    Node* current = node;

    // Traverse down the tree to find the leaf node closest to the test vector
    while (current != nullptr) {
        // Push the current node to the stack.
        path.push(current);
        if (current->vectorIndices.empty()) {
            // Handle the case where the node has no vector indices
            current = nullptr;
        } 
        else if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
            current = current->leftChild; // Set the current node to the left child of the current node.
        } else {
            current = current->rightChild; // Set the current node to the right child of the current node.
        }
    }

    // Set the initial best distance to infinity
    double bestDistance = numeric_limits<double>::infinity();

    // This is used to store the best node.
    Node* bestNode = nullptr;

    // Initialize a set to keep track of the indices that have been added to the nearest neighbors 
    unordered_set<int> addedIndices;

    // Traverse back up the tree to find potential nearest neighbors
    while (!path.empty()) {
        // Set the current node to the top of the stack.
        current = path.top();
        // Pop the top of the stack.
        path.pop();

        // Calculate the distance between the test vector and each vector in the current node
        for (int index : current->vectorIndices) {
            if (index < dataset.size()) { // Ensure index is within bounds
            // Calculate the distance between the test vector and the vector in the current node.
                double distance = testVector.dist(dataset[index]);

                // If the nearestIndices vector is not full, then add the index to the nearestIndices and distances vectors.
                if (nearestIndices.size() < k) {
                    
                    // If the index is not already added, add it to the nearest indices and distances vectors.
                    if (addedIndices.find(index) == addedIndices.end()) {
                        nearestIndices.push_back(index);
                        distances.push_back(distance);
                        addedIndices.insert(index);
                    }
                    
                    // If the distance is less than the best distance, set the best distance to the distance and set the best node to the current node.
                    if (distance < bestDistance) {
                        bestDistance = distance;
                        bestNode = current;
                    }
                } else {
                    // If the nearestIndices vector is full, then check if the distance is less than the best distance.
                     if (distance < bestDistance) {
                        // If index is not already added, add it and remove the last index
                        if (addedIndices.find(index) == addedIndices.end()) {
                            // Remove the last index from the nearestIndices and distances vectors.
                            addedIndices.erase(nearestIndices.back());
                            nearestIndices.pop_back();
                            distances.pop_back();
                            nearestIndices.push_back(index);
                            distances.push_back(distance);
                            addedIndices.insert(index);
                            bestDistance = distance;
                            bestNode = current;
                        }
                    }
                }
            }
        }

        // Calculate the distance between the test vector and the splitting hyperplane
        if (!current->vectorIndices.empty()) {
            // Calculate the distance between the test vector and the splitting hyperplane
            double splitDistance = abs(testVector.getComponent(current->splitDim) - dataset[current->vectorIndices[0]].getComponent(current->splitDim));

            // If the distance to the splitting hyperplane is less than the best distance, search the other side of the tree
            if (splitDistance < bestDistance) {
                // Set the current node to the right child of the current node.
                if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
                    current = current->rightChild; // Set the current node to the right child of the current node.
                } else {
                    current = current->leftChild; // Set the current node to the left child of the current node.
                }
                while (current != nullptr) {
                    // Push the current node to the stack.
                    path.push(current); // Push the current node to the stack.
                    if (current->vectorIndices.empty()) {
                        // Handle the case where the node has no vector indices
                        current = nullptr; // Set the current node to null.
                    } else if (testVector.getComponent(current->splitDim) <= dataset[current->vectorIndices[0]].getComponent(current->splitDim)) {
                        current = current->leftChild;  // Set the current node to the left child of the current node.
                    } else {
                        current = current->rightChild; // Set the current node to the right child of the current node.
                    }
                }
            }
        }
    }

    // Sort the nearest neighbors by distance
    vector<pair<int, double>> nearestPairs;
    
    // Push the nearest indices and distances to the nearestPairs vector.
    for (int i = 0; i < nearestIndices.size(); ++i) {
        // Push the nearest indices and distances to the nearestPairs vector.
        nearestPairs.push_back(make_pair(nearestIndices[i], distances[i]));
    }
    // Sort the nearestPairs vector by distance.
    sort(nearestPairs.begin(), nearestPairs.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second < b.second;
    });

    // Update the nearest indices and distances
    for (int i = 0; i < nearestPairs.size(); ++i) {
        nearestIndices[i] = nearestPairs[i].first;
        distances[i] = nearestPairs[i].second;
    }
}

//This function is used to build the tree. It calls the buildTree function to build the tree.
void RPTreeIndex::buildTree(Node *&node, const std::vector<int> &indices)
{   
    if (indices.empty())
    {
        // Handle the case where the indices vector is empty
        return;
    }

    if (indices.size() < M)
    {
        // If the number of vectors in this node is less than M, make it a leaf
        node->isLeaf = true;
        return;
    }

    // Choose the split rule for this node
    int splitDim; 
    // Choose the rule to split the data. This function is used to choose the rule to split the data.
    auto Rule = ChooseRule(indices, splitDim);
    
    // Set the vector indices of the node to the indices vector.
    node->vectorIndices = indices;
    // cout<<indices.size()<<endl;

    // Partition the indices based on the split rule
    vector<int> leftIndices, rightIndices;
    for (int index : indices)
    {
        // Partition the indices based on the split rule
        if (Rule(dataset[index]))
        {   
            // Push the index to the leftIndices vector.
            leftIndices.push_back(index);
        }
        else
        {   
            // Push the index to the rightIndices vector.
            rightIndices.push_back(index);
        }
    }
    // cout<<leftIndices.size()<<endl;
     if (leftIndices.empty() || rightIndices.empty())
    {
        // Handle the case where one of the partitions is empty
        return;
    }

    // Recursively build the left and right subtrees
    node->splitDim = splitDim;  // Set the splitDim of the node to the splitDim.
    node->leftChild = new Node(); // Create a new node and set it to the leftChild of the node.
    node->rightChild = new Node(); // Create a new node and set it to the rightChild of the node.
    buildTree(node->leftChild, leftIndices); // Recursively build the left subtree. This function is called recursively to build the tree.
    buildTree(node->rightChild, rightIndices); // Recursively build the right subtree. This function is called recursively to build the tree.
}

//This function is used to choose the rule to split the data. It is used to choose the rule to split the data.
std::function<bool(const DataVector &)> RPTreeIndex::ChooseRule(const std::vector<int> &indices, int &splitDim) {
     if (indices.empty()) {
        throw std::invalid_argument("Empty subset");  // Throw an exception if the indices vector is empty.
    }
    
    // This is used to store the number of dimensions in the dataset.
    int numDims = dataset[indices[0]].getDimension();

    // This is used to store the number of dimensions in the dataset.
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<double> dis(-1.0, 1.0); // Define the range of the random number generator

    // Choose a random unit direction v
    DataVector v(numDims);
    // This is used to store the random unit direction v.
    for (int i = 0; i < numDims; ++i) {
        v.setComponent(i, dis(gen)); // Set the component of the vector to a random number between -1 and 1.
    }

    // Normalize to get a unit vector
    v.normalize(); // Normalize to get a unit vector
    // v.print(); // Print the normalized vector v for debugging purposes.

    // Find the farthest point y from any point x in S
    double maxDistance = -1.0; // Set the maximum distance to -1.
    DataVector x = dataset[indices[0]]; // Set the vector x to the first vector in the dataset.
    DataVector y(numDims); // Create a new vector y with the number of dimensions as numDims.
    for (int index : indices) {

        // Find the farthest point y from any point x in S
        double distance = x.dist(dataset[index]); // Calculate the distance between the vector x and the vector in the dataset.
        if (distance > maxDistance) {
            // If the distance is greater than the maximum distance, set the maximum distance to the distance and set the vector y to the vector in the dataset.
            maxDistance = distance;
            y = dataset[index];
        }
    }

    // Calculate δ uniformly at random
    double delta = dis(gen) * 6 * sqrt(x.dist(y)) / sqrt(numDims);

    // Calculate Rule(x)
    double medianDotProduct = 0.0;

    // This is used to store the dot products of the vectors in the dataset.
    std::vector<double> dotProducts;

    // This is used to store the dot products of the vectors in the dataset.
    for (int index : indices) {
        // Calculate the dot products of the vectors in the dataset.
        dotProducts.push_back(dataset[index].dot(v));
    }

    // Sort the dot products
    std::sort(dotProducts.begin(), dotProducts.end());

    // Calculate the median dot product
    int n = dotProducts.size();

    // Calculate the median dot product
    if (n % 2 == 0) {
        medianDotProduct = (dotProducts[n / 2 - 1] + dotProducts[n / 2]) / 2.0;
    } else {
        medianDotProduct = dotProducts[n / 2];
    }
    
    // Return the splitting rule as a lambda function. 
    return [v, medianDotProduct, delta](const DataVector& vec) {
        return vec.dot(v) <= (medianDotProduct + delta); // Return the splitting rule as a lambda function.
    };
    
}

//This function is used to build the tree. It calls the buildTree function to build the tree.
void RPTreeIndex::MakeTree()
{   
    // If the root node is not null, then delete the root node and set it to null.
    if (root)
    {
        delete root; // Delete the root node.
        root = nullptr; // Set the root node to null.
    }

    // If the dataset is not empty, then build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    if (!dataset.empty())
    {   
        // Vector to store the indices of the dataset.
        vector<int> indices(dataset.size()); // Vector to store the indices of the dataset.
        iota(indices.begin(), indices.end(), 0); // Fill indices with 0, 1, 2, ..., n-1
        root = new Node();  // Create a new node and set it to the root node.
        buildTree(root, indices); // Build the tree. This function is called to build the tree. It calls the buildTree function to build the tree.
    }
}

//This function is used to get the instance of the RPTreeIndex class. 
RPTreeIndex &RPTreeIndex::GetInstance(int leafSize)
{
    static RPTreeIndex instance(leafSize); // Create a static instance of the RPTreeIndex class.The leafSize is taken as the parameter while calling the constructor.
    return instance; // Return the instance of the RPTreeIndex class.
}

//This function is used to print the indices of the nodes in the tree. It is used for debugging purposes.
void RPTreeIndex::printNodeIndices(Node *node, int depth)
{   
    // If the node is null, then print the message.
    if (node == nullptr)
    {   
        // Print the message.
        if (depth == 0)
        {
            cout << "Root node is nullptr" << endl;
        }
        else
        {
            cout << "Node at depth " << depth << " is nullptr" << endl;
        }
        return;
    }
    
    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    printNodeIndices(node->leftChild, depth + 1); 

    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    if (node->vectorIndices.size())
    {
        cout << "Indices in this node: ";
        for (int index : node->vectorIndices)
        {
            cout << index << " ";
        }
        cout << endl;
    }

    // Print the indices of the nodes in the tree. It is used for debugging purposes.
    printNodeIndices(node->rightChild, depth + 1);
}

