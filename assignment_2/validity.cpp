#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct split_result
{
    bool valid;
    vector<string> parts;
};

split_result *split(string s, char delimiter)
{
    if (s.length() > 1)
    {
        s = s.substr(1, s.size() - 2);
    }

    size_t i = 0;
    if (s[i] != '~')
    {
        int counter = 0;
        do
        {
            if (s[i] == '(')
            {
                counter -= 1;
            }
            else if (s[i] == ')')
            {
                counter += 1;
            }
            i += 1;
        } while (counter < 0);
        char root = s[i];
    }

    if (root != delimiter)
    {
        return new split_result{false, {}};
    }
    string left = s.substr(0, i);
    string right = s.substr(i + 1, s.size() - i - 1);
    return new split_result{true, {left, right}};
}

bool and_intro_checker(string l1, string l2, string r)
{
    return "(" + l1 + "*" + l2 + ")" == r;
}

bool and_elim_checker(string l, string r, int n = 1)
{
    split_result *sr = split(l, '*');
    if (!sr->valid)
    {
        return false;
    }
    string result = sr->parts[n - 1];
    return result == r;
}

bool or_intro_checker(string l, string r, int n = 1)
{
    split_result *sr = split(r, '+');
    if (!sr->valid)
    {
        return false;
    }
    string result = sr->parts[n - 1];
    return result == l;
}

bool implies_elim_checker(string l1, string l2, string r)
{
    split_result *sr = split(l1, '>');
    if (!sr->valid)
    {
        return false;
    }
    if (sr->parts[0] != l2)
    {
        return false;
    }
    return sr->parts[1] == r;
}

string make_negation(string s)
{
    if (s.length() == 1)
    {
        s = "~" + s;
    }
    else
    {
        s = "~(" + s + ")";
    }
    return s;
}

bool mt_checker(string l1, string l2, string r)
{
    split_result *sr = split(l1, '>');
    if (!sr->valid)
    {
        return false;
    }

    if (make_negation(sr->parts[1]) != l2)
    {
        return false;
    }
    return make_negation(sr->parts[0]) == r;
}

int main()
{
    int n;
    cin >> n;
    vector<string> lines;
    vector<string> values;
    bool valid = true;
    for (int i = 0; (i < n) && valid; i++)
    {
        string line;
        cin >> line;
        vector<string> parts;
        size_t pos = 0;
        string token;
        while ((pos = line.find('/')) != string::npos)
        {
            token = line.substr(0, pos);
            parts.push_back(token);
            line.erase(0, pos + 1);
        }
        parts.push_back(line);
        values.push_back(parts[0]);
        if (parts[1] == "P")
        {
            continue;
        }
        else if (parts[1] == "*i")
        {
            valid = and_intro_checker(values[stoi(parts[2]) - 1], values[stoi(parts[3]) - 1], values[i]);
        }
        else if (parts[1] == "*e1")
        {
            valid = and_elim_checker(values[stoi(parts[2]) - 1], values[i], 1);
        }
        else if (parts[1] == "*e2")
        {
            valid = and_elim_checker(values[stoi(parts[2]) - 1], values[i], 2);
        }
        else if (parts[1] == "+i1")
        {
            valid = or_intro_checker(values[stoi(parts[2]) - 1], values[i], 1);
        }
        else if (parts[1] == "+i2")
        {
            valid = or_intro_checker(values[stoi(parts[2]) - 1], values[i], 2);
        }
        else if (parts[1] == ">e")
        {
            valid = implies_elim_checker(values[stoi(parts[2]) - 1], values[stoi(parts[3]) - 1], values[i]);
        }
        else if (parts[1] == "MT")
        {
            valid = mt_checker(values[stoi(parts[2]) - 1], values[stoi(parts[3]) - 1], values[i]);
        }
        else
        {
            valid = false;
        }
    }
    if (valid)
    {
        cout << "Valid Proof" << endl;
    }
    else
    {
        cout << "Invalid Proof" << endl;
    }
}