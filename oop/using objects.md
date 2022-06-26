## using objects

---

### string

cin >> str
cout << str

### file

### Memory

> - global vars
> - extern
> - static
> - static local var

### **pointers to objects**

### dynamic memory allocation

> - new
> - delete

### reference

char& r = c(another name)
int &r = a
```int& *p(false)```
``` 	int* &p(right)```

### Const

```c++
const int x = 12
int y = x(false)
const int z = x(True)
```

replace 宏定义 problem: 1. scope(定义域)	2. 重复命名
const is a variable
**compile time constance**
**run time constance**

```c++
char * const q = "abc"; //q is const
*q = 'c'; //ok
q++;	//error

const char *p = "abcd";
*p = 'b'; //error

char const *p == const char *p
```

