# CC_Labfile
Semester-6 Compiler Construction Lab file 

# Exp1: Deterministic Finite State Automaton (DFA) for String Pattern Validation 
This program allows DFA to process strings consisting of 'a' and 'b' and accepts only those with an even number of 'a's and an odd number of 'b's.

# Exp2: Deterministic Finite State Automaton (DFA) for Binary Number Divisibility
This program allows DFA to check whether a given binary number is divisible by 5 or not using modulo 5 arithmetic.

# Exp3: Immediate Left Recursion
This program removes immediate left recursion if present in the production rules entered by the user

# Exp4: Left factoring
This program removes left factoring if present in the production rules entered by the user. This code doesn't work if the grammar is ambiguous and multiple levels of left factoring.

# Exp5: FIRST and FOLLOW
This program finds first and follow of the Context-free grammar entered by the user.

# Exp6: Recursive Descent Parser
This program parses the string given by the user using recursive descent parser for the following grammar:
E->E+T|T
T->T*F|F
F->id|(E)

# Exp7: Predictive Parser
This program parses the string given by the user using predictive parser for the following grammar:
E->E+T|T
T->T*F|F
F->id|(E)

# Exp8: LR(0) Parser
This program parses the string given by the user using LR(0) parser for the following grammar:
E->E+T|T
T->T*F|F
F->id|(E)

# Exp9: SLR(1) Parser
This program parses the string given by the user using SLR(1) parser for the following grammar:
E->E+T|T
T->T*F|F
F->id|(E)