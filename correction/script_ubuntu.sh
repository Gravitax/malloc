#!/bin/sh

export LD_LIBRARY_PATH="."

export LD_PRELOAD_PATH="./libft_malloc.so"

export HUGETLB_MORECORE=yes

$@
