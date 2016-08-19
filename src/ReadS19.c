#include "ReadS19.h"
#include <stdio.h>
#include <stdint.h>
#include "InstructionTable.h"
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "CException.h"
#include <malloc.h>
#include "Description.h"

/**


// Include the headers
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Data structure to store S-Record in.
    struct S_Record
    {
        string header;
        string length;
        string address;
        string data;
    };

    // A vector of S-Records
    vector<S_Record> s_record_list;

    // Try to open the file.
    ifstream s_record_file("s_record.txt");

    string line;

    // Read each line in the file. Assumes each line is terminated by a 'newline'
    while (getline(s_record_file, line))
    {
        S_Record s_record;

        // Split the line in parts.
        s_record.header  = line.substr(0, 2); // Start at 0, length 2
        s_record.length  = line.substr(2, 2); // Start at 2, length 2
        s_record.address = line.substr(4, 4); // Satart at 4, length 4
        s_record.data    = line.substr(8);    // Start at 8, up to the end of the line.

        // Add it to the list.
        s_record_list.push_back(s_record);
    }

    s_record_file.close();

    // Print them out.
    for (size_t i = 0; i < s_record_list.size(); ++i)
    {
        cout << "Header = " << s_record_list[i].header
             << " : Length = " << s_record_list[i].length
             << " : Address = " << s_record_list[i].address
             << " : Data = " << s_record_list[i].data
             << "\n";
    }

    // Write them to a new file.
    ofstream output_file("output.txt");

    if (!output_file.fail())
    {
        for (size_t i = 0; i < s_record_list.size(); ++i)
        {
            output_file << s_record_list[i].header
                        << s_record_list[i].length
                        << s_record_list[i].address
                        << s_record_list[i].data
                        << "\n";
        }

        output_file.close();
    }
}



*/