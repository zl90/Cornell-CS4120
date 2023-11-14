# Cornell-CS4120
I'm taking Cornell University's "Introduction to Compilers" course. Follow along with me!

### Course information
This is one of the best introductory compiler courses out there and it's completely free. The lecture videos are available only to Cornell students, but the lecture notes are just as good, if not better than the lecture videos (their words, not mine). I'll be doing the lessons, the supplemental readings, the homework assignments and the programming assignments.

Course website: https://www.cs.cornell.edu/courses/cs4120/2023sp/

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

#### 07 - Chipping away at Assignment 1
My study session: https://www.youtube.com/watch?v=B2myITLRHy8

Before going too deep on Syntactic Analysis, I decide to tackle the first programming assignment. Here you can see me going through the assignment spec and the Eta language spec.

#### 08 - Assignment 1 DONE!
Me demoing the finished assignment: https://www.youtube.com/watch?v=WoRMcVGTsW0

#### 09 - Top-Down parsing
My study session: https://www.youtube.com/watch?v=KakDREosyKw

Here we learn how Predictive Parsing Tables (PPTs) are generated and used to easily implement Recursive Descent Parsers. This was a challenging lesson for me, particularly the algorithms for computing the FIRST and FOLLOWS sets. I ended up finding youtube videos that showed these algorithms being done in a visual way which helped me understand better.

If you are struggling, here are some videos which may help:
- [LL(1) Parsing](https://www.youtube.com/watch?v=clkHOgZUGWU)
- [FIRST and FOLLOW functions](https://www.youtube.com/watch?v=oOCromcWnfc)
- [LL(1) Parsing Table](https://www.youtube.com/watch?v=DT-cbznw9aY)

#### 10 - Bottom-up parsing
My study session: https://www.youtube.com/watch?v=PDaQlcEZw7Q

More parsing algorithms. We learn the ingeneously simple Earley parsing algorithm, as well as the Shift-Reduce (LR) parsing algorithm. These are tough to decipher from the lecture notes and notation. Again, look up the algorithms on Youtube if you are struggling --> this really helped me to understand better! We will need to know these algorithms to complete the homework.

#### 11 - LR parsing and parser generators
My study session: https://www.youtube.com/watch?v=br7SDWXZxic

We are introduced to the LR(1) and LALR parser algorithms which are very similar to the LR(0) algorithm but more powerful. We also learn about reduce-reduce and shift-reduce conflicts that can occur in LR parsers with ambiguous grammars.

## Programming Assignments
#### Assignment 1 - Lexical Analysis: Retrospective
Me demoing the finished assignment: https://www.youtube.com/watch?v=WoRMcVGTsW0

This was a solid first assignment, as it threw me in the deep end and I had to learn a lot to stay afloat. I learned a LOT and it took me longer than expected to finish. Some of the things I learned:
- How to use the Flex lexer generator to generate a C lexer program.
- How to add my own custom C functions and use them inside Flex actions.
- Got a bunch of experience writing regular expressions.
- Learned how to install and use the Google Test suite for C++ projects.
- Learned how to execute shell commands from inside a C++ program (`popen`);
- Discovered the Github kanban board (Projects)! --> Had no idea this existed until I stumbled upon it while working on this assignment.

**Some questions from the assignment spec**

*Have you thought about the key data structures in this assignment?*

I figured we would need some way to pass the filenames and directory name from the command line arguments to the actual lex program. To do this I built a custom data type named `LexInfo` which contained the relevant information needed by the lex function - namely the `input_filename` and the `output_filename`.
I elected not to create a custom data structure to store the output of the lexer because this will need to be handled in the 2nd assignment, where we will presumably read the `.lexed` output files into memory to get a list of tokens. 

*Have you thought through the key algorithms and identified implementation challenges?*

Parsing the CLI arguments was something I decided to do myself (as opposed to using a library to do it) as I wanted to control the format of the output so I could send it to the lexer. This ended up working well.
Additionally, inside the Flex input file I had some choices to make, I could have used custom rule states and alternated between them to get the expected output (for example: using a `INSIDE_STRING_LITERAL` state to dictate how the scanner operates when currently scanning a string literal), or using my own custom C functions inside the existing rules. I realised that I didn't actually need custom rule states and everything I wanted could be accomplished with two custom C functions: `handle_unicode_escape_sequences` and `remove_quotations`.

*Do you have a testing strategy that covers the possible inputs and the different kinds of functionality you are implementing?*

Yes, I used the Google Test suite to unit test each input file and check them against the official solutions. All tests are passing.

