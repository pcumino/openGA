#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]){
	int numberOfNodes = 0;
	if (argc > 1)
		numberOfNodes = atoi(argv[1]);
	else
		numberOfNodes = 5;

	double pos_x, pos_y, max_x = 40, max_y = 40;
	srand( (unsigned)time( NULL ) );

	ofstream output_file;
	string filename = "./ground-nodes-" + to_string(numberOfNodes) + ".txt";
	output_file.open(filename);

	output_file<< "node_id" << "\t"
		<< "pos_x" << "\t"
		<< "pos_y" << endl;


	for( int i = 1; i <= numberOfNodes; i++ ) {
		pos_x = (((double)rand() / RAND_MAX) * max_x);
		pos_y = (((double)rand() / RAND_MAX) * max_y);

		cout << i << "\t"
			<< pos_x << "\t"
			<< pos_y << endl;

		output_file<< i << "\t"
			<< pos_x << "\t"
			<< pos_y << endl;

		if(pos_x >= 200){
			cout << "ERROR!" << endl;
			break;
		}
	}

	output_file.close();

	return 0;
}