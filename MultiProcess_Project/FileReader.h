//
// Created by Erik Peterson on 2/9/21.
//

#ifndef INC_21S_CS3377_PROJECT_FILEREADER_H
#define INC_21S_CS3377_PROJECT_FILEREADER_H


#include <list>
#include <string>
#include "Util.h"
#include <utility>
using namespace std;

class FileReader {
public:
    void readEntries(std::list<EntryInfo>& entryList, const char* fileName);
    void readEntries(std::list<EntryInfo>& entryList, int fileDescriptor);
    static void addMissingEntries(std::list<EntryInfo>& entries);

    // Default constructor.
    FileReader() = default;

    // Constructor that copies a list and sets it to entries (updated list).
    explicit FileReader(list<EntryInfo> originalList) {
        entries = move(originalList);
    }

    // Function that creates a list of entries.
    void createEntry(time_t newTimestamp, int newID, float newPrice, char *newItemName) {
        EntryInfo newEntry = {
                newTimestamp,
                newID,
                newPrice,
                newItemName
        };
        // Add the new entry to the end of the list.
        entries.push_back(newEntry);
    }

    // Function that returns the current list of entries.
    list<EntryInfo> getEntryList() {
        return entries;
    }

    // Function that sets the value of numEntries.
    static void setNumEntries(int numOfEntries) {
        numEntries = numOfEntries;
    }

    // Function that gets the current value of numEntries.
    static int getNumEntries() {
        return numEntries;
    }

    // Function that returns the constant sizeOfEntry variable.
    static long long int getSizeOfEntry() {
        return sizeOfEntry;
    }

    // Function declaration (implemented in FileReader.cpp)
    list<EntryInfo> readFileContents(int fileDescriptor);

private:
    static std::string getErrnoString();
    static void verifyNumBytes(ssize_t expected, ssize_t actual);

    // sizeOfEntry holds the size of an entry (in bytes).
    static const long long int sizeOfEntry = sizeof(time_t) + sizeof(int) + sizeof(float) + 50;
    // numEntries holds the number of entries contained within a file.
    static int numEntries;
    // Holds a list of EntryInfo structs.
    list<EntryInfo> entries;
};


#endif //INC_21S_CS3377_PROJECT_FILEREADER_H