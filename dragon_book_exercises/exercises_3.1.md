# Exercises for Section 3.1

## Exercise 3.1.1:
Divide the Following C++ Program:

```
	float limitedSquare(x) float x; {
		/* returns x-squared, but never more than 100 */
		return (x<=-10.0||x>=10.0)?100:x*x;
	}
```
into appropriate lexemes, using the discussion of Section 3.1.2 as a guide. Which
lexemes should get associated lexical values? What should those values be?

\<float>
\<id, pointer to the symbol table entry for limitedSquare (henceforth represented by value of 1)>
<(>
\<id, 1>
<)>
\<float>
\<id, 1>
<;>
<{>
\<return>
<(>
\<id, 1>
\<lte_op>
\<number, -10.0>
\<LOR_op>
\<id, 1>
\<gte_op>
\<number, 10.0>
<)>
\<tern_op>
\<number, 100>
\<colon_op>
\<id, 1>
\<mult_op>
\<id, 1>
<;>
<}>

## Exercise 3.1.2
Tagged languages like HTML or XML are di erent from conventional programming languages in that the punctuation (tags) are either very numerous (as in HTML) or a user-de nable set (as in XML). Further, tags can often have parameters. Suggest how to divide the following HTML document:
```
Here is a photo of <B>my house</B>:
<P><IMG SRC = "house.gif"><BR>
See <A HREF = "morePix.html">More Pictures</A> if you
liked that one.<P>
```
into appropriate lexemes. Which lexemes should get associated lexical values, and what should those values be?

<literal, pointer to symbol table>
<open_tag>
\<B\> (keyword)
<close_tag>
<literal, pointer>
<open_tag>
<end_tag>
\<B\> (keyword)
<close_tag>
<open_tag>
\<IMG\> (keyword)
<SRC> (keyword)
<assign_op>
<literal, pointer>
<close_tag>








