//Program: Linear Systems of Equations Solver
//This file contains the constructors for class C_LSE_Solver

#include "C_LSE_Solver.h"

//Default constructor initialise member variables
C_LSE_Solver::C_LSE_Solver() {
	rows = 0;
	columns = 0;
}

//Copy constructor
C_LSE_Solver::C_LSE_Solver(const C_LSE_Solver& in) {
	Matrix2D = in.Matrix2D;
	Square_Matrix = in.Square_Matrix;
	RHS_Vector = in.RHS_Vector;
	rows = in.rows;
	columns = in.columns;
	Dataset_Name = in.Dataset_Name;
}