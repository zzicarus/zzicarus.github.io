#include <iostream>

#include <string>
using namespace std;

std::string to_camel_case(std::string text)
{
    int flag_count = 0;
    string result;
    for (auto single : text)
    {
        if (single == '_' || single == '-')
            flag_count = 1;
        if (flag_count == 1)
        {
            if (isalpha(single))
            {
                result.push_back(toupper(single));
                flag_count = 0;
            }
        }
        else
        {
            result.push_back(single);
        }
    }
    return result;
}
int main()
{
    cout << to_camel_case("The_Formal_language");
}