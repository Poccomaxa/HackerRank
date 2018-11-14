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

struct AutNode
{
	AutNode()
	{
		static int i = 0;
		n = i;
		++i;
	}

	int n;
	unordered_multimap<char, shared_ptr<AutNode>> childs;
};

void outAut(AutNode *autNode)
{
	unordered_set<AutNode *> processed;

	vector<AutNode *> layer(1, autNode);
	vector<AutNode *> nextLayer;
	while (!layer.empty())
	{
		nextLayer.clear();
		for (auto l : layer)
		{			
			cout << l->n;
			for (auto &kv : l->childs)
			{
				if (kv.first == '\0')
				{
					cout << "#";
				}
				else
				{
					cout << kv.first;
				}
				cout << "->" << kv.second->n;
				if (!processed.count(kv.second.get()))
				{
					nextLayer.push_back(kv.second.get());
					processed.insert(kv.second.get());
				}
			}
			cout << endl;			
		}
		layer = nextLayer;
	}
}

void findAllLeaves(AutNode *autNode, vector<AutNode *> &leaves, unordered_set<AutNode *> &processed)
{
	if (processed.count(autNode))
	{
		return;
	}
	else
	{
		processed.insert(autNode);
	}	
	if (autNode->childs.empty())
	{
		leaves.push_back(autNode);
	}
	else
	{
		for (auto &kv : autNode->childs)
		{
			findAllLeaves(kv.second.get(), leaves, processed);
		}
	}
}

shared_ptr<AutNode> buildNonDetAut(Regular *node)
{
	switch (node->op)
	{
	case Operation::CHARACTER:
	{
		shared_ptr<AutNode> autNode = make_shared<AutNode>();
		autNode->childs.insert(make_pair(node->c, make_shared<AutNode>()));
		return autNode;
	}
	case Operation::UNION:
	{
		auto left = buildNonDetAut(node->lNode.get());
		auto right = buildNonDetAut(node->rNode.get());
		left->childs.insert(make_pair('\0', right));
		return left;
	}
	case Operation::CONCATENATION:
	{
		auto left = buildNonDetAut(node->lNode.get());
		auto right = buildNonDetAut(node->rNode.get());
		vector<AutNode *> leaves;
		unordered_set<AutNode *> processed;
		findAllLeaves(left.get(), leaves, processed);
		for (auto &leave : leaves)
		{
			leave->childs.insert(make_pair('\0', right));
		}
		return left;
	}
	case Operation::WILDCARD:
	{
		auto left = buildNonDetAut(node->lNode.get());
		vector<AutNode *> leaves;
		unordered_set<AutNode *> processed;
		findAllLeaves(left.get(), leaves, processed);
		for (auto &leave : leaves)
		{
			leave->childs.insert(make_pair('\0', left));
			leave->childs.insert(make_pair('\0', make_shared<AutNode>()));
		}
		return left;
	}
	default:
		cout << "Unknown regular exp node" << endl;
		break;
	}
	return shared_ptr<AutNode>(nullptr);
}

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
					prev->lNode = last;
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
				cout << "Unknown character!" << endl;
				break;
			}
		}		
	}

	root = stack.front();
	auto nonDetAut = buildNonDetAut(root.get());
	outAut(nonDetAut.get());
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
