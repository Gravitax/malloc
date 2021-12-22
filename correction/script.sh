#!/bin/bash

# LINUX
# export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
# MACOS
# export DYLD_LIBRARY_PATH=. DYLD_INSERT_LIBRARIES="libft_malloc.so" DYLD_FORCE_FLAT_NAMESPACE=1

echo "---------- MALLOC CORRECTION -----------"
echo "---------------------"
echo "Fichier auteur :"
cat -e auteur
# echo "---------------------"
# echo "Regles du Makefile :"
# grep -E "all:|clean:|fclean:|re:" Makefile
# echo "---------------------"
# echo "Norminette :"
# norminette src/*.c include/*.h libft/*.[ch]
# echo "---------------------"
# echo "Exporting HOSTTYPE variable..."
# export HOSTTYPE=Testing
echo "---------------------"
echo "Building the project..."
make re
echo "---------------------"
echo "Library link:"
ls -l libft_malloc.so
echo "---------------------"
echo "Makefile HOSTTYPE usage:"
grep "NAME = " Makefile
echo "---------------------"
echo "Appels systeme:"
nm libft_malloc.so | egrep "malloc|free|realloc|mmap|munmap"

echo "---------------------"
echo "Test 0:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test0 correction/test0.c -l"ft_malloc"
/usr/bin/time -l ./test0
echo "---------------------"
echo "Test 1:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test1 correction/test1.c -l"ft_malloc"
/usr/bin/time -l ./test1
echo "---------------------"
echo "Test 2:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test2 correction/test2.c -l"ft_malloc"
/usr/bin/time -l ./test2
echo "---------------------"
echo "Test 3:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test3 correction/test3.c -l"ft_malloc"
./test3
echo "---------------------"
echo "Test 3bis:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test3bis correction/test3bis.c -l"ft_malloc"
./test3bis
echo "---------------------"
echo "Test 4:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test4 correction/test4.c -l"ft_malloc"
./test4
echo "---------------------"
echo "Test 5:"
gcc -L"/Users/marc-antoine/workplace/malloc" -o test5 correction/test5.c -l"ft_malloc"
./test5
echo "---------------------"
# echo "main:"
# gcc -L"/Users/marc-antoine/workplace/malloc" -o main correction/main.c -l"ft_malloc"
# ./main

rm test*
