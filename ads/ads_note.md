## chapter 1: AVL Tree

### AVL Tree

---

BS Tree problem: worst case O(N)
对于一个动态的查找， 任意时刻都要保证平衡

AVL Tree: for every node, height of left subtree h1 and height of right subtree h2, |h1-h2| < 1
**single rotation**
**double rotation**

### Splay Tree

---

从空树开始，对于任意M次操作，最多花费O(MlogN)
在执行查找的过程中：zigzag: a double rotation
										zig-zig: twice single rotation

delete x : 1. find x(x become root)	2. remove x(two subtree T1 and T2).	3. findmax(T1)	4. make T2 become right subtree of T1

### Amortized Analysis

---

Amortized bound: any M consecutive operation take at most O(MlogN) time

worst-case bound >= amortized bound >= average-case bound

1. Aggregate analysis:	
2. accounting method: credit, 
3. potential method:

## charpter 3 leftist heap

### NPL:

definition : npl of left subtree is as large as right one
theorem: a leftist tree with r nodes on the right path must have at least 2^r^-1 nodes

