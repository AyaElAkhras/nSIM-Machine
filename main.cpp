#include <iostream>
#include <thread>
#include <vector>

#include "SIMProcessor.h"
#define N 6   // This represents the number of concurrent programs, specified by the user
using namespace std;

int main()
{
	string file_names[] = {"test0.txt", "test1.txt", "test2.txt" , "test3.txt", "test4.txt", "test5.txt"};   // Array of all assembly files names
	int number_of_files = 6;   // The user should place here the number of files he/she is passing in the array file_names

	int index_of_data_mem = 10; // This controls the number of elements to print from the DataMemory 

	try {
		SIMProcessor my_sim_processor(N, file_names, number_of_files);
		my_sim_processor.exec();
		cout << endl;
		my_sim_processor.printDataMem(index_of_data_mem);

	}
	catch (std::exception except) {
		cout << "Exception Occured! " << except.what() << endl;
	}
	system("pause");
	return 0;
}



