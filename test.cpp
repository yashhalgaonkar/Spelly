#include<iostream>
using namespace std;

int main()
{
    int m = 19937;

    

    string s;
    cout << "Enter a word: " ;
    cin >> s;

    for(int i = 0; i < s.length(); i++)
    {
        int a = m << 6; //left shift
        int b = m >> 26; // right shift

        cout << a << " " << b << endl;
        m = a ^ b ^ s[i];
        cout << m << endl;
    }
}