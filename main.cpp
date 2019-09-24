#include <bits/stdc++.h>
#include <functional>

using namespace std;

template<typename T>
class GridMap
{
public:
	GridMap(vector<vector<T>> &aMap)
	{
		size.first = aMap.size();
		size.second = aMap.empty() ? 0 : aMap.front().size();
		map.resize(size.first * size.second);
		auto mapIt = map.begin();
		for (auto vectorIt = aMap.begin(); vectorIt != aMap.end(); ++vectorIt)
		{
			mapIt = copy(vectorIt->begin(), vectorIt->end(), mapIt);
		}
	}

	GridMap(const pair<size_t, size_t> &aSize, T value) : size(aSize)
	{
		map.assign(aSize.first * aSize.second, value);
	}

	void ForEach(std::function<void(std::pair<size_t, size_t> index, T value)> lambda)
	{
		for (size_t i = 0; i < size.first; ++i)
		{
			for (size_t j = 0; j < size.second; ++j)
			{
				lambda({ i, j }, map[i * size.second + j]);
			}
		}
	}

	T Get(std::pair<size_t, size_t> index)
	{
		return map[index.first * size.second + index.second];
	}

	auto operator[](const std::pair<size_t, size_t> &index)
	{
		return map[index.first * size.second + index.second];
	}

	const auto operator[](const std::pair<size_t, size_t> &index) const
	{
		return map[index.first * size.second + index.second];
	}

	bool InRange(std::pair<size_t, size_t> index) const 
	{
		return index.first < size.first && index.second < size.second;
	}

	pair<size_t, size_t> GetSize() { return size; }
private:
	vector<T> map;

	pair<size_t, size_t> size;
};

pair<size_t, size_t> operator+(const pair<size_t, size_t> &l, const pair<int, int> &r)
{
	return { l.first + r.first, l.second + r.second };
}

template<typename T>
set<pair<size_t, size_t>> traverseConnectedArea(const GridMap<T> &map, const std::pair<size_t, size_t> &startingPos, vector<pair<int, int>> pattern, std::function<bool(T)> suitable)
{
	set<pair<size_t, size_t>> connectedPoints;
	vector<pair<size_t, size_t>> processingPoints{ startingPos };
	while (!processingPoints.empty())
	{
		vector<pair<size_t, size_t>> newProcessingPoints;
		for (const auto &point : processingPoints)
		{
			connectedPoints.insert(point);
			for (const auto &dir : pattern)
			{
				const auto &newPoint = point + dir;
				if (map.InRange(newPoint) && !connectedPoints.count(newPoint) && suitable(map[newPoint]))
				{
					newProcessingPoints.push_back(newPoint);
				}
			}
		}
		processingPoints = newProcessingPoints;
	}
	return connectedPoints;
}

// Complete the connectedCell function below.
int connectedCell(vector<vector<int>> matrix) {
	GridMap<int> map(matrix);
	GridMap<bool> checked(map.GetSize(), false);
	size_t maxIslandSize = numeric_limits<size_t>::min();
	const vector<pair<int, int>> pattern{ {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1} };
	//const vector<pair<int, int>> pattern{ { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };

	map.ForEach([&](std::pair<size_t, size_t> index, int value)
	{
		if (!checked.Get(index) && value == 1)
		{
			const auto &island = traverseConnectedArea<int>(map, index, pattern, [](int value) { return value == 1; });
			maxIslandSize = max(island.size(), maxIslandSize);
			for (const auto &checkedCells : island)
			{
				checked[checkedCells] = true;
			}
		}
		else if (!checked.Get(index) && value == 0)
		{
			checked[index] = true;
		}
	});

	return maxIslandSize;
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
