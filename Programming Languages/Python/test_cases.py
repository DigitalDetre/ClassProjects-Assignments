# Test cases for python assignment
# Author: Curtis Helsel
# Spring 2019 - Programming Languages

import sys
import importlib

test_module = importlib.import_module(sys.argv[1])

# Word Smith Test Cases
def tc1():
    if test_module.word_smith("Programming languages is definitely the best \
            course I have taken in my entire undergraduate CS career!", "Don't \
            OVERTHINK it!") == 8 :
        return True
    else:
        return False

def tc2():
    if test_module.word_smith("You could easily write DOOM in python.", "But \
            but but Haskell!") == 4 :
        return True
    else:
        return False

def tc3():
    if test_module.word_smith("Python is the most powerful language you can \
            still read.", "- Paul Dubois") == 6 :
        return True
    else:
        return False

# Base Builder Test Cases
def tc4():
    if test_module.base_builder(493) == (10, 13231) :
        return True
    else:
        return False

def tc5():
    if test_module.base_builder(42) == (6, 222) :
        return True
    else:
        return False

def tc6():
    if test_module.base_builder(4) == (1, 10) :
        return True
    else:
        return False

for test_case in [tc1, tc2, tc3, tc4, tc5, tc6]:
    if test_case():
        print("Test Case {}: PASS".format(test_case.__name__[2]))
    else:
        print("Test Case {}: FAIL".format(test_case.__name__[2]))
