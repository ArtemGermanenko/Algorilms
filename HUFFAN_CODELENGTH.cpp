#include <iostream>
#include <list>
#include <fstream>
#include <queue>
#include<stack>

using namespace std;

ifstream in("huffman.in");
ofstream out("huffman.out");

long long calc(long long *A, long long* testdata, int n) {
	long long i, sum = 0;
	for (i = 0; i<n; i++) {
		sum += A[i] * testdata[i];
	}
	return sum;
}



int main(int argc, char *argv[])
{
	int size;
	int versh;
	in >> size;
	long long* array = new long long[size];
	for (int i = 0; i < size; i++) {
		in >> versh;
		array[i] = versh;
	}
	long long i;
	long long* data = new long long[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = array[i];
	}

	if (size > 1) {
		array[0] += array[1];
		int r = 0, s = 2, t = 1;
		while (s != size) {
			if (array[r] < array[s]) {
				if ((r + 1 < t) && (array[r + 1] < array[s])) {
					array[t] = array[r] + array[r + 1];
					array[r++] = t;
					array[r++] = t++;
				}
				else {
					array[t] = array[r] + array[s++];
					array[r++] = t++;
				}
			}
			else {
				if ((array[r] < array[s + 1]) || (s + 1 == size)) {
					array[t] = array[s++] + array[r];
					array[r++] = t++;
				}
				else {
					array[t++] = array[s] + array[s + 1];
					s += 2;
				}
			}
		}
		while (t != size - 1) {
			array[t] = array[r] + array[r + 1];
			array[r++] = t;
			array[r++] = t++;
		}
	}
	long long level = size - 2;
	long long depth = 1;
	i = size;
	long long j, k;
	long long nodes = 2;
	while (i > 0) {
		for (k = level; k>0 && array[k - 1] >= level; k--) {}

		long long nodesI = level - k;
		long long leaves_at_level = nodes - nodesI;
		for (j = 0; j<leaves_at_level; j++) {
			array[--i] = depth;
		}
		nodes = nodesI * 2;
		level = k;
		depth++;
	}
	long long cost = calc(array, data, size);
	out << cost;
	out.close();
	in.close();
	return 0;
}