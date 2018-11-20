#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct TreeNode
{
	TreeNode(int aValue) : value(aValue) {}
	int value;
	int count = 1;
	int greaterChildCount = 0;
	TreeNode *l = nullptr;
	TreeNode *r = nullptr;

	~TreeNode()
	{
		if (l)
		{
			delete l;
			l = nullptr;
		}

		if (r)
		{
			delete r;
			r = nullptr;
		}
	}
};
// Complete the insertionSort function below.
long long insertionSort(vector<int> arr) {
	long long res = 0;
	TreeNode *root = new TreeNode(arr.front());

	for (auto it = arr.begin() + 1; it != arr.end(); ++it)
	{
		TreeNode **curNode = &root;
		while (*curNode != nullptr)
		{
			if (*it < (*curNode)->value)
			{
				res += (*curNode)->count + (*curNode)->greaterChildCount;
				curNode = &(*curNode)->l;				
			}
			else if (*it > (*curNode)->value)
			{
				++(*curNode)->greaterChildCount;
				curNode = &(*curNode)->r;
			}
			else
			{
				res += (*curNode)->greaterChildCount;
				++(*curNode)->count;
				break;
			}
		}

		if (*curNode == nullptr)
		{
			*curNode = new TreeNode(*it);
		}
	}
	delete root;
	return res;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
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

		long long result = insertionSort(arr);

		fout << result << "\n";
	}

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
