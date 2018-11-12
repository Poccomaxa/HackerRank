#include <bits/stdc++.h>

using namespace std;

void choose(const string &a, const string &b, int compi, int compj, int &chosi, int &chosj, string &res, function<void()> fallback)
{
	if (a[compi] < b[compj])
	{
		res.push_back(a[chosi]);
		++chosi;
	}
	else if (a[compi] > b[compj])
	{
		res.push_back(b[chosj]);
		++chosj;
	}
	else
	{
		fallback();
	}
}

// Complete the morganAndString function below.
string morganAndString(string a, string b) {
	string res;
	int i = 0;
	int j = 0;
	int ii = i;
	int jj = j;
	vector<pair<int, int>> nextLowerI;
	vector<pair<int, int>> nextLowerJ;
	
	while (i < a.size() && j < b.size())
	{
		choose(a, b, i, j, i, j, res, [&]()
		{
			if (ii > i && jj > j)
			{

			}
			else
			{
				nextLowerI.clear();
				nextLowerJ.clear();
				ii = i + 1;
				jj = j + 1;
				while (ii < a.size() && jj < b.size() && a[ii] == b[jj])
				{
					if (a[ii] < a[i])
					{
						if (!nextLowerI.empty() && !nextLowerJ.empty())
						{
							nextLowerI.back().second = ii;
							nextLowerJ.back().second = jj;
						}
						nextLowerI.push_back(make_pair(ii, ii));
						nextLowerJ.push_back(make_pair(jj, jj));
					}
					++ii;
					++jj;
				}
			}

			int moreThanFront = 0;
			if (i > nextLowerI.front().first)
			{

			}

			int ci = ii < a.size() ? ii : i;
			int cj = jj < b.size() ? jj : j;

			choose(a, b, ci, cj, i, j, res, [&]()
			{
				res.push_back(a[i]);
				++i;
			});
		});
	}

	return res + a.substr(i, a.size()) + b.substr(j, b.size());
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string a;
		getline(cin, a);

		string b;
		getline(cin, b);

		string result = morganAndString(a, b);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}
