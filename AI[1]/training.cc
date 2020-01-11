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
	string s1;
	string hos; 
	string msg; 
	string spamStr = "spam";
	string hamStr = "ham";
	int location1 = -1; 
	int location2 = -1; 
	int hamCount = 0; 
	int hamWordCount = 0; 
	int spamCount = 0; 
	int spamWordCount = 0;
	vector<string> hamGroup; 
	vector<string> hamWords; 
	vector<string> spamGroup; 
	vector<string> spamWords; 
	map<string, int> hamMap; 
	map<string, int> spamMap; 

//Check for file inclusion 
	if(argc > 1){
		//Opening file to read 
		fin.clear();
		fin.open(argv[1]); 
		//Taking first line available, which is v1, v2,,, (esentially garbage string)
		getline(fin, s1);

		//Reading in data until the end of the file. 
		while(getline(fin, s1)){
			//Getting the string of HAM or SPAM 
			location1 = s1.find(','); 
			hos = s1.substr(0, location1);
			//Getting the message tied with eiter HAM or SPAM
			location2 = s1.find(",,,");
			msg = s1.substr(location1 + 1, location2 - 4);
			if(hos == spamStr){
				//If message hos == spam message increase count for SPAM
				spamCount++; 
				spamGroup.push_back(msg);
			} else if(hos == hamStr){
				//If message hos == ham message increase count for HAM
				hamCount++; 
				hamGroup.push_back(msg);
			}
		}
		fin.close();

		//Using the previously created vectors, we break down the vector further to create a new vector that only includes words rather than 
		//sentence structure. 
		string word; 
		for(int i = 0; i < hamGroup.size(); i++){
				stringstream iss(hamGroup[i]);
				while(iss >> word)
					hamWords.push_back(word);
		}
		for(int i = 0; i < spamGroup.size(); i++){
				stringstream iss(spamGroup[i]);
				while(iss >> word)
					spamWords.push_back(word);
		}

		//After the breakdown of both HAM and SPAM sentence vectors, we then sort the WORD vectors in order to have an easy way to read the word vectors
		sort(hamWords.begin(), hamWords.end());
		sort(spamWords.begin(), spamWords.end());

		int tempVal; 
		string tempStr; 

		for(int i = 0; i < hamWords.size(); i++){
			tempStr = hamWords[i];
			cout << tempStr << endl; 
			tempVal = tempStr.find('"');

			if(tempVal == -1)
				continue;
			else
			tempStr.erase(tempVal, 1);
			hamGroup[i] = tempStr;
		}

		//We then place our WORD vectors into a map object in order to get a count on the number of times a unique word appears in our message set. 
		for(int i = 0; i < hamWords.size(); i++){
			if(hamMap.find(hamWords[i]) != hamMap.end()){
				++hamMap[hamWords[i]]; 
			} else {
				hamMap.insert(map<string,int>::value_type(hamWords[i], 1));
			}
			hamWordCount++;
		}
		for(int i = 0; i < spamWords.size(); i++){
			if(spamMap.find(spamWords[i]) != spamMap.end()){
				++spamMap[spamWords[i]]; 
			} else {
				spamMap.insert(map<string,int>::value_type(spamWords[i], 1));
			}
			spamWordCount++;
		}

		fout.clear();
		fout.open("SpamData.txt");

		//Printing out the map

		fout << "Spam MESSAGE count: " << spamCount << endl;
		fout << "Spam WORD count: " << spamWordCount << endl;  
		for(auto it = spamMap.cbegin(); it != spamMap.cend(); it++)
		{
			fout << it->first << " " << it->second << endl; 
		}
		fout.close();

		fout.clear();
		fout.open("HamData.txt");

		//Printing out the map
		fout << "Ham MESSAGE count: " << hamCount << endl; 
		fout << "Ham WORD count: " << hamWordCount << endl; 
		for(auto it = hamMap.cbegin(); it != hamMap.cend(); it++)
		{
			fout << it->first << " " << it->second << endl; 
		}
		fout.close();

	} else {
		//No file was found, throwing return
		cout << "No file." << endl; 
		return -1; 
	}
	return 0; 
}