#include <bits/stdc++.h>
#include <functional>
#include <numeric>

using namespace std;

vector<string> split_string(string);
vector<pair<int, int>> moveDirs{ { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

bool checkCell(const vector<string> &matrix, const pair<int, int> pos, function<bool(char)> predicate)
{
	if (pos.first < 0 || pos.first >= matrix.size())
	{
		return false;
	}
	if (pos.second < 0 || pos.second >= matrix[pos.first].size())
	{
		return false;
	}
	return predicate(matrix[pos.first][pos.second]);
}

vector<pair<int, int>> countWays(const vector<string> &matrix, const pair<int, int> &pos)
{
	vector<pair<int, int>> res;
	return accumulate(moveDirs.cbegin(), moveDirs.cend(), res,
		[&matrix, &pos](vector<pair<int, int>> &value, const pair<int, int> &dir)
	{
		pair<int, int> nextCell = { pos.first + dir.first, pos.second + dir.second };
		if (checkCell(matrix, nextCell,
			[](char c) { return c == '.' || c == '*'; }))
		{
			value.push_back(nextCell);
		}
		return value;
	});
}
// Complete the countLuck function below.
string countLuck(vector<string> matrix, int k)
{
	vector<vector<int>> junctionsCount(matrix.size(), vector<int>(matrix.front().size(), 0));
	pair<int, int> startingPosition;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == 'M')
			{
				startingPosition = { i, j };
				goto foundPos;
			}
		}
	}
	foundPos:
	set<pair<int, int>> pointsToProcess{ startingPosition };
	while (!pointsToProcess.empty())
	{
		decltype(pointsToProcess) newPoints;
		for (const auto &pos : pointsToProcess)
		{
			int currentJunctions = junctionsCount[pos.first][pos.second];
			if (matrix[pos.first][pos.second] == '*')
			{
				return currentJunctions == k ? "Impressed" : "Oops!";
			}

			const auto &ways = countWays(matrix, pos);
			int newJunctions = ways.size() > 1;
			newPoints.insert(ways.begin(), ways.end());
			for (const auto &way : ways)
			{
				junctionsCount[way.first][way.second] = currentJunctions + newJunctions;
				matrix[way.first][way.second] = matrix[way.first][way.second] == '*' ? '*' : 'X';
			}
		}

		pointsToProcess = newPoints;
	}

	return "";
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string nm_temp;
		getline(cin, nm_temp);

		vector<string> nm = split_string(nm_temp);

		int n = stoi(nm[0]);

		int m = stoi(nm[1]);

		vector<string> matrix(n);

		for (int i = 0; i < n; i++) {
			string matrix_item;
			getline(cin, matrix_item);

			matrix[i] = matrix_item;
		}

		int k;
		cin >> k;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		string result = countLuck(matrix, k);

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
