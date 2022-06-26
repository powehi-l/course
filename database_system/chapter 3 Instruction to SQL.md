# chapter 3: Instruction to SQL

## 3.2 SQL data definition language

### 3.2.1 domain Types in SQL

---

each include **null** 

> - char(n) : fixed length character string
> - varchar(n): variable length character string
> - int: integer
> - smallint: half byte of int(similar to short)
> - numeric: 
> - real, double precision
> - float(n)

### 3.2.2 basic schema definition

---

**"create table"** command
example:

```SQL
create table department
	(dept_name	varchar(20) not null,
	 building	varchar(15),
	 budget	numeric(12,2),
	 primary key(dept_name),
	 foreign key(dept_name) references department);
```

#### integrity-constraint
**not null** 
foreign key(referencing) references(referenced)
primary key(默认为not null, 不能重复)

#### drop and alter Table constructs

drop table student
delete from student

```sql
alter table r from A D(A is the name and D is domain)
alter table r drop A(delete attribute A)
```



## 3.3 Basic Structure of SQL Queries(DML:data-manipulation language)

### 3.3.1 queries on a single relation

```sql
select distinct(all) A1,A2,A3...
from r1,r2,r3...
where P

select *
from instructer

select name, course_id
from instructer natural join teaches 
```

 == $\prod$ ~a1~, ~a2~,... ($\sigma$ ~P~ (r1,r2,r3...))		(去重！！！！)
SQL names are case insensitive(大小写不敏感)

select distinct dept_name(去重的)
select all dept_name(不去重的)

old-name **as** new-name

## 3.4 Additional Basic operation
### 3.4.1  rename operation:	old name as new name

### 3.4.2 string operations

---

> - **like** 
>
>   > + %: any substring
>   > + _ :matches a character

### 3.4.4 order the display of tuples

**order by**

```sql
select name
from instructor
where dept_name = 'Physics'
order by name;

where (instructor.ID, dept_name) = (teaches.ID, 'Biology');
```

## 3.5 set operations

union -- $\$
intersect
except

```sql
(select course_id
from section
where semester = 'Fail' and year = 2017)

union all
(select course_id
from section
where semester = 'Fail' and year = 2017);
```

## 3.6 null value

salary is(not) null

```sql
select name
from instructor
where salary is null
```

## 3.7 aggregate function

avg, min, max, sum, count

```sql
select avg(salary)
from instrctor
where dept_name = 'comp.sci'

select count(distinct ID)
from teaches
where semester = 'spring' and year = 2018

select dept_name, avg(salary) as avg_salary
from instructor
group by dept_name
```

## 3.8 Nested Subqueries

some, all, exist, not exist, unique, not unique, with

## 3.9 modification of the database

---

1. delete from
   where ...

2. insert into <table>
   	value (...)s
3. update <table>
   set
4. 
