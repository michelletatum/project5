//
// Created by Michelle on 9/1/2024.
// class file for Vernal Pool and global functions
//

#ifndef VERNAL_POOLS_H
#define VERNAL_POOLS_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


#include "Vernal_Pools.h"
using namespace std;
using std::ifstream, std::left, std::ostream, std::setw;
using std::string, std::right, std::vector, std::count;


/**
 * Class representing Vernal Pool Visits
 * source: https://geodata.vermont.gov/datasets/VTANR::vermont-vernal-pool-atlas-vpatlas-org-pool-visits/about

    poolStatus - if the pool is confirmed to exist
    townName - the name of the town the pool is in
    countyName - the county the pool is in
    visitDate - date of the recorded visit
    visitLocationComments - user-entered data on the pool status, surroundings, and comments on land use
    visitPoolType - the type of pool - manmade, forest depression, or associated with other water bodies
    objectID = unique ID for each pool entered in vector
 */
class Vernal_Pool {
private:
    string poolStatus, townName,countyName,visitLocationComments, visitPoolType;
    int objectID;
    long visitDate;

public:
    // Constructors
    Vernal_Pool() {
        // Set default values to the fields
        poolStatus = "";
        townName = "";
        countyName = "";
        visitLocationComments = "";
        visitDate = -1;
        visitPoolType = "";
        objectID = -1;
    }

    Vernal_Pool(string poolStatus, string townName, string countyName,
        string visitLocationComments, long visitDate, string visitPoolType,
        int objectID) {
        this->poolStatus = poolStatus;
        this->townName = townName;
        this->countyName = countyName;
        this->visitLocationComments = visitLocationComments;
        this->visitDate = visitDate;
        this->visitPoolType = visitPoolType;
        this->objectID = objectID;
    }

    // Getters
    string getPoolStatus() const {
        return poolStatus;
    }
    string getTownName() const {
        return townName;
    }
    string getCountyName() const{
        return countyName;
    }
    string getVisitLocationComments() const{
        return visitLocationComments;
    }

    long getVisitDate() const{
        return visitDate;
    }
    string getVisitPoolType() const{
        return visitPoolType;
    }
    int getObjectID() const {
        return objectID;
    }

    // Setters
    void setPoolStatus(string poolStatus) {
        this->poolStatus = poolStatus;
    }
    void setTownName(string townName) {
        this->townName = townName;
    }
    void setCountyName(string countyName) {
        this->countyName = countyName;
    }
    void setVisitLocationComments(string poolStatus) {
        this->visitLocationComments = poolStatus;
    }
    void setVisitDate(long visitDate) {
        this->visitDate = visitDate;
    }
    void setVisitPoolType(string visitPoolType) {
        this->visitPoolType = visitPoolType;
    }
    void setObjectID(int objectID) {
        this->objectID = objectID;
    }

    // Overloaded Operators
    // updated for project 4
    friend ostream& operator<<(ostream& os, const Vernal_Pool& pool) {
        os << left << setw(6)<< pool.objectID;
        os <<left << setw(12) << pool.poolStatus;
        os << setw(17) << pool.townName;
        os << setw(12) << pool.countyName;
        os << setw(12) << pool.visitDate;
        os << setw(32) << pool.visitPoolType;
        os << setw(31) << wordWrap(pool.visitLocationComments, 100, 0);
        return os;
    }

    // overload == operator
    // compare objectID
    // switched to compare visitDate for testing for project 4
    friend bool operator == (const Vernal_Pool& lhs, const Vernal_Pool& rhs) {
        if (lhs.visitDate == rhs.visitDate) {
            return true;
        }
        return false;
    }
    // Project 3 - overload more operators

    // overload < operator
    // compare objectID
    friend bool operator < (const Vernal_Pool& lhs, const Vernal_Pool& rhs) {
        if (lhs.visitDate < rhs.visitDate) {
            return true;
        }
        return false;
    }
    // overload > operator
    // compare objectID
    friend bool operator > (const Vernal_Pool& lhs, const Vernal_Pool& rhs) {
        if (lhs.visitDate > rhs.visitDate) {
            return true;
        }
        return false;
    }

    // overload >= operator
    // compare objectID
    friend bool operator >= (const Vernal_Pool& lhs, const Vernal_Pool& rhs) {
        if (lhs.visitDate >= rhs.visitDate) {
            return true;
        }
        return false;
    }
    // overload <= operator
    // compare objectID
    friend bool operator <= (const Vernal_Pool& lhs, const Vernal_Pool& rhs) {
        if (lhs.visitDate <= rhs.visitDate) {
            return true;
        }
        return false;
    }

