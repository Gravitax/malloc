#!/bin/bash

echo "---------------------"
echo "Fichier auteur :"
cat auteur
echo "---------------------"
echo "Regles du Makefile :"
grep -E "all:|clean:|fclean:|re:" Makefile
echo "---------------------"
echo "Norminette :"
norminette src/*.c include/*.h libft/*.[ch]
echo "---------------------"
echo "---------- MALLOC CORRECTION -----------"
echo "Exporting HOSSTYPE variable..."
export HOSTTYPE=Testing
echo "Building the project..."
make re
echo "---------------------"
echo "Library link:"
ls -l libft_malloc.so
echo "---------------------"
echo "Makefile HOSSTYPE usage:"
grep "NAME = " Makefile
echo "---------------------"
echo "Export des fonctions:"
nm libft_malloc.so | pcregrep -M " _free\n| _malloc\n|_realloc\n|_show_alloc_mem\n"
echo "---------------------"
echo "Export des appels systeme:"
nm libft_malloc.so | pcregrep -M "_mmap\n|_munmap\n|_getpagesize\n|_write\n|dyld_stub_binder\n"
echo "---------------------"
echo "Test 0:"
gcc -o test0 correction/test0.c
sh correction/script_macos.sh ./test0 > result_0
grep -Er "page reclaims" result_0
echo "---------------------"
echo "Test 1:"
gcc -o test1 -L. -lft_malloc correction/test1.c
sh correction/script_macos.sh ./test1
echo "---------------------"
echo "Test 2:"
gcc -o test2 correction/test2.c
sh correction/script_macos.sh ./test2
echo "---------------------"
echo "Test 3:"
gcc -o test3 correction/test3.c
sh correction/script_macos.sh ./test3
echo "---------------------"
echo "Test 3bis:"
gcc -o test3bis -lft -Llibft/ -Ilibft/ -L./ -lft_malloc -Iinclude/ correction/test3bis.c
sh correction/script_macos.sh ./test3bis
echo "---------------------"
echo "Test 4:"
gcc -o test4 -lft -Llibft/ -Ilibft/ -L./ -lft_malloc -Iinclude/ correction/test4.c
sh correction/script_macos.sh ./test4
echo "---------------------"
echo "Test 5:"
gcc -o test5 -lft -Llibft/ -Ilibft/ -L./ -lft_malloc -Iinclude/ correction/test5.c
sh correction/script_macos.sh ./test5
rm test*
