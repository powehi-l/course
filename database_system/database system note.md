

## database system

### charpter 2

##### 2.1 structure of relation databases

a collection of table, tuple, relation, attribute, relation instance, domain of attribute, null value
==a relation is just a set==(unsorted), ==a domain is atomic==, distinguash database schema and database instance

##### 2.2 database schema

difference between relation and relation schema?(没看懂)

##### 2.3 keys

superkey(a subset, distinguash tuples), candidate keys(minimal superkey)
primary key(a specific candidate key),  foreign key(referencing relation, referenced relation), referential integrity constraint
==distinguash foreign key and referential integrity constraint==

##### 2.4 the relation algebra

- Select 选择：$\sigma_{p}(r)={t|t\in r \and p(t) }$
  - 筛选出所有满足条件p(t)的元素t
  
- Project投影：$\prod_{A_1,A_2,\cdots,A_k}(r)$
  - 运算的结果是原来的关系r中各列只保留属性$A_1,A_2,\dots,A_k$ 后的关系
  - 会**自动去掉重复**的元素，因为可能投影的时候舍弃的属性是可以标识关系唯一性的属性
  
- Union 并操作：$r \cup s={t|t\in r \or t \in s}$
  - 两个关系的属性个数必须相同
  - 各属性的domain必须是可以比较大小的
  
- Set difference 差操作：$r-s={t| t\in r \and t \notin s}$

- Cartesian-Product笛卡尔积：$r\times s={tq| t\in r\and q\in s}$
  - 两个关系必须是不相交的，如果相交则需要对结果中重复的属性名进行重命名
  - 笛卡儿积运算的结果关系中元组的个数应该是rs的个数之乘积
  
- Renaming重命名：$\rho_{X}(E)$
  - 将E重命名为x, 让一个关系拥有多个别名，同时X可以写为$X(A_1,A_2,\dots,A_n)$ 表示对属性也进行重命名
  - 类似于C++中的引用
  
- 扩展运算: 可以用前面的六种基本运算得到
    - Intersection 交运算$r \cap s={t|t\in r \and t \in s}=r-(r-s)$
    - Natual-Join 自然连接：$r\Join s$
      - 两个关系中同名属性在自然连接的时候当作**同一个属性**来处理
      - **Theta join** 满足某种条件的合并：$r\Join_{\theta} s=\sigma_{\theta}(r\Join s)$
    - Outer-Join外部连接，分为左外连接，右外连接，全外连接
      - 用于应对一些**信息缺失**的情况(有null值)
      - 左外连接$\ltimes $
        - 左边的表取全部值按照关系和右边连接，右边不存在时为空值
      - 右外连接$\rtimes $
        - 右边的表取全部值按照关系和右边连接，不存在为空值
      - Full join左右全上，不存在对应的就写成空值
    - Division除法：$r\div s={t|t\in\prod_{R-S}(r)\and \forall u \in s (tu\in r)}$
      - 如果$R=(A_1,A_2,\dots,A_m,B_1,\dots,B_n)\and S=(B_1,\dots,B_n)$ 则有$R- S=(A_1,A_2,\dots,A_m)$
    - Assignment声明操作，类似于变量命名用$\leftarrow$ 可以把一个关系代数操作进行命名
  - Aggregation operations聚合操作
    - 基本形式：$*{G_1,G_2,\dots,G_n}{\cal {G}}*{F_1(A_1),\dots,F_n(A_n)}(E)$
    - G是聚合的标准，对于关系中所有G值相同的元素进行聚合，F( )是聚合的运算函数
    - 常见的有SUM/MAX/MIN/AVG/COUNT
  

### chapter 3 introduction to sql

##### 3.1 overview

consist: DDL, DML, integrity,view definition, transaction control, embedded SQL and dynamic SQL, authorization

##### 3.2 SQL data definition(数据定义)

- basic type: char(n), varchar(n), int, smallint, numeric(p,d)(p为有效数字，d为小数位数), real, double precision, float(n)

- 创建表

  ```sql
  create table department(
  	dept_name varchar(20),
  	building varchar(15),
  	budget numeric(12,2)not null,
  	primary key(dept_name),
  	foreign key (dept_name) references department);
  ```

- 删除表 drop table s;

- 添加/删除/更改attribute,

  ```sql
  alter table r add salary int;
  alter table r drop salary;
  
  alter table r
  modify clolumn salary real;
  ```

##### 3.3 basic structure of SQL queries(查询语句)

- 基础形式

  ```sql
  select A1,A2,…,An
  from r1,r2,…,rn
  where P
  ```

- 其他细节
  - order, 先from，再where， 最后select
  
  - as clause，重命名(select, from)
  
  - select子句中
    -  distinct/ select all
    
  - where中
    - and, or, not
    - between and
    
  - order by(进行排序)
  
  - 集合操作：union/intersect/except
  
  - null-- 1<null = unknown
  
  - aggregation(any attribute in "select" not in aggregate should be in "group")
  
    - having: denote the attribute of a group
  
  - nest
  
    - set membership: in/ not in
    - \>,<,>=,<= + some + 子查询, 判断存在
    - all + subquery
    - exists + subquery
    - not exists + subquery
  
  - modification
  
    ```sql
    delete from r where P;
    insert into r values r1;
    update r set ... where P;
    ```

##### 3.4 intermediate SQL

- join epressions

  - natural join(equal to "a join b using(attribute)")
  - normal join("a join b on a.ID = b.ID")
  - outer join

  ```sql
  join type: inner join; left outer join ; right outer join; full outer join;
  
  join condition: natural; on ; using
  ```

- views

  - defination

  ```sql
  create view name as
  	(select A
  	from r
  	where p);
  ```

  - materialized views(up-to-date)
  - update of views(condition to update a view)
    - from has only one database relation
    - select only contain attribute names
    - any attribute in the 

### chapter 6: database design using the E-R model

##### 6.1 E-R model

- composing entity and relationship
- entity set
  - entity set is a set of some object(actual object or concept object), entity is denote by some attribute
- relationship set
  - a relationship is the relation between several entity
- attribute types
  - simple and composite
  - single valued and multivalued--{name}
  - derived(派生compute from another attribute when needed)--name()
  - null, missing unknown
- E-R model constraint
  - mapping cardinalities
    - in binary relationship, only one-to-one, one-to-many, many-to-one, many-to-many
    - 箭头表示one, 直线表示many
  - 参与度约束:total(必须全部在关系中，用双横线表示), partial(不用全部参与)
  - low..max, low denote minimal in relationship, max denote maximal in relationship.
  - key约束:for entity, the same with relation schema. for relationship, union entity set's primary key. if(one-to-many or many-to-one...) use the one's primary key
  - weak entity set, rely on a identifying entity. 
- removing redundant attributes in entity sets