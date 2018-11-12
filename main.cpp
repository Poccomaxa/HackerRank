#include <bits/stdc++.h>

using namespace std;

void chooseFrom(const string &from, int &index, list<int> &seq, string &res)
{
	res.push_back(from[index]);
	++index;
	if (!seq.empty())
	{
		--seq.front();
		if (seq.front() == 0)
		{
			seq.pop_front();
		}
	}
}

void choose(const string &a, const string &b, char compi, char compj, int &chosi, int &chosj, list<int> &lowSeqI, list<int> &lowSeqJ, string &res, function<void()> fallback)
{
	if (compi < compj)
	{
		chooseFrom(a, chosi, lowSeqI, res);
	}
	else if (compi > compj)
	{
		chooseFrom(b, chosj, lowSeqJ, res);
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
	list<int> lowSeqI;
	list<int> lowSeqJ;

	while (i < a.size() && j < b.size())
	{
		choose(a, b, a[i], b[j], i, j, lowSeqI, lowSeqJ, res, [&]()
		{
			char ai;
			char bj;
			char prevai = a[i];
			if (!(ii > i && jj > j) || lowSeqI.size() != lowSeqJ.size())
			{
				lowSeqI.clear();
				ii = i + 1;
				jj = j + 1;
				lowSeqI.push_back(1);				
				ai = ii < a.size() ? a[ii] : b[ii - a.size()];
				bj = jj < b.size() ? b[jj] : a[jj - b.size()];
				while ((ii < a.size() || jj < b.size()) && ai == bj)
				{
					if (ai > prevai)
					{
						lowSeqI.push_back(0);
					}
					prevai = ai;
					++ii;
					++jj;
					++lowSeqI.back();

					ai = ii < a.size() ? a[ii] : b[ii - a.size()];
					bj = jj < b.size() ? b[jj] : a[jj - b.size()];
				}
				lowSeqJ = lowSeqI;
				ii = ii < a.size() ? ii : a.size() - 1;
				jj = jj < b.size() ? jj : b.size() - 1;
			}	
			else
			{
				ai = a[ii];
				bj = b[jj];
			}

			choose(a, b, ai, bj, i, j, lowSeqI, lowSeqJ, res, [&]()
			{
				chooseFrom(a, i, lowSeqI, res);
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
