#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n; cin >> n;
    while(n--)
    {
        string s; cin >> s;
        string result = "";
        result += s[0];
        for(int i = 1; i < s.size(); i++)
        {
            if(s[i] != s[i-1])
                result += s[i];
        }
        cout << result << endl;
    }
    return 0;
}