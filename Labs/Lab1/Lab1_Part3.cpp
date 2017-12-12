#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
	float balance = 0;
	queue<float> transactions;

	transactions.push(15.01f);
	transactions.push(32.15f);
	transactions.push(-1.23f);
	transactions.push(44.99f);
	transactions.push(-56.54f);

	while (!transactions.empty()) {
		cout << transactions.front() << " pushed to account" << endl;
		balance += transactions.front();
		transactions.pop();
	}

	cout << endl << "Final Balance = $" << balance << endl;

	return 0;
}