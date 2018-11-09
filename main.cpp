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
	vector<unordered_map<int, int>> aInB;

	while (true)
	{
		if (a[i] == a[j])
		{
			++i;
			++j;
		}
	}
	//while (i < a.size() && j < b.size())
	//{
	//	choose(a, b, i, j, i, j, res, [&] ()
	//	{
	//		while (ii - i <= 0 || jj - j <= 0)
	//		{
	//			++ii;
	//			++jj;
	//			while (ii < a.size() && jj < b.size() && a[ii] == b[jj])
	//			{
	//				++ii;
	//				++jj;
	//			}
	//		}

	//		int ci = ii < a.size() ? ii : i;
	//		int cj = jj < b.size() ? jj : j;

	//		choose(a, b, ci, cj, i, j, res, [&]()
	//		{
	//			res.push_back(a[i]);
	//			++i;
	//		});
	//	});
	//}

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
