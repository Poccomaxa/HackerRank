#include <bits/stdc++.h>

using namespace std;

// Complete the morganAndString function below.
string morganAndString(string a, string b) {
	string res;
	int i = 0;
	int j = 0;
	while (i < a.size() && j < b.size())
	{
		if (a[i] < b[j])
		{
			res.push_back(a[i]);
			++i;
		}
		else if (a[i] > b[j])
		{
			res.push_back(b[j]);
			++j;
		}
		else
		{
			int ii = i + 1;
			int jj = j + 1;
			while (ii < a.size() && jj < b.size() && a[ii] == b[jj])
			{
				++ii;
				++jj;
			}

			if (ii < a.size() && jj < b.size())
			{
				if (a[ii] < b[jj])
				{
					res.push_back(a[i]);
					++i;
				}
				else
				{
					res.push_back(b[j]);
					++j;
				}
			}
			else if (ii < a.size())
			{
				if (a[ii] < b[j])
				{
					res.push_back(a[i]);
					++i;
				}
				else
				{
					res.push_back(b[j]);
					++j;
				}
			}
			else if (jj < b.size())
			{
				if (b[jj] < a[i])
				{
					res.push_back(b[j]);
					++j;
				}
				else
				{
					res.push_back(a[i]);
					++i;
				}
			}
			else
			{
				res.push_back(a[i]);
				++i;
			}
		}
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
