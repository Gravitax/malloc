#!/bin/bash

echo "---------- MALLOC CORRECTION -----------"
echo "---------------------"
echo "Fichier auteur :"
cat auteur
# echo "---------------------"
# echo "Regles du Makefile :"
# grep -E "all:|clean:|fclean:|re:" Makefile
# echo "---------------------"
# echo "Norminette :"
# norminette src/*.c include/*.h libft/*.[ch]
echo "---------------------"
echo "Exporting HOSTTYPE variable..."
export HOSTTYPE=Testing
echo "---------------------"
echo "Exporting LIB PATH LINUX..."
sh correction/script_linux.sh
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
echo "Export des fonctions et appels systeme:"
nm libft_malloc.so

# gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test path/test.c -l"ft_mallocx86_64_Linux"
# gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test path/test.c -l"ft_mallocTesting"

echo "---------------------"
echo "Test 0:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test0 correction/test0.c -l"ft_mallocTesting"
/usr/bin/time --verbose ./test0
echo "---------------------"
echo "Test 1:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test1 correction/test1.c -l"ft_mallocTesting"
/usr/bin/time --verbose ./test1
echo "---------------------"
echo "Test 2:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test2 correction/test2.c -l"ft_mallocTesting"
/usr/bin/time --verbose ./test2
echo "---------------------"
echo "Test 3:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test3 correction/test3.c -l"ft_mallocTesting"
./test3
echo "---------------------"
echo "Test 3bis:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test3bis correction/test3bis.c -l"ft_mallocTesting"
./test3bis
echo "---------------------"
echo "Test 4:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test4 correction/test4.c -l"ft_mallocTesting"
./test4
echo "---------------------"
echo "Test 5:"
gcc -L"/mnt/nfs/homes/maboye/workplace/malloc" -o test5 correction/test5.c -l"ft_mallocTesting"
./test5

rm test0 test1 test2 test3 test3bis test4 test5
# make fclean
