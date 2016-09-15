#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> arr, ans;
	int start_time = clock();
	ifstream html_file;
	ofstream out_file;
	string str_tmp;

	if (argc > 1) {
		html_file.open(argv[1]);
		if (!html_file.is_open()) {
			cout << "HTML file can not be opened." << endl;
			return -1;
		}
	}

	else {
		cout << "Enter HTML file, please." << endl;
		system("pause");
		return -2;
	}

	out_file.open("out_openmp.txt", ios::trunc);

	while (!html_file.eof()) {
		getline(html_file, str_tmp);
		arr.push_back(str_tmp);
	}

	omp_set_num_threads(2);

	#pragma omp parallel for
				for (int k = 0; k < arr.size(); ++k) {
				string text = "";
				char ch = '\0';
				bool b = true;
				for (unsigned int i = 0; i < arr[k].length(); i++) {
					ch = arr[k][i];
					if (ch == '<') b = false;
					if (ch == '>') {
						b = true;
						continue;
					}
					if (b) text += ch;
				}
				arr[k] = text; 
				cout << arr[k] << endl;
			}
	
	for (int i = 0; i < ans.size(); i++)
		out_file << arr[i] << endl;

	html_file.close();
	out_file.close();

	int algorithm_end_time = clock();
	cout << "Algorithm completed in: " << (algorithm_end_time - start_time) / 1000.0 << " seconds." << endl;

	return 0;
}