## chapter 4 Intermediate SQL

### 4.1 join expression

---

> 1. natural join
>
> 2. join ... using ...
>
> 3. join ... on ...(the same column will reserve both while natural join just save one)
>
> 4. outer join(include those not appear in another table)
>
>    > - natural left outer join
>    > - natural right outer join
>    > - natural full outer join

### 4.2 Views

---

1. **create view** <v> **as** <query>(attribute) **with check option**

2. materialized views

3. update of a view(condition)

   > 1. from clause has only one database relation
   > 2. select just contains names of relation(exclude aggregates or distinct)
   > 3. no **group by** or **having**

### 4.3 Transaction

commit work
rollback work

### 4.4 Integrity Constraints

---



