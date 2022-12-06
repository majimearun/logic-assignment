Submission for CS F214: Logic assignment 2

Done by:

    1. Arunachala Amuda Murugan (2021A7PS0205H)
    2. Ayush Bhauwala (2021A7PS0180H)
    3. Suryansh Chandola (2021A7PS0058H)

ALGORITHM

1. Each line of the proof is taken as input, line by line

2. The propostional logic formula entered as input is added to a vector

3. A vector that stores the parts of an input line (propositional logic formula and proof rule used) is created

4. Based on the proof rule used, the appropriate function to check the validity of the rule is called

5. The split function is used to split the given propositional logic formula, into 2 parts at the root of the formula

EXAMPLE OUTPUT\n
Tested with the proof in file proof.txt, the output is : Valid Proof

For the implementation of other rules:\n
Each element in the 'values' vector will be a pair of the propositional logic formula and an integer that denotes the level of scope in which the propositional logic formula is available.

For example, consider the following proof:

1. p>q premise
2. ~q assumption
3. ~p MT 1,2
4. ~q>~p >i 2-3

The values vector will look like {(p>q, 0), (~q, 1), (~p, 1), (~q>~p, 0)}

Each line can access propositional logic formula from lines whose scope integer is less than or equal to it's own scope integer.

Here, lines with scope 1 can access lines with scope 0 or 1 while lines with scope 0 can access lines with scope 0 only.
