#include <iostream> 
#include <fstream> 
#include <stack> 
#include<vector>

using namespace std;

ifstream in("in.txt");
ofstream out("out.txt");

vector<int>** vniz(vector<int>** A, int i, int j, int k) {
	for (int h = 0; h < k / 2; h++) {
		for (int l = 0; l < i; l++) {
			for (int w = 0; w < j; w++) {
				int cur = A[l][w].front();
				A[l][w].erase(A[l][w].begin());
				A[2*j - l - 1][w].insert(A[2*j - l - 1][w].begin(),cur);
			}
		}
	}
	return A;
}

vector<int>** vpravo(vector<int>** A, int i, int j, int k) {
	for (int h = 0; h < k / 2; h++) {
		for (int l = 0; l < i; l++) {
			for (int w = 0; w < j; w++) {
				int cur = A[l][w].front();
				A[l][w].erase(A[l][w].begin());
				A[l][2*j - w - 1].insert(A[l][2*j - w - 1].begin(), cur);
			}
		}
	}
	return A;
}

int main() {
	int size;
	in >> size;
	int kletki = pow(4, size);
	vector<vector<int>> arr;
	vector<int>** matr = new vector<int>*[kletki];
	for (int i = 0; i < kletki; i++)
	{
		matr[i] = new vector<int>[kletki];
	}

	for (int i = 0; i < kletki; i++) {
		matr[0][0].push_back(kletki - i);
	}
	int s = 1;
	int l = 1;
	int siz = kletki;
	for (int i = 0; i < kletki / 4; i++) {
		matr = vniz(matr, s, l, siz);
		s*=2;
		siz /= 2;
		matr = vpravo(matr, s, l, siz);
		l*=2;
		siz /= 2;
	}
	int t = pow(2, size);
	for (int i = 0; i < kletki / t; i++) {
		for (int j = 0; j < kletki/ t; j++)
		{
			out << matr[i][j][0];
			if (j != kletki / t - 1 || i != kletki / t - 1) {
				out << " ";
			}
		}
	}
	
	system("pause");
	in.close();
	out.close();
	return 0;
}