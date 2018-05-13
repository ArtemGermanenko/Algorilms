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

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int size;
	in >> size;
	char* Operations = new char[2 * size];
	MinAndMax** MainArray = new MinAndMax*[2 * size];
	for (int i = 0; i < 2 * size; i++)
		MainArray[i] = new MinAndMax[2 * size];
	long long s;
	for (int i = 0; i < size; i++)
	{
		in >> Operations[i];
		Operations[i + size] = Operations[i];
		in >> s;
		MainArray[i][i].minimum = s;
		MainArray[i][i].maximum = s;
		MainArray[i + size][i + size].maximum = s;
		MainArray[i + size][i + size].minimum = s;
	}
	long long MAX;
	long long max = 9223372036854775808;
	max = 0 - max;
	long long MIN;
		for (int index = 1; index < size; index++)
		{
			for (int current = 0; current < 2*size - index - 1; current++)
			{
				MAX = 9223372036854775808;
				MAX = 0 - MAX;
				MIN = 9223372036854775807;
				for (int i = 0; i <= index - 1; i++)
				{
					if (MAX < findMax(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], Operations[index + current - i]))
						MAX = findMax(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], Operations[index + current - i]);
					if (MIN > findMin(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], Operations[index + current - i]))
						MIN = findMin(MainArray[current + index - i][current + index], MainArray[current][index + current - i - 1], Operations[index + current - i]);
				}
				MainArray[current][index + current].maximum = MAX;
				MainArray[current][index + current].minimum = MIN;
				if (index == size - 1) {
					if (MainArray[current][index + current].maximum > max)
						max = MainArray[current][index + current].maximum;
				}
			}
	}
	out << max << endl;
	bool isFirst = true;
	for (int index = 0; index < size; index++)
	{
		if (max == MainArray[index][index + size - 1].maximum) {
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