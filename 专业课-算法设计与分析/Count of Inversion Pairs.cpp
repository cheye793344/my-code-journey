#include <iostream>
#include <vector>

using namespace std;

void Counter() {
	int n;
	cin >> n; 
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                count++;
            }
        }
    }
    cout << count;
}

int main() {
    Counter();
    return 0;
}

