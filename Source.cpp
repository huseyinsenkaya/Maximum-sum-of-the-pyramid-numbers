#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int isPrime(int n)
{
	int i;
	bool prime = true;
	if (n == 0 || n == 1) {
		prime = false;
	}
	else {
		for (i = 2; i <= n / 2; ++i) {
			if (n % i == 0) {
				prime = false;
				break;
			}
		}
	}
	if (prime)
		return 0;
	else
		return n;
}

int max(int n1, int n2) {
	if (n1 > n2)
		return n1;

	if (n2 > n1)
		return n2;
}

void printMatrix(std::vector<std::vector<int>>* mat) {
	//Print Matrix
	for (int i = 0; i < mat->size(); ++i)
	{
		for (int j = 0; j < (*mat)[i].size(); ++j)
		{
			std::cout << (*mat)[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int maxSum(std::vector<std::vector<int>> mat, int row, int column)
{
	for (int i = 1; i < mat.size(); i++) {
		for (int j = 0; j < mat[i].size(); j++) {
			if (j > 0 && j < mat[i].size() - 1)
				mat[i][j] += max(mat[i - 1][j], mat[i - 1][j - 1]);
			else if (j > 0)
				mat[i][j] += max(mat[i - 1][j],
					mat[i - 1][j - 1]);
			else if (j < mat[i].size() - 1)
				mat[i][j] += mat[i - 1][j];
		}
	}
	int sum = 0;
	for (int j = 0; j < column; j++)
		sum = max(mat[row - 1][j], sum);
	return sum;
}

void extractNumbers(std::string str, std::vector<std::vector<int>>* mat, int row) {
	std::stringstream lineStream;
	lineStream << str;
	std::string temp;
	int number;
	int i = 0;
	while (!lineStream.eof())
	{
		lineStream >> temp;
		if (std::stringstream(temp) >> number) {
			(*mat)[row][i] = isPrime(number);
			i++;
		}
		temp = "";
	}
}

int main() {
	std::fstream myFile;
	int row = 0, i = 0, a = 0, column, k = 0;

	std::string line;

	//Get the file's columns and rows for the matrix.
	myFile.open("input2.txt", std::ios::in);
	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			row++;
		}
	}
	myFile.close();
	for (column = 0; column < line.length(); column++)
	{
		if (line[column] == ' ') {
			k++;
		}
	}

	int matrixRow = row;
	int matrixColumn = k + 1;

	//Initializing a vector of zeros and store the values inside the matrix
	myFile.open("input2.txt", std::ios::in);
	std::vector<std::vector<int>> matrix(matrixRow, std::vector<int>(matrixColumn, 0));
	//printMatrix(&matrix);
	row = 0;
	if (myFile.is_open()) {
		while (std::getline(myFile, line)) {
			extractNumbers(line, &matrix, row);
			row++;
		}
	}
	myFile.close();

	//printMatrix(&matrix);

	std::cout << "Max: " << maxSum(matrix, matrixRow, matrixColumn);
	return 0;
}