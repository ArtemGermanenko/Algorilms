#include<iostream>
#include<string> 
#include<fstream>
#include<stdlib.h>
#include<iostream>

using namespace std;

int BinarySearch(long long array[], long long key, int size) {
	int left = 0;
	int right = size;

	while (true) {
		int mid = (int)floor((right + left) / 2);
		if (array[mid] == key)
			return mid;
		if (array[mid] > key)
			right = mid;
		else
			left = mid + 1;
		if (right == left)
			return right;
	}
}

int NiceWorkFriends(long long* input, int size) {
	if (size == 1) {
		return 1;
	}
	int LittleSize = 1;
	long long* Little = new long long[size];
	Little[0] = input[0];
	int max = 1;
	int j = 1;

	for (int i = 1; i < size; i++)
	{
		if (input[i - 1] != input[i])
		{
			int index = BinarySearch(Little, input[i], LittleSize);
			if (max < index + 1)
				max = index + 1;
			Little[index] = input[i];
			if (index == LittleSize)
				LittleSize++;
		}
	}
	return max;
}

int main()
{
	ifstream in("input.txt");
	int size;
	in >> size;
	long long current;
	int i = 0;
	if (in.eof())
		return 0;
	long long* input = new long long[100001];
	while (!in.eof()) {
		in >> current;
		input[i] = current;
		i++;
	}
	int rezult = NiceWorkFriends(input, i);
	ofstream out("output.txt");
	out << rezult;
	in.close();
	out.close();
	return 0;
}
