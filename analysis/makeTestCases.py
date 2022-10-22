import string
import random
import os

# using only operators which need 2 operands for ease of making large sized test cases
operators = ["+", "*", ">"]

# 3*size long expressions will be created
# size is number of small (3 nodes) tress
size = 25000

dir = os.path.dirname(os.path.realpath(__file__))

with open(dir + "/infixTestCase.txt", "w") as fh:
    infix = ""
    for i in range(size):
        infix += "("
        infix += random.choice(string.ascii_lowercase)
        infix += random.choice(operators)
    infix += random.choice(string.ascii_lowercase)
    for i in range(size):
        infix += ")"
    fh.write(infix[1:-1])

with open(dir + "/prefixTestCase.txt", "w") as fh:
    prefix = ""
    for i in range(size):
        prefix += random.choice(operators)
    for i in range(size + 1):
        prefix += random.choice(string.ascii_lowercase)
    fh.write(prefix)
