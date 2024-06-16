import h5py
import numpy as np
import pandas as pd

# Open the HDF5 file
with h5py.File("1", "r") as hf:
    # Get the dataset
    Datasetnames = hf.keys()
    print(Datasetnames)
    # Get the dataset
    dataset = hf["test"]
    # Convert the dataset to a NumPy array
    data = np.array(dataset)
    # Create a Pandas DataFrame from the NumPy array
    df = pd.DataFrame(data)
    # Save the DataFrame to a CSV file
    df.to_csv("fmnist-test.csv", index=False)
