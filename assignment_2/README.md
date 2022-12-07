# Submission for CS F214: Logic assignment 2

Done by:

    1. Arunachala Amuda Murugan (2021A7PS0205H)
    2. Ayush Bhauwala (2021A7PS0180H)
    3. Suryansh Chandola (2021A7PS0058H)

## Algorithm

1. The proof is taken as input line by line (either input @ stdin or from a file using `<`).

2. The split function is used to split the given propositional logic formula, into 2 parts at the root of the formula

3. The propostional logic formula entered as input is added to a vector<string>.

4. A vector that stores the parts of an input line (propositional logic formula and proof rule used) is also created.

5. Based on the proof rule used, the appropriate function to check the validity of the rule is called.

6. The function runs as long as it reads valid proof lines or if it breaks out at an invalid line.

## Example Runs

### Example 1:

```cmd
15
(((a*b)>(c*d))>((~e*~f)>(~g+~h)))/P
((a*b)>(c*d))/P
(a*b)/P
(~e*~f)/P
((~e*~f)>(~g+~h))/>e/1/2
(~g+~h)/>e/5/4
(c*d)/>e/2/3
c/*e1/7
d/*e2/7
a/*e1/3
b/*e2/3
(a*b)/*i/10/11
(c*(a*b))/*i/8/12
(d*(c*(a*b)))/*i/9/13
((d*(c*(a*b)))+~i)/+i1/14
```

**Output** :

```
Valid Proof
```

### Example 2:

```cmd
4
(~a>b)/P
(b>c)/P
~c/P
~b/MT/2/3
~a/MT/1/4
```

**Output** :

```cmd
Invalid Proof
```

## For the implementation of other rules:

1. To implement scopes of boxes we will aditionally need two data structures. A pair<string, int> where the integer decalres the scope of the box and a map<int, bool> where we decalre whether the scope has ended or nor for a given number.

2. Any line can use other lines above it as long as its scope is >= the scope of the line as the scope referred to has not been closed (false in map).

3. The same scope number should never be used twice, so it can easily be implemented/assigned using a counter.

For example, consider the following proof:

(using `A` for assumption)

```cmd
1. (p>q)/P
2. ~q/A
3. ~p/MT/1/2
4. (~q>~p)/>i/2-3
```

The values vector will look like

```cpp
{
    <(p>q), 0>,
    <~q, 1>,
    <~p, 1>,
    <(~q>~p), 0>
}
```

Here, lines with scope 1 can access lines with scope 0 or 1 while lines with scope 0 can access lines with scope 0 only. And once the scope of 1 is over we assign it `false` in the map.
