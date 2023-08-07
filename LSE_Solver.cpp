//Program: Linear Systems of Equations Solver
//This file containts the main() of the LSE Solver program

#include "C_LSE_Solver.h"
#include <iostream>
#include <conio.h>			//Includes function _getch() which is used for getting user selections
#include <locale>			//Includes toupper() which is used to remove ambiguity between lower and upper cases

int main(void) {
	//Write title and opening statement to screen
	cout << "Program Title: Linear Systems of Equations Solver\n";
	cout << "This program uses matrices to perform row operations on linear systems to solve Ax = b for x\n";

	char another_dataset = 'x';
	do {
		C_LSE_Solver Read_In_Matrix, Answer_Matrix; //Declared here to clear any previous data

		//Get initial matrix data
		char data_entry_type;	
		do {
			cout << "\nHow would you like to read in the data - from a file or type it in (F/T)? ";
			data_entry_type = _getch();
			if (toupper(data_entry_type) == 'F') { //Read matrix from file
				bool correct_matrix_shape;
				do {
					cout << endl << endl;
					Read_In_Matrix.Read_Matrix_Properties_from_User();
					correct_matrix_shape = Read_In_Matrix.Read_Matrix_from_File();
				} while (!correct_matrix_shape); //Repeat until the matrix shape that is read in is the same as the matrix shape entered by the user
			}
			else if (toupper(data_entry_type) == 'T') { //Type matrix
				cout << endl << endl;
				Read_In_Matrix.Read_Matrix_Properties_from_User();
				Read_In_Matrix.Read_Matrix_Elements_from_User();
			}
			else cout << "Invalid answer. Please try again\n";
		} while (!(toupper(data_entry_type) == 'F' || toupper(data_entry_type) == 'T'));

		//Matrix calculations, ouputting results along the way
		Write_to_Screen(Read_In_Matrix.Matrix2D, "Original");
		Read_In_Matrix.Parse_Data_into_Square_Matrix_and_RHS_Vector();		//Split the read in data in Matrix2D into its Square_Matrix and RHS_Vector components
		Write_to_Screen(Read_In_Matrix.Square_Matrix, "Square");
		Write_to_Screen(Read_In_Matrix.RHS_Vector, "RHS");
		//Call copy constructor to preserve inital data in case user wants to write it to file later (as data is overwritten when calling Create_Upper_Triangular_Matrix()
		Answer_Matrix = C_LSE_Solver(Read_In_Matrix);
		//Now that the data is in Answer_Matrix, perform Gaussian Elimination to create an upper traingular matrix and then solve using back substitution
		Answer_Matrix.Create_Upper_Triangular_Matrix();	//Create Upper Triangular Matrix using Gaussian Elimination
		Write_to_Screen(Answer_Matrix.Square_Matrix, Answer_Matrix.RHS_Vector, "Augmented Upper Triangular");
		Answer_Matrix.Back_Substitution(); //Solve using Back Substitution
		Write_to_Screen(Answer_Matrix.Solution_Vector, "Solution");


		//Write Matrix to file (optional)
		char matrix_selection = 'z'; //Dummy assignment, overwritten later with capitals (used to modify initial question to user, as will never be set to lowercase z again)
		do {
			(matrix_selection == 'z') ? cout << "\nWhich matrix/vector would you like to write to your file? If you would not like to write to a file, select No.\n" : cout << "\nWould you like to append an additional matrix/vector to your file?\n";
			if (matrix_selection == 'z' && toupper(data_entry_type) == 'T') cin.ignore(INT_MAX, '\n'); //Clear buffer from previous cin >> uses (if typed matrix was entered, clears the \n from the last element
			cout << "Options are: (M) for original matrix, (S) for original square matrix, (R) for original RHS vector, (A) for augmented upper triangular matrix, (X) for solution vector or (N) for no writing to file\n";
			matrix_selection = _getch();
			matrix_selection = toupper(matrix_selection);
			if (matrix_selection == 'M') Write_to_File(Read_In_Matrix.Matrix2D, "original");
			else if (matrix_selection == 'S') Write_to_File(Read_In_Matrix.Square_Matrix, "square");
			else if (matrix_selection == 'R') Write_to_File(Read_In_Matrix.RHS_Vector, "RHS");
			else if (matrix_selection == 'A') Write_to_File(Answer_Matrix.Square_Matrix, Answer_Matrix.RHS_Vector, "augmented upper triangular");
			else if (matrix_selection == 'X') Write_to_File(Answer_Matrix.Solution_Vector, "solution");
			else if (matrix_selection == 'N') continue;
			else cout << "Invalid entry. Please try again\n";
		} while (matrix_selection != 'N');

		//Add another dataset
		do {
			cout << "\nWould you like to add another dataset to perform further calculations for a different matrix? (Y/N): ";
			another_dataset = _getch();
			if (toupper(another_dataset) == 'Y') break;
			else if (toupper(another_dataset) == 'N') break;
			else cout << "Invalid entry. Please try again...";
		} while (another_dataset != 'N');
	} while (toupper(another_dataset) == 'Y'); //Repeat while the user wants to add further datasets

	cout << "\n\nThank you for using this Linear Systems of Equations Solver!\n\n";
	return 0;
}