#/!bin/bash

g++ -o nearest_neighbor_program nearestneighbor.cpp VectorDataset.cpp DataVector.cpp
./nearest_neighbor_program
rm -f nearest_neighbor_program