printf "3 -4 5 1 7 0\n8 0 15 12 3 5\n18\n19 20 30 7 12\n50\n34\n32\n19\n44" | ./histogram >> testing.out


printf "3 -4 5 1 7 0\n8 0 15 12 3 5\n3 3 3 3 3" | ./histogram >> testing.out

printf "150" | ./histogram >> testing.out

printf "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 150" | ./histogram >> testing.out

