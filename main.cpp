/*
 * Please report any bug to the author:
 * +----------------------------------+
 * | Author: Tuhin Paul               |
 * |  Email: tuhin.paul@yahoo.com     |
 * |  Phone: 306 880 5494             |
 * +----------------------------------+
 *
 */

#include <cstdio>       /* isspace() */
#include <iostream>
#include <string>
#include <math.h>       /* log2 */
#include <fstream>
#include <cstdlib>

#include "LZEntropy.h"
#include "Row.h"
#include "util.h"

using namespace std;

int debugMode = false;

int main (int argc, char* argv[])
{
	/*
	LZEntropy<char> lzH;

	string s("ABC ABCDAB ABCDABCDABDE");
	string w("ABCDABD");
	string x("ABXYPQMN");
	Row<char>* S = string2charrows(s);
	Row<char>* W = string2charrows(w);
	Row<char>* X = string2charrows(x);
	cout << lzH.lzEntropy( S, s.length() ) << endl;
	cout << lzH.lzEntropy( W, w.length() ) << endl;
	cout << lzH.lzEntropy( X, x.length() ) << endl;
	
	print_rows( S, s.length() );
	*/
	
	if  ( argc != 2 )
	{
		string eMsg = "There should be exactly one argument (input file path)!";
		cerr << "ERROR: " << eMsg << endl;
		throw eMsg;
	}

	// file path
	string fPath(argv[1]);
	
	long numLines = 0;
	FILE *infile = fopen( fPath.c_str(), "r" );
    int ch;
	int chLast;
    while ( EOF != (ch=getc(infile)) )
	{
		chLast = ch;
        if ( (int)'\n' == ch )
            ++numLines;
	}
	
	if ( chLast != (int)'\n' )
	{
		string eMsg = "There is not a \'\\n\' at the end of the input file!";
		cerr << "ERROR: " << eMsg << endl;
		throw eMsg;
	}
	
	Row<long> *rows = new Row<long>[numLines - 1]; // because there should be a header
	int numRecords = 0; // actual num of records

	string line;
	ifstream myfile ( fPath.c_str() );
	if (myfile.is_open())
	{
		// ignore header
		getline (myfile, line);

		int rNo = 0;
		while ( getline (myfile,line) )
		{
			int iTrim = 0;   // trim scanning index
			while ( isspace( line[iTrim] ) )
				iTrim++; 
			int trimStartsAt = iTrim;
			
			int lastNonSpace = iTrim;
			while ( line[iTrim] != '\0' )
			{
				if ( ! isspace( line[iTrim] ) )
					lastNonSpace = iTrim;

				iTrim++;
			}
			
			if ( trimStartsAt == lastNonSpace ) // no non-space character
				continue;
			else
			{
				line = line.substr( trimStartsAt, (lastNonSpace - trimStartsAt + 1) );
				
				int commaPos = line.find_first_of(",");
				long x = atol(line.substr(0, commaPos).c_str());
				long y = atol(line.substr(commaPos+1).c_str());
				// todo: what if there are more than 2 values in a row?

				rows[rNo].setVal(x);
				rows[rNo].addNext();
				rows[rNo].getNext()->setVal(y);
				
				rNo++;
			}
		}

		numRecords = rNo;
		myfile.close();
	}
	
	if ( debugMode )
	{
		cout << "# of actual records: " << numRecords << endl;
		print_rows(rows, numRecords);
		cout << endl;
	}

	LZEntropy<long> lzH;
	cout << lzH.lzEntropy( rows, numRecords );

	return 0;
}

