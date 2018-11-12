#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

enum class Operation : int
{
	UNKNOWN,
	CHARACTER,
	CONCATENATION,
	UNION,
	WILDCARD
};

struct Regular
{
	Regular(char aC, Operation aOp) : c(aC), op(aOp) {}
	char c;
	Operation op;

	shared_ptr<Regular> lNode;
	shared_ptr<Regular> rNode;
};

int countStrings(string r, int l) {
	shared_ptr<Regular> root;
	vector<shared_ptr<Regular>> stack;
	vector<Operation> opStack;
	for (char c : r)
	{
		if (isalpha(c))
		{
			stack.push_back(make_shared<Regular>(c, Operation::CHARACTER));
		}
		else
		{
			switch (c)
			{
			case '(':
				stack.push_back(make_shared<Regular>('\0', Operation::UNKNOWN));
				break;
			case ')':
			{
				auto last = stack.back(); stack.pop_back();
				auto prev = stack.back(); stack.pop_back();
				Operation op;
				if (opStack.empty())
				{
					op = Operation::CONCATENATION;
				}
				else
				{
					op = opStack.back(); opStack.pop_back();
				}
				if (op == Operation::WILDCARD)
				{
					prev->op = op;
					last->lNode = prev;
					stack.push_back(prev);
				} 
				else if (prev->op != Operation::UNKNOWN)
				{
					auto node = stack.back(); stack.pop_back();
					node->op = op;
					node->lNode = last;
					node->rNode = prev;
					stack.push_back(node);
				}
				else
				{
					stack.push_back(last);
				}
				break;
			}
			case '|':
				opStack.push_back(Operation::UNION);
				break;
			case '*':
				opStack.push_back(Operation::WILDCARD);
				break;
			default:
				break;
			}
		}		
	}

	root = stack.front();
	return 0;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int t;
	cin >> t;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string rl_temp;
		getline(cin, rl_temp);

		vector<string> rl = split_string(rl_temp);

		string r = rl[0];

		int l = stoi(rl[1]);

		int result = countStrings(r, l);

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
