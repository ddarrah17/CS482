#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std; 

int main(int argc, char* argv[])
{
	ifstream fin; 
	ofstream fout; 
	string testFile; 
	string hamFile; 
	string spamFile; 
	string outputPred; 
	string str; 
	string msg; 
	vector<string> testGroup; 
	int location = -1; 


	if(argc == 5){
		testFile = argv[1];
		spamFile = argv[2];
		hamFile = argv[3];
		outputPred = argv[4];
		
		fin.clear();
		fin.open(testFile);
		if(fin.good()){
			while(getline(fin, str)){
				location = str.find(",,,");
				msg = str.substr(0, location - 4);
				testGroup.push_back(msg);
			}
			for(int i = 0; i < testGroup.size(); i++){
				cout << testGroup[i] << endl << endl; 
			}
		} else {
			cout << "The testfile that was entered was not found." << endl; 
		}


	} else {
		cout << "Missing input files." << endl; 
		cout << "Takes arguements <testfile> <spamfile> <hamfile>" << endl;
	}

	return 0;
}