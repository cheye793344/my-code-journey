#include <iostream>
using namespace std;

bool isPrime(int n) {
	if (n < 2) return false;
	for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
	}
	return true;
}

int main() {
	int n; cin >> n;
	while (n--) {
		int a; cin >> a;
		if (isPrime(a)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}