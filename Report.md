# Project 5 Report

* Information about your dataset (you will be assigned a different grader for this project).


* poolStatus - if the pool's existence is confirmed, potential, or probable
* townName - the name of the town the pool is in
* countyName - the county the pool is in
* visitDate - date of the recorded visit
* visitLocationComments - user-entered data on the pool status, surroundings, and comments on land use
* visitPoolType - the type of pool - manmade, forest depression, or associated with other water bodies
* objectID = unique ID for each pool entered in list

The data was sourced from the State of Vermont's Vermont Open Geodata portal used for GIS applications. The link to the direct dataset is here: https://geodata.vermont.gov/datasets/VTANR::vermont-vernal-pool-atlas-vpatlas-org-pool-visits/about

Vernal pools are seasonal wetlands that provide an essential habitat for hundreds of species, both rare and common, particularly amphibian and plant life. They are considered threatened, and wetland conservation efforts are focusing on these areas due to their fragile nature and ecosystem value.

The rows are in a CSV file (comma separated) with 163 columns. The data used in this project is from column c4 (poolStatus), c7 (townName), c8 (countyName), c45 (visitDate), c50 (visitLocationDirections), c55 (visitPoolType), and c163 (objectID).

Total records: 1901.

Data is sorted ascending by objectID by default in the csv file.

* Create graphs for the number of collisions for inserting your dataset into all 20 hash tables.

Separate Chaining Key 1
![SCK1](charts/SeparateChainingKey1Graph.png)

Separate Chaining Key 2
![SCK2](charts/SeparateChainingKey2Graph.png)

Open Addressing Key 1
![OAK1](charts/OpenAddressingKey1Graph.png)

Open Addressing Key 1
![OAK2](charts/OpenAddressingKey2Graph.png)

* Using the graphs, analyze why the collision counts are different for the different size hash tables. Use what you know about your keys and the hash tables to justify why the collision counts make sense.

Charts indicate average collisions per table size. Table sizes chosen were 1950, 2500, 3000, 3900, and 4400.

A smaller table size will mean more collisions, since the dataset is the same size for each run of the table. Each key is 
unique, one built from the object ID and the town name, and the other the ID and the pool status. Each key is unique but about
the same length in each grouping.

The only graph with steadily decreasing collisions as the table size increased is the separate chaining table that used Key 1.
All other tables decreased collisions through the first three iterations, but increased in average collisions with a table
size of 3900 before decreasing again. I was not expecting this and am not completey sure why the data came out this way, but the affected 
keys (Separate Chaining 2 and both Open Addressing keys) collided more with a table size of 3900 because the hash
function resulted in the same index number more often. 

* Determine which global function works best as the key for your dataset objects based on the collision counts.

I believe that the best global function using Key 2 is better for this dataset. Despite the odd jump in collisions at the
3900 table size, its lowest value has much fewer collisions than the Key 1 tables, especially with a large table size. 

* Draw conclusions about which hash collision detection method works best on your dataset (separate chaining or open addressing).

I think that separate chaining works best for this dataset. It is a bit more consistent with expectations that collision 
counts will decrease with increasing table size. It also seems to have overall lower numbers of collisions than
the double hashing function does.

Original Table Size: 1950, 2500, 3000, 3900, 4400

Table size for Key 1:
  
  * 3907
  * 5009
  * 6007
  * 3907
  * 4409
  

Table size for Key 2:
  * 3907
  * 5009
  * 6007
  * 3907
  * 4409

**Note: Any code that was not authored by yourself or the instructor must be cited in your report. This includes the use of concepts not taught in lecture.**


Double Hashing Source:

https://www.geeksforgeeks.org/double-hashing/