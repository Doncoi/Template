#include <iostream>
#include <stack>
#define MAXN 100 + 5
using namespace std;
 
bool isLeft(char c)
{
    return (c == '(' || c == '[' || c == '{');
}
 
bool isMatch(char right, char left)
{
    if (right == ')')
    {
        return (left == '(');
    }
 
    if (right == ']')
    {
        return (left == '[');
    }
 
    if (right == '}')
    {
        return (left == '{');
    }

    return false;
}
 
bool matching(char* s)
{
    stack<char> cs;
    char c;
    while (*s)
    {
        c = *s;
        if (isLeft(c))
        {
            cs.push(c);
        }
        else
        {
            if (cs.empty() || !isMatch(c, cs.top()))
            {
                return false;
            }
 
            cs.pop();
        }
        ++s;
    }
 
    if (!cs.empty())
    {
        return false;
    }
    return true;
}


int main()
{
    char s[MAXN];
    cin >> s;

    if (matching(s))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
 
    return 0;
}