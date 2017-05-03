
#include <iostream>
#include <fstream>


using namespace std;


int main(int args, char * argv[])
{
ofstream MyExcelFile;
MyExcelFile.open("C:\\con_inrush.csv");

MyExcelFile << "First Name, Last Name, Middle Initial" << endl;
MyExcelFile << "Michael, Jackson, B." << endl;
MyExcelFile.close();
return 0;
} 

