# Cornell-CS4120
I'm taking Cornell University's "Introduction to Compilers" course. Follow along with me!

### Course information
Course website: https://www.cs.cornell.edu/courses/cs4120/2023sp/
This is one of the best introductory compiler courses out there and it's completely free. The lecture videos are available only to Cornell students, but the lecture notes are just as good, if not better than the lecture videos (their words, not mine). I'll be doing the lessons, the supplemental readings, the homework assignments and the programming assignments.

## Study sessions
#### 01 - Course Overview
My study session: https://www.youtube.com/watch?v=U8bg22j2Yt4

In this lesson we get a high-level view of the main components of a compiler, including lexical analysis, syntactic analysis, semantic analysis, intermediate code generation, code optimization and machine dependent phases. We learn the difference between the frontend and backend of a compiler.

#### 02 - Supplemental reading
My study session: https://www.youtube.com/watch?v=ZzOJ0UORxMA

In this lesson we go through the supplemental readings from the Dragon book. We delve deeper into the way tokens are represented, and we learn about a fundamentally important data structure used throughout most of the compilation process: the Symbol Table. We also see more examples of Intermediate Representation of code, and during the study session I show an example of breaking down the individual steps used in the G++ compiler.

#### 03 - Lexical Analysis and Regular Expressions
My study session: https://www.youtube.com/watch?v=b2VPWksZGIE

We go into more depth on how modern lexers tokenize input streams. We start learning the notation and arithmetic surrounding Regular Expressions and discern how Regular Expressions help solve common problems with lexers (such as overlapping tokens and lookahead issues).

#### 04 - Automating Lexical Analysis
My study session: https://www.youtube.com/watch?v=18mFL3ySy5I

This was a tough lesson (the best kind of lesson). Going even deeper into the mathematics surrounding regular expressions, Deterministic and Non-deterministic Finite Automata (DFA and NFA), we tackle the problems of converting back and forth between these different representations of string matching patterns. This lesson preps us for the upcoming homework assignment.

#### 05 - Homework Assignment 1
My study session: https://www.youtube.com/watch?v=MQzJyxpnG90

We go through the homework questions, including the conversion of Regular Expressions to NFAs(and vice versa), NFAs to DFAs, and the concept of equivalent states/transitions in NFAs.

#### 06 - Grammars and Parsing
My study session: https://www.youtube.com/watch?v=7xEPBkLrvCk

We move onto Syntactic Analysis, diving into the construction of Context Free Grammars as the first step towards building an abstract syntax tree. We learn about common problems with top-down parsers and how to work around them.

