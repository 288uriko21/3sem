**Number 1**
Сalculating the root of x with precision E in an iterative way

---

**Number 2**
Implemented 2.1 and 2.2 together. To calculate the derivative at this point,
the coefficients of the polynom obtained using the Horner scheme for dividing the original polynomial by (x-a)
are used as the coefficients of the input polynom.

---

**Number 2_3**
2.2.1-2.2.3 are implemented. To calculate a definite integral, the formula
of an indefinite integral is first applied for each term of the original polynom. 
The value of each of these indefinite integrals is calculated at a given point. 
When summing these results , we get a certain integral from 0 to x .

---

**Number 3**
The tests showed, that whith calculating large Fibonacci numbers,
the recursive function works noticeably slower.

---

**Number 4**
First, the integer part of the number is recognized, then the fractional part (if there are any). 
After that, the number after "e/E" is taken into account, that is, multiplying the previously recognized number by a power of 10.

---

**Number 5**
Letter-by-letter word comparison is implemented as a separate function.
Reading: we select the "next word" in advance, read the word entered from the keyboard there. 
At the end of the loop, we free up one extra allocated space for the word / replace it with NULL. 
In the same cycle, we remember the last word, so that later we delete everything except it, the same.

---

**Number 6**
A non-recursive description of all functions, except myfree, necessary to free dynamic memory at the end of the program.
Deletion: instead of the element being deleted, we try to put "the leftmost element from its right subtree". 
We consider 3 cases: the element being deleted has neither a left nor a right subtree; there is no one of the subtree;
there are both subtree. Adding an element as a tree leaf.

---

**Number 7**
<выражение> ::= <слагаемое> {+ <слагаемое>} | <слагаемое> {- <слагаемое>}
<слагаемое> ::= <степень> {* <степень>} | <степень> {/ <степень>}
<степень> ::= <множитель> {^ <степень>}
<множитель> ::= 0|1|2|3|4|5|6|7|8|9| (<выражение>)