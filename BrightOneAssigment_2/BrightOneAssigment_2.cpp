#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
/**
*	\brief This function takes input according to specs in assigment. 
*
*	I am going to use std::vector for sake of similicity and make to algorithm implementation a bit easier to me, I won't need to play with dynamic memory allocation, std::vector will take of that.
*
*	\param &inputSequences - a two-dimensional std::vector<std::vector<int>> containing input sequences
*
*	\returns errorCode - Error code. If 0 - all ok, If 1 - you have provided a number less than 0 e.g negative number for inputSequencesCount. If 2 - the same situation, but for digitCountPerTestCase.
*
*	Excuse me the use of magic numbers, all error codes are for myself to aid my debugging efforts. 
*/
int takeInput(std::vector< std::vector<int> > &inputSequences)
{
	int errorCode = 0; 
	size_t inputSequencesCount = 0;
	std::cin >> inputSequencesCount;

	if (inputSequencesCount > 0)
	{
		for (size_t actualSequence = 0; actualSequence < inputSequencesCount; actualSequence++)
		{
			size_t digitCountPerTestCase = 0; ///this will be the same case, if 0 or negative value will be inputted - we exit
			std::cin >> digitCountPerTestCase;
			std::vector<int> sequence(digitCountPerTestCase);

			if (digitCountPerTestCase < 0)
			{
				errorCode = 2;
				break;
			}
			
			for (size_t actualDigit = 0; actualDigit < digitCountPerTestCase; actualDigit++)
			{
				int singleDigit = 0;
				std::cin >> singleDigit;
				std::cin.ignore(1, ' ');
				sequence[actualDigit] = singleDigit;
			}
			inputSequences.push_back(sequence);
		}
	}
	else
	{
		errorCode = 1; ///you have inputted a 0 or negative number, we cannot input *that* much data
		return errorCode;
	}
	return errorCode;
}
/**
*
*	\brief Function calculates sums of left-side and right-side elements.
*	
*	\param &leftSideNumbers Reference to element to the left from central element
*
*	\param &rightSideNumbers Reference to element to the right from central element
*
*	\returns std::pair<int, int> containing sums. First is left-side element sum, second is right-side element sum.
*/
std::pair<int, int> calculateSums(std::vector<int> &leftSideNumbers, std::vector<int> &rightSideNumbers)
{
	std::pair<int, int> sums; 
	int leftSum = 0;
	int rightSum = 0;
	for (size_t actualDigit = 0; actualDigit < leftSideNumbers.size(); actualDigit++)
	{
		leftSum += leftSideNumbers[actualDigit];
	}
	for (size_t actualDigit = 0; actualDigit < rightSideNumbers.size(); actualDigit++)
	{
		rightSum += rightSideNumbers[actualDigit];
	}
	sums.first = leftSum;
	sums.second = rightSum;
	return sums;
}
/**
*	\brief This function will extract left-side and right-side elements to actual element.
*
*	\param &sequences Reference to input sequences.
*
*	\returns std::vector<std::pair<int,int>> consisting of summed pairs for input sequences
*/
std::vector<std::pair<int,int>> parseSequencesAndSumSequences(std::vector<std::vector<int>> &sequences)
{
	std::vector<std::pair<int, int>> sums;
	for (size_t actualSequence = 0; actualSequence < sequences.size(); actualSequence++)
	{
		std::vector<int> singleSequence = sequences[actualSequence];
		for (size_t actualDigit = 1; actualDigit < singleSequence.size() - 1; actualDigit++)
		{
			std::vector<int> elementsToTheLeft;
			std::vector<int> elementsToTheRight;
			elementsToTheLeft.push_back(singleSequence[0]); //to make sure that first element is present
			for (size_t actualElementForLeftSequence = actualDigit; actualElementForLeftSequence > 0; actualElementForLeftSequence--)
			{
				if (actualElementForLeftSequence != actualDigit)
				{
					elementsToTheLeft.push_back(singleSequence[actualElementForLeftSequence]);
				}
			}

			for (size_t actualElementForRightSequence = actualDigit; actualElementForRightSequence < singleSequence.size(); actualElementForRightSequence++)
			{
				if (actualElementForRightSequence != actualDigit)
				{
					elementsToTheRight.push_back(singleSequence[actualElementForRightSequence]);
				}
			}
			std::pair<int,int> singleSum = calculateSums(elementsToTheLeft, elementsToTheRight);
			sums.push_back(singleSum);
		}
	}
	return sums;
}
/**
*	\brief Function compares all sums of left-side and right-side elements
*	
*	Prints out to stdout "No" if boundary requirement is not satisfied, prints "Yes" if requierment is satisfied
*
*	\param &sums Reference to left-side and right-side sum of elements
*	
*
*/
void compareSumPairs(std::vector<std::pair<int, int>> &sums)
{
	if (sums.size() > 0)
	{
		for (size_t actualSum = 0; actualSum < sums.size(); actualSum++)
		{
			if (sums[actualSum].first == sums[actualSum].second)
			{
				std::cout << "Yes" << std::endl;
			}else
			{
				std::cout << "No" << std::endl;
			}
		}
	}
	
}
int main()
{
	std::vector<std::vector<int>> inputSequences; ///our inputted sequences
    takeInput(inputSequences);
	std::vector<std::pair<int,int>> sums = parseSequencesAndSumSequences(inputSequences);
	compareSumPairs(sums);
	return 0;
}

