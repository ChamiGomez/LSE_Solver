//Program: Linear Systems of Equations Solver
//This file contains the C_LSE_Solver class declaration and the declarations of output data functions used in the program

#pragma once
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class C_LSE_Solver {
public:
	vector<vector<double>> Matrix2D, Square_Matrix;				//Create a 2D Matrix for intial data and a Square Matrix to store the values of A
	vector<double> RHS_Vector, Solution_Vector;					//Create a RHS Vector to store the values of b, and a Solution vector containing x values for the solution to Ax = b
	int rows, columns;
	string Dataset_Name;

	//Constructors
	C_LSE_Solver();
	C_LSE_Solver(const C_LSE_Solver& in);

	//Read data functions
	void Read_Matrix_Properties_from_User(void);
	bool Read_Matrix_from_File(void);							//Reading a matrix of known size from a file provided by the user (returns if this was the desired shape or not)
	void Read_Matrix_Elements_from_User(void);
	void Parse_Data_into_Square_Matrix_and_RHS_Vector(void);	//Split original matrix into a square matrix and a RHS vector

	//Matrix Calculation Functions
	void Create_Upper_Triangular_Matrix(void);					//Create an Upper Traingular Matrix from Square_Matrix
	void Back_Substitution(void);								//Create a Solution_Vector from an upper triangular matrix
};

//Output data functions, includes Preliminary_Output_File_Checks in Output Data Handling.cpp
void Write_to_Screen(const vector<vector<double>> matrix, const string name);
void Write_to_Screen(const vector<vector<double>> matrix, const vector<double> vec, const string name);
void Write_to_Screen(const vector<double> vec, const string name);
void Write_to_File(const vector<vector<double>> matrix, const string name);
void Write_to_File(const vector<vector<double>> matrix, const vector<double> vec, const string name);
void Write_to_File(const vector<double> vec, const string name);