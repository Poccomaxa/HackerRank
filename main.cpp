#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the lilysHomework function below.
int lilysHomework(vector<int> arr) 
{
	vector<int> indeces(arr.size());
	iota(indeces.begin(), indeces.end(), 0);
	sort(indeces.begin(), indeces.end(), [&arr](int l, int r)
	{
		return arr[l] < arr[r];
	});
	
	int swapsForward = 0;
	int swapsBackward = 0;	
	vector<int> indecesReversed;
	copy(indeces.rbegin(), indeces.rend(), back_inserter(indecesReversed));
	for (int i = 0; i < indeces.size();)
	{		
		swapsForward += i != indeces[i];
		if (i != indeces[i])
		{
			swap(indeces[i], indeces[indeces[i]]);
		}
		else
		{
			++i;
		}
	}
	
	for (int i = 0; i < indecesReversed.size();)
	{
		swapsBackward += i != indecesReversed[i];
		if (i != indecesReversed[i])
		{
			swap(indecesReversed[i], indecesReversed[indecesReversed[i]]);
		}
		else
		{
			++i;
		}
	}

	int swaps = min(swapsForward, swapsBackward);

	return swaps;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string arr_temp_temp;
	getline(cin, arr_temp_temp);

	vector<string> arr_temp = split_string(arr_temp_temp);

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item = stoi(arr_temp[i]);

		arr[i] = arr_item;
	}

	int result = lilysHomework(arr);

	fout << result << "\n";

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y && x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
