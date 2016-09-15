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
	vector<string> arr;
	vector<string> ans[2];
	int start_time = clock();
	ifstream html_file;
	ofstream out_file;
	string str_tmp;

	/*
	#pragma omp parallel num_threads(4)
	{
		cout << omp_get_num_threads() << endl;
	}
	*/

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

	#pragma omp parallel for num_threads(2)
	for (int k = 0; k < arr.size(); k++) {
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
		if (omp_get_thread_num() == 0) {
			ans[0].push_back(text);
			//cout << "1" << endl;
		}
		else {
			ans[1].push_back(text);
			//cout << "2" << endl;
		}
	}
	
	for (int i = 0; i < ans[0].size(); i++)
		out_file << ans[0][i] << endl;

	for (int i = 0; i < ans[1].size(); i++)
		out_file << ans[1][i] << endl;
	
	html_file.close();
	out_file.close();

	int algorithm_end_time = clock();
	cout << "Algorithm completed in: " << (algorithm_end_time - start_time) / 1000.0 << " seconds." << endl;

	return 0;
}