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
	static int i;
	AutNode(bool aEndNode) : endNode(aEndNode)
	{		
		n = i;
		++i;
	}
	int n;
	unordered_multimap<char, shared_ptr<AutNode>> childs;
	bool endNode;
};

int AutNode::i = 0;

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
			cout << l->n << (l->endNode ? "e" : "") << ":";
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

set<AutNode *> epsilonClosure(set<AutNode *> nodes)
{
	set<AutNode *> result;
	result.insert(nodes.begin(), nodes.end());	
	set<AutNode *> newNodes(result);
	while (!newNodes.empty())
	{
		set<AutNode *> currentNodes;
		swap(newNodes, currentNodes);

		for (auto node : currentNodes)
		{
			for (auto &kv : node->childs)
			{
				if (kv.first == '\0' && !result.count(kv.second.get()))
				{
					result.insert(kv.second.get());
					newNodes.insert(kv.second.get());
				}
			}
		}
	}
	return result;
}

set<AutNode *> moveTo(set<AutNode *> nodes, char c)
{
	set<AutNode *> res;

	for (auto node : nodes)
	{
		for (auto &kv : node->childs)
		{
			if (kv.first == c)
			{
				res.insert(kv.second.get());
			}
		}
	}

	return res;
}

shared_ptr<AutNode> convertToDetAut(AutNode *node, vector<int> &endNodes)
{	
	map<set<AutNode *>, shared_ptr<AutNode>> allNodes;
	map<set<AutNode *>, shared_ptr<AutNode>> unprocessedNodes;
	map<set<AutNode *>, shared_ptr<AutNode>> processedNodes;
	
	auto closure = epsilonClosure(std::set<AutNode *>({ node }));
	auto it = find_if(closure.begin(), closure.end(), [](AutNode *nod)
	{
		return nod->endNode == true;
	});
	auto root = make_shared<AutNode>(it != closure.end());
	if (root->endNode)
	{
		endNodes.push_back(root->n);
	}
	unprocessedNodes.insert(make_pair(closure, root));
	
	allNodes = unprocessedNodes;
	while (!unprocessedNodes.empty())
	{
		map<set<AutNode *>, shared_ptr<AutNode>> newNodes;
		for (auto &kv : unprocessedNodes)
		{
			for (char c : vector<char>({ 'a', 'b' }))
			{
				auto closure = epsilonClosure(moveTo(kv.first, c));
				if (!closure.empty())
				{
					auto findIt = allNodes.find(closure);
					if (findIt == allNodes.end())
					{
						auto it = find_if(closure.begin(), closure.end(), [](AutNode *nod) 
						{
							return nod->endNode == true;
						});
						auto newNode = make_shared<AutNode>(it != closure.end());
						if (newNode->endNode)
						{
							endNodes.push_back(newNode->n);
						}
						findIt = newNodes.insert(make_pair(closure, newNode)).first;
						allNodes.insert(*findIt);
					}

					kv.second->childs.insert(make_pair(c, findIt->second));
				}
			}
		}

		processedNodes.insert(unprocessedNodes.begin(), unprocessedNodes.end());
		unprocessedNodes = newNodes;
	}
	return root;
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

shared_ptr<AutNode> buildNonDetAut(Regular *node, bool endNode)
{
	switch (node->op)
	{
	case Operation::CHARACTER:
	{
		shared_ptr<AutNode> autNode = make_shared<AutNode>(false);
		autNode->childs.insert(make_pair(node->c, make_shared<AutNode>(endNode)));
		return autNode;
	}
	case Operation::UNION:
	{
		auto left = buildNonDetAut(node->lNode.get(), endNode);
		auto right = buildNonDetAut(node->rNode.get(), endNode);
		left->childs.insert(make_pair('\0', right));
		return left;
	}
	case Operation::CONCATENATION:
	{
		auto left = buildNonDetAut(node->lNode.get(), false);
		auto right = buildNonDetAut(node->rNode.get(), endNode);
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
		auto left = buildNonDetAut(node->lNode.get(), endNode);
		vector<AutNode *> leaves;
		unordered_set<AutNode *> processed;
		findAllLeaves(left.get(), leaves, processed);
		left->endNode = endNode;
		for (auto &leave : leaves)
		{
			leave->childs.insert(make_pair('\0', left));
			leave->childs.insert(make_pair('\0', make_shared<AutNode>(endNode)));
			left->childs.insert(make_pair('\0', leave));
		}
		return left;
	}
	default:
		cout << "Unknown regular exp node" << endl;
		break;
	}
	return shared_ptr<AutNode>(nullptr);
}

void formTraverseMatrix(AutNode *node, vector<vector<int>> &res)
{
	unordered_set<AutNode *> processedNodes;
	unordered_set<AutNode *> newNodes({ node });
	while (!newNodes.empty())
	{
		unordered_set<AutNode *> curNodes;
		swap(curNodes, newNodes);
		for (auto &node : curNodes)
		{
			if (!processedNodes.count(node))
			{
				processedNodes.insert(node);
				for (auto &kv : node->childs)
				{				
					++res[node->n][kv.second->n];

					newNodes.insert(kv.second.get());				
				}
			}
		}
	}	
}

void multiplyMatrix(const vector<vector<int>> &l, const vector<vector<int>> &r, vector<vector<int>> &res)
{
	for (int i = 0; i < l.size(); ++i)
	{
		for (int j = 0; j < l[i].size(); ++j)
		{
			res[i][j] = 0;
			for (int k = 0; k < r[i].size(); ++k)
			{
				res[i][j] += l[i][k] * r[k][j];
			}
		}
	}
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
				opStack.push_back(Operation::CONCATENATION);
				break;
			case ')':
			{
				auto last = stack.back(); stack.pop_back();
				auto prev = stack.back(); stack.pop_back();
				Operation op = opStack.back(); opStack.pop_back();
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
				opStack.back() = Operation::UNION;
				break;
			case '*':
				opStack.back() = Operation::WILDCARD;
				break;
			default:
				cout << "Unknown character!" << endl;
				break;
			}
		}		
	}

	root = stack.front();
	AutNode::i = 0;
	auto nonDetAut = buildNonDetAut(root.get(), true);
	outAut(nonDetAut.get());
	cout << endl;
	AutNode::i = 0;
	vector<int> endNodes;
	auto detAut = convertToDetAut(nonDetAut.get(), endNodes);
	outAut(detAut.get());

	vector<vector<int>> traverseMatrix(AutNode::i);
	for (auto &v : traverseMatrix)
	{
		v.resize(AutNode::i);
	}	

	formTraverseMatrix(detAut.get(), traverseMatrix);

	auto res = traverseMatrix;
	for (int i = 1; i < l; ++i)
	{
		auto cur = res;
		multiplyMatrix(cur, traverseMatrix, res);
	}

	int result = 0;
	for (int good : endNodes)
	{
		result += res[0][good];
	}

	cout << endl;
	for (auto &v : res)
	{
		for (auto i : v)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	return result;
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
