## chapter 2: introduction to the relational model

---

### 2.1 structure of relation database

> - relation -- table 	
> - tuple or relationship -- a row(their order doesn't count)
> - attribute(属性) -- a column
> - relation instance -- a specific instance of a relation
> - domain of a attribute -- D1 * D2 * D3 * .....* Dn

#### 命名规则

a schema -- 'R'	an instance --'r' 
**R is a set of attribute, r is a set of tuples**

####  domain of a attribute

atomic if care.
==**null**== is a special value means unknown.	null may cause problems.

### 2.2 database schema

relation -- relation schema
variable -- type definition

### 2.3 Keys

---

**a ==superkey== is a set of one or more attributes that identity a unique tuple in the relation**
**a ==candidate key== is minimal (if remove one more attribute in that, it is not a superkey)**
**the ==primary key== is a key selected from candidate key.**
**==Foreign key== constraint :value that must appear in another relation**
referencing relation	referenced relation(must be a primary key)
foreign-integrity constraint

### 2.6 The relation algebra

---

> > - select : "$\sigma$" --instance	 $\sigma$_dept_name = “Physics” (instructor)
> > - project(投影): "$\prod$" -- instance $\prod$ *ID, name, salary* (*instructor*) 
> > - union: "$\cup$" -- instance A $\cup$ B    (A, B must have the same attribute)
>
> > - set difference : "-" -- instance  r - s    (A, B must have the same attribute)
> > - cartesian product: "x" -- 
> > - join : "$\Join$" -- combine product and select 
>
> > - set-intersection operation : "$\cap$"
> > - natural-join operation : "$\Join$"
> > - assignment operation: "$\leftarrow$"
> > - outer join : 1. natural join  2.

