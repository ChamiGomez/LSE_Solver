//Program: Linear Systems of Equations Solver
//This file contains the functions written to hangle the ouput of data within the LSE Solver program

#include "C_LSE_Solver.h"
#include <iostream>
#include <conio.h>

void Write_to_Screen(const vector<vector<double>> matrix, const string name) {
	cout << name << " matrix:\n[\t";
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
            if (j + 2 < matrix[i].size()) cout << matrix[i][j] << ",\t";
            else if (name == "Square") {
                cout << matrix[i][j] << ",\t" << matrix[i][j + 1];
                break;
            }
            else {
                cout << matrix[i][j] << "\t|\t" << matrix[i][j + 1];
                break;
            }
		}
		if (i + 1 < matrix.size()) cout << "\n\t";
	}
	cout << "\t]\n";
}

void Write_to_Screen(const vector<vector<double>> matrix, const vector<double> vec, const string name) {
    cout << name << " matrix:\n[\t";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++)
            (j + 1 < matrix[i].size()) ? cout << matrix[i][j] << ",\t" : cout << matrix[i][j] << "\t|\t" << vec[i];
        if (i + 1 < matrix.size()) cout << "\n\t";
    }
    cout << "\t]\n";
}

void Write_to_Screen(const vector<double> vec, const string name) {
	cout << name << " vector:\n[\t";
	for (int i = 0; i < vec.size(); i++)
		(i + 1 < vec.size()) ? cout << vec[i] << ",\t" : cout << vec[i] << "\t]\n";
}

fstream Preliminary_Output_File_Checks(string filename) { 
    fstream file;
    bool correct_filename = false;
    char option = 'x'; //Dummy assignment to initialise local variable for do...while check below - is overwritten in that loop
    do {
        file.open(filename, fstream::out | fstream::in);  //Won't create file
        if (file.is_open()) { //If file already exists
            cout << "Warning: " << filename << " already exists. Would you like to overwrite the file, try a new filename, append the matrix to the file or exit?\n";
            cout << "(O) - Overwrite the file, (R) - Retry with new filename, (A) - Append the matrix or (E) - Exit. Enter option: ";
            do {
                char option = _getch();
                if (toupper(option) == 'O') correct_filename = true;
                else if (toupper(option) == 'R') getline(cin, filename);
                else if (toupper(option) == 'A') correct_filename = true;
                else if (toupper(option) == 'E') exit(1);
                else
                    cout << "\nInvalid option entered. Please enter (O/R/A/E): ";
            } while (toupper(option) != 'O' && toupper(option) != 'R' && toupper(option) != 'A' && toupper(option) != 'E');
        }
        else { // If file doesn't already exist
            file.clear();
            file.open(filename, fstream::out);
            if (file.fail()) {
                cout << "\nError creating file for writing! Please try a new filename: ";
                getline(cin, filename);
            }
            else {
                cout << "\nFile created for writing successfully...\n";
                return file;
            }
        }
    } while (!correct_filename);
    if (toupper(option) == 'O') { //File already exists but user wants to overwrite file
        file.close();
        file.open(filename, fstream::out);
        return file;
    }
    else { //User wants to append to file
        file.close();
        file.open(filename, fstream::app);
        return file;
    }
}

void Write_to_File(const vector<vector<double>> matrix, const string name) {
    fstream output_file;
    string output_filename;
    cout << "Please enter filename (remember to include .txt) for " << name << " matrix: ";
    getline(cin, output_filename);
    output_file = Preliminary_Output_File_Checks(output_filename);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++)
            (j + 1 < matrix[i].size()) ? output_file << matrix[i][j] << "\t" : output_file << matrix[i][j];
        if (i + 1 < matrix.size()) output_file << "\n";
    }
    output_file.close();
    cout << "Successfully wrote " << name << " matrix to file " << output_filename << ".\n";
}

void Write_to_File(const vector<vector<double>> matrix, const vector<double> vec, const string name) {
    fstream output_file;
    string output_filename;
    cout << "Please enter filename (remember to include .txt) for " << name << " matrix: ";
    getline(cin, output_filename);
    output_file = Preliminary_Output_File_Checks(output_filename);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++)
            (j + 1 < matrix[i].size()) ? output_file << matrix[i][j] << "\t" : output_file << matrix[i][j] << "\t" << vec[i];
        if (i + 1 < matrix.size()) output_file << "\n";
    }
    output_file.close();
    cout << "Successfully wrote " << name << " matrix to file " << output_filename << ".\n";
}

void Write_to_File(const vector<double> vec, const string name) {
    fstream output_file;
    string output_filename;
    cout << "Please enter filename (remember to include .txt) for " << name << " matrix: ";
    getline(cin, output_filename);
    output_file = Preliminary_Output_File_Checks(output_filename);
    for (int i = 0; i < vec.size(); i++)
        (i + 1 < vec.size()) ? output_file << vec[i] << "\t" : output_file << vec[i];
    output_file.close();
    cout << "Successfully wrote " << name << " matrix to file " << output_filename << ".\n";
}