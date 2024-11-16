
#include "OpenAddressing.h"
#include "SeparateChaining.h"
#include "Vernal_Pools.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// GLOBAL FUNCTIONS

// First Key
string getTownNameKey(Vernal_Pool &vernal_pool) {
    // use objectID and town name
    return to_string(vernal_pool.getObjectID()) + vernal_pool.getTownName();
}

// Second Key
string getPoolStatusKey(Vernal_Pool & vernal_pool) {
    // use objectID and visitPoolType
    return to_string(vernal_pool.getObjectID()) + " " + vernal_pool.getPoolStatus();

}

int main() {
    //code from project 1 to load data into vector
    vector<Vernal_Pool> vernalPools;
    string datafile = "../Vermont_Vernal_Pool_Atlas.csv";
    if (getDataFromFile(datafile, vernalPools))
    {
        // remove duplicate final record
        vernalPools.pop_back();
    } else {
        cout << "Error reading file" << endl;
    }

    // use separate chaining

    // 10 different hash table objects for separate chaining
    // 5 use first getKey
    ofstream Separate_Chaining_Data_Key1;
    ofstream Separate_Chaining_Data_Key2;
    ofstream Open_Addressing_Data_Key1;
    ofstream Open_Addressing_Data_Key2;

    Separate_Chaining_Data_Key1.open("../data/Separate_Chaining_Data_Key1.csv");
    Separate_Chaining_Data_Key2.open("../data/Separate_Chaining_Data_Key2.csv");
    Open_Addressing_Data_Key1.open("../data/Open_Addressing_Data_Key1.csv");
    Open_Addressing_Data_Key2.open("../data/Open_Addressing_Data_Key2.csv");

    // hash table objects using key 1
    SeparateChaining<Vernal_Pool> chaining_table1k1(1950);
    SeparateChaining<Vernal_Pool> chaining_table2k1(2500);
    SeparateChaining<Vernal_Pool> chaining_table3k1(3000);
    SeparateChaining<Vernal_Pool> chaining_table4k1(3900);
    SeparateChaining<Vernal_Pool> chaining_table5k1(4400);

    OpenAddressing<Vernal_Pool> open_addressing_table1k1(1950);
    OpenAddressing<Vernal_Pool> open_addressing_table2k1(2500);
    OpenAddressing<Vernal_Pool> open_addressing_table3k1(3000);
    OpenAddressing<Vernal_Pool> open_addressing_table4k1(3900);
    OpenAddressing<Vernal_Pool> open_addressing_table5k1(4400);

    // hash table objects using key 2
    SeparateChaining<Vernal_Pool> chaining_table1k2(1950);
    SeparateChaining<Vernal_Pool> chaining_table2k2(2500);
    SeparateChaining<Vernal_Pool> chaining_table3k2(3000);
    SeparateChaining<Vernal_Pool> chaining_table4k2(3900);
    SeparateChaining<Vernal_Pool> chaining_table5k2(4400);

    OpenAddressing<Vernal_Pool> open_addressing_table1k2(1950);
    OpenAddressing<Vernal_Pool> open_addressing_table2k2(2500);
    OpenAddressing<Vernal_Pool> open_addressing_table3k2(3000);
    OpenAddressing<Vernal_Pool> open_addressing_table4k2(3900);
    OpenAddressing<Vernal_Pool> open_addressing_table5k2(4400);


     for (int i = 0; i < vernalPools.size(); i++) {
         int collisions1 = 0;
         int collisions2 = 0;
         int collisions3 = 0;
         int collisions4 = 0;
         int collisions5 = 0;

         // get Key 1 data (Separate Chaining)
         string key1String = getTownNameKey(vernalPools.at(i));

         // insert objects into tables
         chaining_table1k1.insert(key1String, vernalPools.at(i), collisions1);
         chaining_table2k1.insert(key1String, vernalPools.at(i), collisions2);
         chaining_table3k1.insert(key1String, vernalPools.at(i), collisions3);
         chaining_table4k1.insert(key1String, vernalPools.at(i), collisions4);
         chaining_table5k1.insert(key1String, vernalPools.at(i), collisions5);

         // write to file
         Separate_Chaining_Data_Key1 << "," << collisions1 << ","
             << collisions2 << "," << collisions3 << ","
             << collisions4 << "," << collisions5 << endl;
         collisions1 = 0;
         collisions2 = 0;
         collisions3 = 0;
         collisions4 = 0;
         collisions5 = 0;

         // get Key 2 data (Separate Chaining)
         string key2String = getPoolStatusKey(vernalPools.at(i));
         // insert objects into tables
         chaining_table1k2.insert(key2String, vernalPools.at(i), collisions1);
         chaining_table2k2.insert(key2String, vernalPools.at(i), collisions2);
         chaining_table3k2.insert(key2String, vernalPools.at(i), collisions3);
         chaining_table4k2.insert(key2String, vernalPools.at(i), collisions4);
         chaining_table5k2.insert(key2String, vernalPools.at(i), collisions5);

         // write to file
         Separate_Chaining_Data_Key2 << collisions1 << ","
             << collisions2 << "," << collisions3 << ","
             << collisions4 << "," << collisions5 << endl;


         // get Key 1 data (Open Addressing)
         key1String = getTownNameKey(vernalPools.at(i));
         collisions1 = 0;
         collisions2 = 0;
         collisions3 = 0;
         collisions4 = 0;
         collisions5 = 0;

         // insert objects into tables
         open_addressing_table1k1.insert(key1String, vernalPools.at(i), collisions1);
         open_addressing_table2k1.insert(key1String, vernalPools.at(i), collisions2);
         open_addressing_table3k1.insert(key1String, vernalPools.at(i), collisions3);
         open_addressing_table4k1.insert(key1String, vernalPools.at(i), collisions4);
         open_addressing_table5k1.insert(key1String, vernalPools.at(i), collisions5);

         // write to file
         Open_Addressing_Data_Key1 << collisions1 << ","
             << collisions2 << "," << collisions3 << ","
             << collisions4 << "," << collisions5 << endl;

         collisions1 = 0;
         collisions2 = 0;
         collisions3 = 0;
         collisions4 = 0;
         collisions5 = 0;

         // get Key 2 data (Open Addressing)
         key2String = getPoolStatusKey(vernalPools.at(i));
         //insert objects into tables
         open_addressing_table1k2.insert(key2String, vernalPools.at(i), collisions1);
         open_addressing_table2k2.insert(key2String, vernalPools.at(i), collisions2);
         open_addressing_table3k2.insert(key2String, vernalPools.at(i), collisions3);
         open_addressing_table4k2.insert(key2String, vernalPools.at(i), collisions4);
         open_addressing_table5k2.insert(key2String, vernalPools.at(i), collisions5);

         // write to file
         Open_Addressing_Data_Key2 << collisions1 << ","
             << collisions2 << "," << collisions3 << ","
             << collisions4 << "," << collisions5 << endl;

    }

    // close files
    Separate_Chaining_Data_Key1.close();
    Separate_Chaining_Data_Key2.close();
    Open_Addressing_Data_Key1.close();
    Open_Addressing_Data_Key2.close();

    // print the size of each Open Addressing Table
    cout << "Table size for Key 1:" << endl;
    cout << "Original Size: 1950, 2500, 3000, 3900, 4400" << endl;
    cout << open_addressing_table1k1.getTableSize() << endl;
    cout << open_addressing_table2k1.getTableSize() << endl;
    cout << open_addressing_table3k1.getTableSize() << endl;
    cout << open_addressing_table4k1.getTableSize() << endl;
    cout << open_addressing_table5k1.getTableSize() << endl;

    cout << "Table size for Key 2:" << endl;
    cout << open_addressing_table1k2.getTableSize() << endl;
    cout << open_addressing_table2k2.getTableSize() << endl;
    cout << open_addressing_table3k2.getTableSize() << endl;
    cout << open_addressing_table4k2.getTableSize() << endl;
    cout << open_addressing_table5k2.getTableSize() << endl;
    return 0;

}



