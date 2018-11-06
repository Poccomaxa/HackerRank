#include <bits/stdc++.h>

using namespace std;

// Complete the steadyGene function below.
int steadyGene(string gene) {
	return 0;

}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string gene;
	getline(cin, gene);

	int result = steadyGene(gene);

	fout << result << "\n";

	fout.close();

	return 0;
}
