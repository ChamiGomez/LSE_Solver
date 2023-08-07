//Program: Linear Systems of Equations Solver
//This file contains the calculation functions from C_LSE_Solver.h which are required to solve linear systems of equations

#include "C_LSE_Solver.h"

//Create an Upper Triangular Matrix using Gaussian Elimination algorithmn
void C_LSE_Solver::Create_Upper_Triangular_Matrix(void) {
	for (int k = 0; k < rows - 1; k++) {															//Loop over each pivot row, except for the last row (hence rows -1), which will never need to be used as a pivot row
		for (int i = k + 1; i < rows; i++) {														//Loop over each row below the pivot row (hence k + 1)
			double Scale_Factor = Square_Matrix[i][k] / Square_Matrix[k][k];						//Set value for scale factor - first term in the manipulated row divided by the first term in the pivot row
			for (int j = k; j < rows; j++)															//Loop over each element - start at k as elements before k are zero. Note 'rows' is used as this is a square matrix
				Square_Matrix[i][j] = Square_Matrix[i][j] - (Scale_Factor * Square_Matrix[k][j]);	//Updated current row of Matrix by looping over column j
			RHS_Vector[i] = RHS_Vector[i] - (Scale_Factor * RHS_Vector[k]);							//Update RHS_Vector in corresponding fashion
		}
	}
}

//Perform Back Substitution on an Upper Traingular Matrix using algorithmn from Numerical Methods
//Note: If there are infinite solutions (so if there is an entire row of 0s) then this will push -nan values into Solution_Vector as there is no unique solution
void C_LSE_Solver::Back_Substitution(void) {
	Solution_Vector.resize(rows);																//Set the size of the solution vector to the number of rows
	for (int k = rows - 1; k > -1; k--)	{														//Start at the penultimate row and work backwards (as this is back not forward substitution)
		double Summation_Total = 0.0;															//Reinitialise the summation total for each row
		for (int j = k + 1; j < rows; j++)														
			Summation_Total = Summation_Total + (Square_Matrix[k][j] * Solution_Vector[j]);		//Summation calculation using limits, using the solution vector value from the row above
		Solution_Vector[k] = (RHS_Vector[k] - Summation_Total) / Square_Matrix[k][k];
	}
}