#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <list>
#include <forward_list>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

struct PersonInfo
{
    string name;
    vector<string> Phones;
};

void PrintVector(vector<int> a)
{
    for (auto single : a)
    {
        cout << " " << single;
    }
    cout << endl;
}
int main()
{
    int aaSSD_dawj = 5;
    string asd;
    int count = 4;
    vector<int> a({0, 1, 2, 3, 4, 5, 6, 7});

    vector<vector<int>> D = {{0, 1, 2}, {3, 4, 5, 6}};
    cout << D[0][0];
}

class Solution
{
public:
    vector<string> fizzBuzz(int n)
    {
        vector<string> ans;
        for (size_t i = 1; i <= n; i++)
        {
            if (i % 3 == 0 && i % 5 == 0)
                ans.push_back("FizzBuzz");
            else
            {
                if (i % 3 == 0)
                    ans.push_back("Fizz");
                else if (i % 5 == 0)
                    ans.push_back("Buzz");
                else
                    ans.push_back(to_string(i));
            }
        }
        return ans;
    }
};