    // function for word wrap display for long text strings
    static string wordWrap(string str, int width, int tabs)
    {
        string newstring;
        if (str.length() < width) {
            newstring = str;
        } else {
            while (str.length() >= width){
                // get the characters of the string within width and append to newstring
                newstring = newstring.append(str.substr(0, width));
                newstring.append("\n");
                for (int i = 1; i < tabs; i++)
                    newstring.append("\t");
                str = str.substr(width);
                if (str.length() < width) {
                    newstring += str;
                }
            }
        }
        return newstring;
    }
};

// loads data from file
// null fields are left blank
// two complex cells, c30, c114
// return bool true if successful
bool getDataFromFile(string filename, vector<Vernal_Pool>& vernalPools) {
    ifstream fileIn;
    fileIn.open(filename);
    if (fileIn) {
        string header;
        getline (fileIn, header);

        // Declare variables
        string poolStatus, townName, countyName, visitDate, visitDirections, visitLocationComments, visitPoolType;
        int objectID;

        string field;
        char quotes = '"';
        char comma = ',';
        string skipdata;
        string newline = "";

        while(fileIn) {

            // c1-3
            for(int i = 0; i < 3; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c4 poolStatus
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, poolStatus, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                poolStatus = "";
            } else {
                getline(fileIn, poolStatus, ',');
            }
            if (!fileIn) {
                // no poolStatus, set default
                poolStatus = "N/A";
                fileIn.clear();
            }

            // c 5- 6
            for(int i = 0; i < 2; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c 7 townName
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, townName, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                townName = "";
            } else {
                getline(fileIn, townName, ',');
            }
            if (!fileIn) {
                // no townName, set default
                townName = "N/A";
                fileIn.clear();
            }

            // c 8 countyName
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, countyName, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                countyName = "";
            } else {
                getline(fileIn, countyName, ',');
            }
            if (!fileIn) {
                // no countyName, set default
                countyName = "N/A";
                fileIn.clear();
            }

            // c9-29
            for(int i = 0; i < 21; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c 30 Format is: "{<junk>}"
            if (fileIn.peek() == '"')
            {
                fileIn >> quotes;
                //fileIn >> curly;
                while (fileIn.peek() != '"') {
                    getline(fileIn, skipdata, '}');
                }
                fileIn >> quotes;
                fileIn >> comma;
            }

            // c31-44
            for(int i = 0; i < 14; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c45 visitDate
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, visitDate, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                visitDate = "";
            } else {
                getline(fileIn, visitDate, ',');
            }
            if (!fileIn) {
                // no data , set default
                visitDate = "N/A";
                fileIn.clear();
            }

            // c 46-48
            for(int i = 0; i < 3; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c49 visitDirections
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, visitDirections, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                visitDirections = "";
            } else {
                getline(fileIn, visitDirections, ',');
            }
            if (!fileIn) {
                // no data, set default
                visitDirections = "N/A";
                fileIn.clear();
            }

            // c50 visitLocationComments
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, visitLocationComments, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                visitLocationComments = "";
            } else {
                getline(fileIn, visitLocationComments, ',');
            }
            if (!fileIn) {
                // no entry, set default
                visitLocationComments = "N/A";
                fileIn.clear();
            }

            // c51- 54
            for(int i = 0; i < 4; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c55 visitPoolType
            if (fileIn.peek() == '"') {
                fileIn >> quotes;
                if (fileIn.peek() != '"') {
                    getline(fileIn, visitPoolType, '"');
                }
                fileIn >> quotes;
            }else if (fileIn.peek() == ',') {
                fileIn >> comma;
                visitPoolType = "";
            } else {
                getline(fileIn, visitPoolType, ',');
            }
            if (!fileIn) {
                // no entry, set default
                visitPoolType = "N/A";
                fileIn.clear();
            }

            // c56 -113
            for(int i = 0; i < 58; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            // c114 complex cell
            if (fileIn.peek() == '"')
            {
                fileIn >> quotes;
                //fileIn >> curly;
                while (fileIn.peek() != '"') {
                    getline(fileIn, skipdata, '}');
                }
                fileIn >> quotes;
                fileIn >> comma;
            } else if (fileIn.peek() == ',') {
                fileIn >> comma;
            } else {
                getline(fileIn, skipdata, ',');
            }

            // c 115 - 162
            for(int i = 0; i < 48; i++) {
                if (fileIn.peek() == '"') {
                    fileIn >> quotes;
                    if (fileIn.peek() != '"') {
                        getline(fileIn, skipdata, '"');
                    }
                    fileIn >> quotes;
                }else if (fileIn.peek() == ',') {
                    fileIn >> comma;
                } else {
                    getline(fileIn, skipdata, ',');
                }
            }

            //c 163 objectID
            fileIn >> objectID;
            if (!fileIn) {
                objectID = -1;
            }

            getline(fileIn, newline);

            // convert VisitDate to Int before inserting into vector
            // must have a visitDate to be added to vector
            if (visitDate != "N/A") {
                //cout << visitDate << endl;
                string date = visitDate.substr(0,10);
                //cout << date << endl;
                date.erase(4, 1);
                date.erase(6, 1);
                //cout << date << endl;
                long dateNum = stoi(date);
                //cout << objectID << "  " << dateNum << endl;
                vernalPools.push_back(Vernal_Pool(poolStatus, townName, countyName,
            visitLocationComments, dateNum, visitPoolType, objectID));
            }

        }
        fileIn.close();
        return true;
    }
    return false;
}

// given a vector of pool objects, prints data on pool status/existence (confirmed, potential, probable)
void showPoolStatus(vector<Vernal_Pool> vernalPools) {
    int probable = 0;
    int confirmed = 0;
    int potential =0;
    int other =0;

    for (const Vernal_Pool& pool : vernalPools) {
        if (pool.getPoolStatus() == "Confirmed") {
            confirmed++;
        } else if (pool.getPoolStatus() == "Potential") {
            potential++;
        }else if (pool.getPoolStatus() == "Probable") {
            probable++;
        } else {
            // catch anything else
            other++;
        }
    }
    cout << "\nVernal Pool Status:" << endl;
    cout << "Probable: " <<probable << endl;
    cout << "Confirmed: "<< confirmed << endl;
    cout << "Potenial: "<< potential << endl;
    int total = probable + confirmed + potential;
    cout << "Total: " << total <<endl;
    if (other > 0 || total != 1901) {
        cout<<"Error reading data"  <<endl;
    }
}

// testing getters, setters, and constructors
bool vernalPoolTest () {
    bool testPassed = true;
    Vernal_Pool testPool = Vernal_Pool();
    testPool.setPoolStatus("Test");
    if (testPool.getPoolStatus() != "Test") {
        cout << "Failed poolStatus test" << endl;
        testPassed = false;
    }
    testPool.setTownName("Test");
    if (testPool.getTownName() != "Test") {
        cout << "Failed townName test" << endl;
        testPassed = false;
    }
    testPool.setCountyName("Test");
    if (testPool.getCountyName() != "Test") {
        cout << "Failed countyName test" << endl;
        testPassed = false;
    }
    testPool.setVisitDate(300);
    if (testPool.getVisitDate() != 300) {
        cout << "Failed visitDate test" << endl;
        testPassed = false;
    }
    testPool.setVisitLocationComments("Test");
    if (testPool.getVisitLocationComments() != "Test") {
        cout << "Failed visitLocationComments test" << endl;
        testPassed = false;
    }
    testPool.setObjectID(1);
    if (testPool.getObjectID() != 1) {
        cout << "Failed objectID test" << endl;
        testPassed = false;
    }
    testPool.setVisitPoolType("Test");
    if (testPool.getVisitPoolType() != "Test") {
        cout << "Failed visitPoolType test" << endl;
        testPassed = false;
    }

    // test non default constructor
    Vernal_Pool testPool2 = Vernal_Pool("Confirmed", "Burlington", "Chittenden",
            "This is a test, with a comma", 300, "Mysterious", 0);
    if (testPool2.getPoolStatus() != "Confirmed" ||
        testPool2.getTownName() != "Burlington" ||
        testPool2. getCountyName() != "Chittenden" ||
        testPool2.getVisitLocationComments() != "This is a test, with a comma"
        || testPool2.getVisitDate() != 300 ||
        testPool2.getVisitPoolType() != "Mysterious"){
        cout << "Failed constructor test" << endl;
    }
    return testPassed;
}

#endif //VERNAL_POOLS_H

