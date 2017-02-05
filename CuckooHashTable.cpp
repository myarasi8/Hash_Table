#include "CuckooHashTable.h"

using namespace std;

CuckooHashTable::CuckooHashTable()
{
	vector<string> HashTable1; //Initialize vector, HashTable1
	vector<string> HashTable2; //Initialize vector, HashTable2
	//HashTable1.push_back("Table 1:"); //first value in HashTable1
	//HashTable2.push_back("Table 2:"); //first value in HashTable2

	/*fill both HashTables with '-' */
	for (int i = 0; i < LOGICAL_SIZE; i++)
	{
		HashTable1.push_back("-");
		HashTable2.push_back("-");
	}

	/*put both HashTables into conent*/
	contents.push_back(HashTable1);
	contents.push_back(HashTable2);
}


int CuckooHashTable::hashCode(string value, int which)
{
	int myInt = atoi(value.c_str());

	if (which == 1)
	{
		return myInt % 13;
	}
	else if (which == 2)
	{
		return 11 - (myInt % 11);
	}

}

void CuckooHashTable::add(string value)
{
	//value is new value and insertvalue is old value
	int index = hashCode(value, 1);
	
	int oldValue = 0;
	
	/*check to see if value is in HashTable1 */
	if (contents[0][index] == "-")
	{
		contents[0][index] = value; 
		currentSize += 1;
	}

	/* If there is a value in table1 but not in Table2 */
	else
	{
		string insertValue = value; //insertValue is new value
		int cycles = 0; //keeps track of how many times
		int hash = 0; 
		while ((cycles < currentSize) || (contents[hash][index] != "-"))
		//while loop is only to switch values
		{
			//Looking at first HashTable
			if (hash == 0)
			{
				value = contents[hash][index]; //store old value from table 1
				contents[hash][index] = insertValue; //the value we are inserting is the new value. put new value into table 1
				index = hashCode(value,2); //find hash2 of old value to put into table2
				insertValue = value; //the value we are inserting into table 2 is the old value so update inserting value to old value
				hash = 1; //switch tables
			}

			//Looking at second HashTable
			if (hash == 1)
			{
				value = contents[hash][index]; //store old value in table2
				contents[hash][index] = insertValue; //put new value into table2
				index = hashCode(value, 1); //find hash1 of the old value to put into table 1
				insertValue = value; //the value we are inserting into table 1 is the old value so we update inserting value to old value
				hash = 0; //switch tables
			}

		cycles += 1;

		}
		//table 2 is empty so you put it in there
		index = hashCode(value,2);
		contents[hash][index] = insertValue;
		cycles = 0; //reinitialize cycles to 0
	}


}

void CuckooHashTable::print()
{
	cout << "Table 1:" << endl;
	for (int i = 0; i < LOGICAL_SIZE; i++)
	{
		cout << contents[0][i] << endl;
	}
	cout << "Table 2:" << endl;
	for (int i = 0; i < LOGICAL_SIZE; i++)
	{
		cout << contents[1][i] << endl;
	}
}










