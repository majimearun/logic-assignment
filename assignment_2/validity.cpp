#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/// @brief A struct that contains the root node of a given propositional logic formula and it's index in the string.
struct res
{
    char root; /*!<This is the root node of a given formula.*/
    int index; /*!<This is the position of the root node in the string.*/
};

/// @brief Finds root node of the propositional logic formula.
/// @param s The propositional logic formula.
/// @return A pointer to a struct res that contains the root node and and it's index in the string.
res *find_root(string s)
{
    int add = 0;
    if (s.length() > 1)
    {
        if (s[0] != '(' && s[0] != '~')
        {
            return new res{'\0', -1};
        }
        else if (s[0] == '(')
        {
            s = s.substr(1, s.length() - 2);
            add++;
        }
    }
    if (s[0] != '~')
    {
        int counter = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                counter -= 1;
            }
            else if (s[i] == ')')
            {
                counter += 1;
            }
            if (counter == 0)
            {
                return new res{s[i + 1], i + 1 + add};
            }
        }
    }
    else
    {
        s = s.substr(1);
        if (s[0] == '(')
        {
            int counter = 0;
            int i;
            for (i = 0; i < s.size(); i++)
            {
                if (s[i] == '(')
                {
                    counter -= 1;
                }
                else if (s[i] == ')')
                {
                    counter += 1;
                }
                if (counter == 0)
                {
                    break;
                }
            }
            if (i == s.length() - 1)
            {
                return new res{'~', 0};
            }
            res *ans = find_root("(" + s + ")");
            ans->index += 1;
            return ans;
        }
        else
        {
            if (s.length() == 1)
            {
                return new res{'~', 0};
            }
            return new res{s[1], 2 + add};
        }
    }
}
/// @brief A struct that stores validity of a given line of proof and the propositional logic formula split into 2 parts at the root.
struct split_result
{
    bool valid;           /*!<Checks if the split is valid.*/
    vector<string> parts; /*!<Stores the left and right part of a formula split at the root node.*/
};

/// @brief Splits the propositional logic formula at its root node
/// @param s The propositional logic formuala to be split at the root
/// @param delimiter The operator expected to be the root node
/// @return A pointer to struct split_result that stores the validity and parts of the split
split_result *split(string s, char delimiter)
{
    res *result = find_root(s);
    if (result->root != delimiter)
    {
        return new split_result{false, {}};
    }
    string left = s.substr(1, result->index - 1);
    string right = s.substr(result->index + 1);
    right = right.substr(0, right.length() - 1);
    return new split_result{true, vector<string>{left, right}};
}

/// @brief Checks if the 'and introduction' rule has been used correctly
/// @param l1 The first propositional logic formula used in the 'and introduction' rule
/// @param l2 The second propositional logic formula used in the 'and introduction' rule
/// @param r The propositional logic formula that used the 'and introduction' rule
/// @return Boolean that checks if the rule has been correctly used
bool and_intro_checker(string l1, string l2, string r)
{
    return "(" + l1 + "*" + l2 + ")" == r;
}

/// @brief Checks if the 'and elimination' rule has been used correctly
/// @param l The propositional logic formula on which 'and elimination' rule has been used
/// @param r The propositional logic formula formed as a result of the use of 'and elimination' rule
/// @param n Integer that stores whether 'and elimiation' rule 1 or 2 has been used
/// @return Boolean that checks if the rule has been correctly used
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

/// @brief Checks if the 'or introduction' rule has been used correctly
/// @param l The propositional logic formula on which 'or introduction' rule has been used
/// @param r The propositional logic formula formed as a result of the use of 'or introduction' rule
/// @param n Integer that stores whether 'or introduction' rule 1 or 2 has been used
/// @return Boolean that checks if the rule has been correctly used
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

/// @brief Checks if the 'implies elimination' rule has been used correctly
/// @param l1 The propositional loigc formula with root as >
/// @param l2 The propositional logic formula on which > is checked
/// @param r The propositional logic formula formed as a result of the use of 'implies elimination' rule
/// @return Boolean that checks if the rule has been correctly used
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

/// @brief Returns negation of propostional logic formula
/// @param s The propositional logic formula to be negated
/// @return The negated propostional logic formula
string make_negation(string s)
{
    if (s[0] == '~')
    {
        return "~" + ("(" + s + ")");
    }
    else
    {
        return "~" + s;
    }
}

/// @brief Checks if the 'MT' rule has been used correctly
/// @param l1 The propositional loigc formula with root as >
/// @param l2 The propositional logic formula on which > is checked
/// @param r The propositional logic formula formed as a result of the use of 'MT' rule
/// @return Boolean that checks if the rule has been correctly used
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
    vector<string> lines;  // Vector containing the input lines of the proof.
    vector<string> values; // Vector containing the propositional logic formula entered.
    bool valid = true;
    for (int i = 0; (i < n) && valid; i++)
    {

        string line;
        cin >> line;
        vector<string> parts; // Vector containing the input lines of the proof split into parts conatining propositional logic formula, proof rule, and line numbers.
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