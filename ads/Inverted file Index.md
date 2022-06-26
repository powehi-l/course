# Inverted file Index

## structure

---

a dictionary: 

> - No.
> - Term
> - Times and Documents(with position which document and which place in that document)

### index generator

### key aspects

---

> - token analyzer stop filter
> - vocabulary scanner
> - vocabulary insertor
> - memory management

## Module 

---

### word stemming

process a word so that only its stem or root form is left

### stop words

'a', 'the', 'it'

### accessing a term

1. search tree(a range of posting list)
2. hashing(it maybe far for a range of list)(fast)

## topics

---

### distributed indexing

1. term-partitioned index(a~c, d~E,,,,)
2. 

