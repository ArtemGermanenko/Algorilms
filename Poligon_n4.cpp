#include<iostream>
#include<fstream>

using namespace std;

struct MinAndMax
{
	long long minimum;
	long long maximum;
};

long long findMax(MinAndMax One, MinAndMax Two, char operation)
{
	long long maximum;
	if (operation == 't') {
		maximum = One.maximum + Two.maximum;
		if (maximum < One.minimum + Two.minimum)
			maximum = One.minimum + Two.minimum;
		if (maximum < One.minimum + Two.maximum)
			maximum = One.minimum + Two.maximum;
		if (maximum < One.maximum + Two.minimum)
			maximum = One.maximum + Two.minimum;
	}
	else
	{
		maximum = One.maximum * Two.maximum;
		if (maximum < One.minimum * Two.minimum)
			maximum = One.minimum * Two.minimum;
		if (maximum < One.minimum * Two.maximum)
			maximum = One.minimum * Two.maximum;
		if (maximum < One.maximum * Two.minimum)
			maximum = One.maximum * Two.minimum;
	}
	return maximum;
}

long long findMin(MinAndMax One, MinAndMax Two, char operation)
{
	long long minimum;
	if (operation == 't') {
		minimum = One.maximum + Two.maximum;
		if (minimum > One.minimum + Two.minimum)
			minimum = One.minimum + Two.minimum;
		if (minimum > One.minimum + Two.maximum)
			minimum = One.minimum + Two.maximum;
		if (minimum > One.maximum + Two.minimum)
			minimum = One.maximum + Two.minimum;
	}
	else
	{
		minimum = One.maximum * Two.maximum;
		if (minimum > One.minimum * Two.minimum)
			minimum = One.minimum * Two.minimum;
		if (minimum > One.minimum * Two.maximum)
			minimum = One.minimum * Two.maximum;
		if (minimum > One.maximum * Two.minimum)
			minimum = One.maximum * Two.minimum;
	}
	return minimum;
}

char* OperationsToRemake(char* Operations, int size, int number) {
	char* current = new char[size];
	int index = 0;
	for (int i = number; i < size; i++)
	{
		current[index] = Operations[i];
		index++;
	}
	for (int i = 0; i < number; i++)
	{
		current[index] = Operations[i];
		index++;
	}
	return current;
}

MinAndMax** NumbersToRemake(MinAndMax** array, long long* Numbers, int size, int number) {
	MinAndMax** toOut = new MinAndMax*[size];
	for (int i = 0; i < size; i++)
		toOut[i] = new MinAndMax[size];
	int index = 0;
	for (int i = number; i < size; i++)
	{
		toOut[index][index].maximum = Numbers[i];
		toOut[index][index].minimum = Numbers[i];
		index++;
	}
	for (int i = 0; i < number; i++)
	{
		toOut[index][index].maximum = Numbers[i];
		toOut[index][index].minimum = Numbers[i];
		index++;
	}
	return toOut;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int size;
	in >> size;
	char* Operations = new char[size];
	long long* Numbers = new long long[size];
	char* OperationsAAA = new char[size];
	long long* NumbersAAA = new long long[size];
	MinAndMax** MainArray = new MinAndMax*[size];
	for (int i = 0; i < size; i++)
		 MainArray[i] = new MinAndMax[size];
	for (int i = 0; i < size; i++)
	{
		in >> Operations[i];
		in >> Numbers[i];
	}
	long long* ArrayOfAllMaxmimum = new long long[size];
	long long MAX;
	long long max = 9223372036854775808;
	max = 0 - max;
	long long MIN;
	for (int MainIndex = 0; MainIndex < size; MainIndex++)
	{
		MainArray = NumbersToRemake(MainArray, Numbers, size, MainIndex);
		for (int index = 1; index < size; index++)
		{
			OperationsAAA = OperationsToRemake(Operations, size, MainIndex);
			for (int current = 0; current < size - index; current++)
			{
				MAX = 9223372036854775808;
				MAX = 0 - MAX;
				MIN = 9223372036854775807;
				for (int i = 0; i <= index - 1; i++)
				{
					if (MAX < findMax(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], OperationsAAA[index + current - i]))
						MAX = findMax(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], OperationsAAA[index + current - i]);
					if (MIN > findMin(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], OperationsAAA[index + current - i]))
						MIN = findMin(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], OperationsAAA[index + current - i]);
				}
				MainArray[current][index + current].maximum = MAX;
				MainArray[current][index + current].minimum = MIN;
			}
		}
		if (MainArray[0][size - 1].maximum > max)
			max = MainArray[0][size - 1].maximum;
		ArrayOfAllMaxmimum[MainIndex] = MainArray[0][size - 1].maximum;
	}
	out << max << endl;
	bool isFirst = true;
	for (int index = 0; index < size; index++)
	{
		if (max == ArrayOfAllMaxmimum[index]) {
			if (!isFirst)
				out << " " << index + 1;
			else
				out << index + 1;
			isFirst = false;
		}
	}
	in.close();
	out.close();
	return 0;
}
