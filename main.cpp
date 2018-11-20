#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void addWithMedianSave(multiset<int> &sorted, multiset<int>::iterator &medianl, multiset<int>::iterator &medianr, int value)
{
	auto fresh = sorted.insert(value);
	if (medianl == sorted.end())
	{
		medianl = fresh;
	}
	// Newly inserted is even
	else if (medianr == sorted.end())
	{
		if (value < *medianl)
		{
			medianr = medianl;
			--medianl;
		}
		else
		{
			medianr = medianl;
			++medianr;
		}
	}
	else
	{
		if (value < *medianl)
		{
			medianr = sorted.end();
		}
		else if (value >= *medianr)
		{
			medianl = medianr;
			medianr = sorted.end();
		}
		else
		{
			medianl = fresh;
			medianr = sorted.end();
		}
	}
}

void removeWithMedianSave(multiset<int> &sorted, multiset<int>::iterator &medianl, multiset<int>::iterator &medianr, int value)
{
	auto removing = sorted.find(value);
	if (medianr == sorted.end())
	{
		if (value < *medianl)
		{
			medianr = medianl;
			++medianr;
		}
		else if (value > *medianl)
		{
			medianr = medianl;
			--medianl;
		}
		else
		{
			if (medianl == removing)
			{
				medianr = medianl;
				--medianl;
				++medianr;
			}
			else
			{
				medianr = medianl;
				++medianr;
			}
		}
	}
	else
	{
		if (value <= *medianl)
		{
			medianl = medianr;
			medianr = sorted.end();
		}
		else if (value >= *medianr)
		{
			medianr = sorted.end();
		}
	}
	sorted.erase(removing);
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) 
{
	multiset<int> sorted;
	auto medianl = sorted.end();
	auto medianr = sorted.end();
	int res = 0;
	deque<int> trailing;

	for (int i = 0; i < expenditure.size(); ++i)
	{
		int value = expenditure[i];
		if (trailing.size() >= d)
		{
			int median = *medianl;
			if (medianr != sorted.end())
			{
				median += *medianr;
			}
			else
			{
				median *= 2;
			}
			if (value >= median)
			{
				++res;
			}
		}

		trailing.push_back(value);

		addWithMedianSave(sorted, medianl, medianr, value);

		while (trailing.size() > d)
		{
			removeWithMedianSave(sorted, medianl, medianr, trailing.front());
			trailing.pop_front();
		}

		if (medianl != sorted.end())
		{
			cout << *medianl << " ";
		}

		if (medianr != sorted.end())
		{
			cout << *medianr;
		}

		cout << endl;

		
	}
	
	return res;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string nd_temp;
	getline(cin, nd_temp);

	vector<string> nd = split_string(nd_temp);

	int n = stoi(nd[0]);

	int d = stoi(nd[1]);

	string expenditure_temp_temp;
	getline(cin, expenditure_temp_temp);

	vector<string> expenditure_temp = split_string(expenditure_temp_temp);

	vector<int> expenditure(n);

	for (int i = 0; i < n; i++) {
		int expenditure_item = stoi(expenditure_temp[i]);

		expenditure[i] = expenditure_item;
	}

	int result = activityNotifications(expenditure, d);

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
