gcc ex1.c

rm answer10.txt >/dev/null 2>/dev/null
rm answer50.txt >/dev/null 2>/dev/null
rm answer100.txt >/dev/null 2>/dev/null

echo 10 | ./a.out >> answer10.txt
echo 50 | ./a.out >> answer50.txt
echo 100 | ./a.out >> answer100.txt