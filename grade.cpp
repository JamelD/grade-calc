/*
Grade Calculator
*/

#include <iostream>		//Input-Output Stream
#include <iomanip> 	//Input-Output Manipulation
#include <ctime>		//C Time library
//#include <cmath>		//C Math Library
#include <cstring> 	//C String Library
#include <cstdlib>	//C Std Library
#include <string>		//String Object Library
#include <fstream> 		//file Stream objects Library
using namespace std;

void OpenFile(); //open file function
void Menu(); //menu function
void PrintCategory(const int, struct Category*); // Prints out categories from file.
void PrintAssignment(const int, struct Assignment*); // Prints out assignments from file.
void PrintAssignmentByCategory(const int, struct Category*, const int, struct Assignment*); // Prints out assignments for selected category from file.
void PrintGrade(const int, struct Category*, const int, struct Assignment*); // Prints out category points breakdown and final grade calc.

struct Category{ // Struct to hold category data from file
	int Num;
	string Name;
	double Weight;
};
struct Assignment{ // Struct to hold assignment data from file
	string Name;
	string Type;
	double Points_recv;
	double Total_points;
};

int main(){
	OpenFile();
	
	return 0;
}

void OpenFile(){
	char selection;
	int cat_size, assign_size; //hold size from file
	string file; 		//var to take in name of input file
	ifstream fileName; 	//Input file stream object
	
	cout << endl << "Enter the name of the file to open > ";
	cin >> file;	//take in the name of the file to read
	cout << endl;
	fileName.open(file.c_str());	//open the file
	while(!fileName){	//File error checking
		cout << "That file does not exist!" << endl;
		cout << "Enter the name of the file to open > ";
		cin >> file;
		fileName.open(file.c_str());
		cout << endl;
	}
	
	fileName >> cat_size; //first input from file, size of array
	Category *cat = new Category[cat_size]; //dynamic array of strucs
	for(int i = 0; i < cat_size; i++){	//store data from file into array of strucs
		fileName >> cat[i].Num;
		fileName >> cat[i].Name;
		fileName >> cat[i].Weight;
	}
    fileName >> assign_size;
    Assignment *assign = new Assignment[assign_size];
    for(int i = 0; i < assign_size; i++){
        fileName >> assign[i].Name;
        fileName >> assign[i].Type;
        fileName >> assign[i].Points_recv;
        fileName >> assign[i].Total_points;
    }
	do{ // file menu
		Menu();
		cout << "Selection > ";
		cin >> selection; 
		
		//eror checking for invalid menu entries
		while(selection != '1' && selection != '2' && selection != '3' && selection != '4' && selection != 'q' && selection != 'Q'){
			cout << "That is not a valid menu selecion!" << endl;
			cout << "Selection > ";
			cin >> selection; 
		}
		
		//Menu Selection
		if(selection == '1'){
			PrintCategory(cat_size, cat); //Call Print Categories Function
		}else if(selection == '2'){
			PrintAssignment(assign_size, assign); //call Print Assigments function
		}else if(selection == '3'){
			PrintAssignmentByCategory(cat_size, cat, assign_size, assign); //Print Assignments by Category
		}else if(selection == '4'){
			PrintGrade(cat_size, cat, assign_size, assign); // print grades function
		}else if(selection == 'q' || selection == 'Q'){
			break; //
		}
		
	}while(selection != 'q' || selection != 'Q');
	
	delete [] cat;	//delete dynamic array of struct
    delete [] assign;	//delete dynamic array of struct
	fileName.close(); 	//close the file filestream
}

void Menu(){ 
	cout << endl;
	cout << "Menu:" << endl;
    cout << "1 - Print Categories" << endl;
	cout << "2 - Print Assignments" << endl;
	cout << "3 - Print Assignments by Category" << endl;
	cout << "4 - Print Grades" << endl;
	cout << "Q - Quit" << endl;
}

void PrintCategory(const int cat_size, Category * cat){
	cout << endl;
	cout << "Categories:" << endl;
	for(int i = 0; i < cat_size; i++){
		cout << left << cat[i].Num << "\t";
		cout << left << setw(15) << cat[i].Name;
		cout << right << "Weight: " << cat[i].Weight << "%" << endl;
	}
}

void PrintAssignment(const int assign_size, Assignment * assign){ 
	cout << endl;
	cout << "Assignments:" << endl;
	for(int i = 0; i < assign_size; i++){
		cout << left << setw(15) << assign[i].Name;
        cout << left << setw(15) << assign[i].Type;
		cout << fixed << showpoint << setprecision(2); 
		cout << right << "Points : " << assign[i].Points_recv << " / ";
		cout << right << assign[i].Total_points << endl;	
	}
}

void PrintAssignmentByCategory(const int cat_size, struct Category* cat, const int assign_size, struct Assignment* assign){
    int select;
    
	cout << endl;
	cout << "Categories:" << endl;
	for(int i = 0; i < cat_size; i++){
		cout << left << cat[i].Num << "\t";
		cout << left << setw(15) << cat[i].Name;
		cout << right << "Weight: " << cat[i].Weight << "" << endl;
	}
    cout << "Select Category (use number): ";
    cin >> select;
	
	// Doesnt work.
	//category selction error checking
	// while(select > cat_size && select < 1){	
	// 	cout << "Invalid category selection" << endl;
	// 	cout << "Select Category (use number): ";
    // 	cin >> select;
	// }

    cout << endl;
	cout << "Assignments:" << endl;
	for(int i = 0; i < assign_size; i++){
		if(cat[select-1].Name == assign[i].Type){
            cout << left << setw(15) << assign[i].Name;
            cout << left << setw(15) << assign[i].Type;
            cout << fixed << showpoint << setprecision(2); 
			cout << right << "Points : " << assign[i].Points_recv << " / " << assign[i].Total_points << endl;
        }	
	}

}

void PrintGrade(const int cat_size, struct Category* cat, const int assign_size, struct Assignment* assign){
    double grade[cat_size], total[cat_size], grade_calc[cat_size], grade_weight;
	
	cout << endl;
	cout << "Grade: " << endl;
	for(int i = 0; i < cat_size; i++){
        grade[i] = 0;
		total[i] = 0;
		for(int j = 0; j < assign_size; j++){
            if(cat[i].Name == assign[j].Type){
               	grade[i] += assign[j].Points_recv;
				total[i] += assign[j].Total_points;
            }	
        }
    }

	grade_weight = 0;
    for(int i = 0; i < cat_size; i++){
		grade_calc[i] = 0;
		grade_calc[i] += (grade[i]/total[i]);
		grade_weight += (grade_calc[i]*cat[i].Weight);

		cout << left << cat[i].Num << "\t";
		cout << left << setw(15) << cat[i].Name;
		cout << fixed << showpoint << setprecision(2);
		cout << right << "Points: " << grade[i] << " / " << total[i];
		cout << "\t" << grade_calc[i]*100 << "%" << endl;
	}
	cout << right << "Total Grade: " << grade_weight*100 << "%" << endl;
}