#### Question 1
Regular expression: (GTG)(\[TGAC\]{3})\*(TGA|TAG|TAA)
\*See the image file `question_1.png` for the (ugly) NFA drawing.

#### Question 2
DFA table:
	a	b	c	d
------------------------------------
**1**	2,3		3	
**2**				1,3
**3**		1	2	1
**1,3**	2,3	1	2,3	1,3
**2,3**		1	2,3	1,3

#### Question 3


