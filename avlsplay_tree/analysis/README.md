# AVL/Splay Tree Analysis
## Test Cases Used in Assignment
* I tested using test cases of multiple sizes, going from small 10 line
text files up to text files of over 1000 lines. Three main test cases 
were particularly instructive. I used a test case with 10 words, a test
case with 720 words but in alphabetical order, and a test case with the 
1000 most common english words but in random order.

## Results
1. 10 line test case
    * 20 insertions
    * AVL: 2.64e-06 seconds
    * Splay: 5.13e-06 seconds
    * Splay expensive: 0
2. 720 line test case (alphabetical order)
    * 1440 insertions
    * AVL: 0.00086507 seconds
    * Splay: 0.00024345 seconds
    * Splay expensive: 0
3. 1000 line test case (random order)
    * 2000 insertions
    * AVL: 0.00130159 seconds
    * Splay: 0.00256288 seconds
    * Splay expensive: 67
4. I did all the analysis of these results below

## Methods Used and Analysis
* When running the analysis, I repeated the process of inserting all the words
into the splay and AVL trees 100 times and then averaged the durations for my
answers. This ensured that differences didn't round to 0.
* Looking at the results above, I notice a clear and sensible difference based on 
the input. In the first case, the small input causes both to have very small durations
for the operations. However, the AVL tree is faster in this case. This is likely
because when there is such a small input, the tree rarely gets imbalanced so it is similar
to just inserting into a BST whereas the splay tree requires splay operations each time.
* In the second case, now that the input is bigger, the Splay Tree was faster. This is because
there were no splay expensive operations, likely due to the input being in alphabetical order.
However, the avl tree required a lot of rebalancing since the input was bigger this time.
* Finally, in the third case, the Splay Tree becomes more expensive than the AVL tree. The AVL
definitely still required rebalancing with such a large input, but now there were splay expensive
operations (67 to be exact). This is because the input was random this time, causing there to
be insertions far down the tree in some cases rather than there being a mostly balanced tree throughout
the process.
* Overall, the results were clearly impacted by the parameters. Based on the test cases I ran
the trees both seem to function as intended.

## Performance of Insertion in Other Cases
* Unsorted List: Inserting into an unsorted list would be very fast because there are no changes in structure
involved, you just insert at the end. It would be faster than both trees.
* Sorted List: A sorted list would take a long time since a linear search must be performed every time.
Additionally, items will have to be moved over every time unless it is a linked list and not
an array. This will take longer than both trees for insertion.
* Regular BST: Inersting into a BST will be faster since it is the exact same as a splay and avl tree but 
without any rotations. However, retrieving values from the tree will be more difficult than
a splay or an avl tree.
* Hash Table (with universal hash function): A hashtable would be faster for insertion since one just has to calculate the hash function and then insert the proper values at that spot in the array. There may be a little extra time for chaining
or probing but it will be much less than a splay or avl tree.
