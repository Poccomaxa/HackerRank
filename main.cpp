#include <bits/stdc++.h>
#include <functional>

using namespace std;

template<typename T>
class GridMap
{
public:
	GridMap(vector<vector<T>> &aMap) : map(aMap) {}

	void forEach(std::function<void(typename vector<vector<T>>::iterator, typename vector<T>::iterator)> pred)
	{
		for (auto cit = map.begin(); cit != map.end(); ++cit)
		{
			for (auto it = cit->begin(); it != cit->end(); ++it)
			{
				pred(cit, it);
			}
		}
	}



private:
	vector<vector<T>> map;
};

// Complete the connectedCell function below.
int connectedCell(vector<vector<int>> matrix) {
	GridMap<int> map(matrix);

	map.forEach([](auto cit, auto it)
	{

	});

	return 0;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int m;
	cin >> m;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<vector<int>> matrix(n);
	for (int i = 0; i < n; i++) {
		matrix[i].resize(m);

		for (int j = 0; j < m; j++) {
			cin >> matrix[i][j];
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	int result = connectedCell(matrix);

	fout << result << "\n";

	fout.close();

	return 0;
}
