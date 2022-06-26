#! /bin/bash
echo -e "---------------------------------------------------------"
echo -e "Show all records of personal diary below:\n\n"
./pdlist < showall.txt
echo -e "---------------------------------------------------------"

echo -e "Search entities: \n\n"
./pdlist < searchoption.txt
echo -e "---------------------------------------------------------"

echo -e "show all diary with date"
./pdshow
echo -e "---------------------------------------------------------"

echo -e "before add diary: \n\n"
cat diary.txt
echo -e "---------------------------------------------------------"
./pdadd < tobeadded.txt
echo -e "After adding diary, all records listed below: \n\n"
cat diary.txt
echo -e "---------------------------------------------------------"

echo -e "before remove: \n\n"
cat diary.txt
echo -e "---------------------------------------------------------"
./pdremove < tobedelete.txt
echo -e "after remove: \n\n"
cat diary.txt
echo -e "---------------------------------------------------------"
read a
