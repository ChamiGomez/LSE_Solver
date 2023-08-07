//Program: Linear Systems of Equations Solver
//This file contains the data handling functions from C_LSE_Solver.h

#include "C_LSE_Solver.h"
#include <iostream>
#include <sstream>
#include <conio.h>

//Read matrix properties from user
void C_LSE_Solver::Read_Matrix_Properties_from_User(void) {
	//Get matrix name
	cout << "Enter name of matrix:\n";
	getline(cin, Dataset_Name);

	cout << "For augmented matrix of square matrix A and RHS vector b:\n";
	//Get matrix shape
	do {
		cout << "Enter number of columns: ";
		cin >> columns;
		cout << "Enter number of rows: ";
		cin >> rows;
		if (columns != rows + 1)
			cout << "Incompatible matrix shape entered.\nThis function reads in the augmented matrix of the square matrix A and RHS vector b for Ax = b,\nso the number of columns should be one more than the number of rows.\n\n";
	} while (columns != rows + 1);	//Repeat while the matrix shape is incorrect			

	//Set Matrix2D size
	Matrix2D.resize(rows);
	for (int i = 0; i < rows; i++)
		Matrix2D[i].resize(columns);
}

//Reading a matrix of known size from a file provided by the user (returns if this was the desired shape or not)
bool C_LSE_Solver::Read_Matrix_from_File(void) {	
	///Put Formatting disclaimer in .readme
	///cout << endl << "Note: File must be in a tab-delineated .txt file, with only coefficients (no square brackets/commas etc.)" << endl;

	ifstream Data_In;
	string input_filename, LineIn;
	bool input_file_opened_successfully = false;

	//Open the file
	cin.ignore(INT_MAX, '\n'); //Clear buffer from previous cin >> uses
	do {
		//Get filename and open file for reading only
		cout << "Enter input filename (including '.txt'):\n";
		getline(cin, input_filename);
		Data_In.open(input_filename, fstream::in); 

		//Check if the file opened correctly
		if (Data_In.fail())
			cout << "Error opening file for reading. Please try again\n";
		else {
			cout << "File opened for reading successfully\n";
			input_file_opened_successfully = true;
		}
	} while (!input_file_opened_successfully);

	//Read file contents into TempMatrix
	vector<vector<double>> TempMatrix;
	while (getline(Data_In, LineIn)) {
		istringstream Input_String_Stream(LineIn);
		string Word;
		double ElementValue;
		vector<double> TempVector;
		while (getline(Input_String_Stream, Word, '\t')) {
			ElementValue = stod(Word);
			TempVector.push_back(ElementValue);
		}
		TempMatrix.push_back(TempVector);
	}

	//Check that read in data matches the shape entered by the user
	if (rows != TempMatrix.size()) {
		cout << "Number of rows entered by user: " << rows << "\nNumber of rows read from file: " << TempMatrix.size() << endl;
		cout << "The matrix that was read in from file does not match the shape entered by user. Check the file or check the correct shape was entered and try again!\n";
		return false;
	}
	for (int i = 0; i < rows; i++) {
		if (columns != TempMatrix[i].size()) {
			cout << "Number of columns entered by user: " << columns << "\nNumber of columns read from file on row " << i + 1 << ": " << TempMatrix[i].size() << endl;
			cout << "The matrix that was read in from file does not match the shape entered by user. Check the file or check the correct shape was entered and try again!\n";
			return false;
		}
	}
	//Once the data has been confirmed to contain a matrix of the required shape, assign values that were read into TempMatrix to Matrix2D
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			Matrix2D[i][j] = TempMatrix[i][j];
	}

	Data_In.close();
	cout << endl;
	return true;
}

//Read individual values for each element of the matrix from the user
void C_LSE_Solver::Read_Matrix_Elements_from_User(void) {
	double TempMatrixElement;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "Enter " << Dataset_Name << "[" << i << "][" << j << "]: ";
			cin >> TempMatrixElement;
			Matrix2D[i][j] = TempMatrixElement;
		}
		cout << endl;
	}
	cout << endl;
}

//Split original matrix into a square matrix and a RHS vector
void C_LSE_Solver::Parse_Data_into_Square_Matrix_and_RHS_Vector(void) {
	//Set Square_Matrix size
	Square_Matrix.resize(C_LSE_Solver::rows);
	for (int i = 0; i < C_LSE_Solver::rows; i++)
		Square_Matrix[i].resize(C_LSE_Solver::rows);	//This is 'rows' not 'columns' as this is a square matrix
	
	//Copy data from Matrix2D to Square_Matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			for (int k = 0; k < rows; k++)				//For values that go into the square matrix i.e.: every column except the final one (hence k < rows not k < columns)
				Square_Matrix[i][k] = Matrix2D[i][k];
			if (j == rows)								//For the final column (which is rows because matrix indexing starts from 0 but indexing for C_LSE_Solver::rows starts from 1 for human use)
				RHS_Vector.push_back(Matrix2D[i][j]);
		}
	}
}