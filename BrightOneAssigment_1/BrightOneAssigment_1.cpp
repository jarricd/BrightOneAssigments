﻿#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
const int ARR_SIZE = 100;
/*
	\brief This function reads a text file to memory, reads it char by char and returns data as char *

	Also filters out according to specs.

	\param path Path to the file
*/
void readFileToEndFilerAndParse(std::string path, int *outputArr)
{
	char buffer[ARR_SIZE] = { '\0' };
	if (path != "")
	{
		std::ifstream dataFile(path);
		if (dataFile.is_open())
		{
			char singleChar = 0;
			size_t actualChar = 0;
			while (dataFile >> singleChar)
			{
				if ((singleChar >= '0' && singleChar <= '9') || toupper((singleChar >= 'A' && singleChar <= 'F')))
				{
					buffer[actualChar] = singleChar;
					actualChar++;
				}
				
			}
		}
		size_t dataSetSize = strlen(buffer);
		for (size_t actualElement = 0; actualElement < dataSetSize - 1; actualElement++)
		{
			char singleElement[3] = { buffer[actualElement], buffer[actualElement + 1], '\0' };
			int byteOut = -1;
			sscanf_s(singleElement, "%X", &byteOut);
			outputArr[actualElement] = byteOut;
		}
		dataFile.close();
	}
}
/*
	\brief This function will divide input array consiting bytes into two arrays depending on oddness of ones in byte.

	I'm assuming that the assigment is talking about ones in binary form of the hex. 

	\param bytes Our input bytes array

	\param *evens Resulting even array

	\param *odds Resulting odd array
*/
void divideArrayByOnes(int *bytes, int *evens, int *odds)
{
	size_t actualByte = 0;
	int singleByte = 0;
	size_t oddsPos = 0; //pos of odds array
	size_t evenPos = 0; //as above
	while (singleByte != -1)
	{
		singleByte = bytes[actualByte];
		unsigned int onesCount = 0;
		int dividedByte = singleByte;
		while (true)
		{
			if (0 == dividedByte)
			{
				actualByte++;
				break;
			}
			if (1 == dividedByte % 2)
			{
				onesCount++;
			}
			dividedByte /= 2;
		}
		if (onesCount != 0)
		{
			if (0 == onesCount % 2) //the count is even
			{
				evens[evenPos] = singleByte;
				evenPos++;
			}
			else
			{
				odds[evenPos] = singleByte;
				oddsPos++;
			}
		}
	}  

}
/*
	\brief Function sorts both arrays. Uses std::sort

	\param odds Array consisting bytes with odd ones

	\param evens Array consisting bytes with even ones
*/
void sortOddAndEvenArrays(int *odds, int *evens)
{
	std::sort(odds, odds+(ARR_SIZE-1), std::greater<int>());
	std::sort(evens, evens+(ARR_SIZE-1));
}
/*
	\brief Function writes resulting arrays to files. Omits -1, which indicates empty space in array.

	evens.txt will contain sorted data from evens array, odds.txt will contain sorted data from odds data

	As an added bonus, for improved reladibility, I've added spaces between bytes in resulting files.

	\param odds Array consisting bytes with odd ones

	\param evens Array consisting bytes with even ones
*/
void writeOutputToFile(int *odds, int *evens)
{
	bool isWriteSuccessfull = false;
	std::ofstream evensOutputFileStream("evens.txt", std::ofstream::out);
	std::ofstream oddsOutputFileStream("odds.txt", std::ofstream::out);
	for (int actualElementFromBothArray = 0; actualElementFromBothArray < ARR_SIZE; actualElementFromBothArray++)
	{
		int singleEven = evens[actualElementFromBothArray];
		int singleOdd = odds[actualElementFromBothArray];
		if (singleEven != -1)
		{
			evensOutputFileStream << " " << singleEven;
		}
		if (singleOdd != -1)
		{
			oddsOutputFileStream << " " << singleOdd;
		}
	}
	evensOutputFileStream.close();
	oddsOutputFileStream.close();
}
/*
	App entry point.
*/
int main()
{
	int bytes[ARR_SIZE];
	int oddsAray[ARR_SIZE];
	int evensArray[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; i++) //-1 means no byte is at the index.
	{
		bytes[i] = -1;
		oddsAray[i] = -1;
		evensArray[i] = -1;
	}
    readFileToEndFilerAndParse("file.txt", bytes);
	divideArrayByOnes(bytes, evensArray, oddsAray);
	sortOddAndEvenArrays(oddsAray, evensArray);
	writeOutputToFile(oddsAray, evensArray);
    return 0;
}

