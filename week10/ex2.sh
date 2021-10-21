mkdir week01
mkdir week10

echo "God bless Succi" > week01/file.txt
rm ex2.txt
rm week10/_ex2.txt

link week01/file.txt week10/_ex2.txt

find week01/file.txt -inum "$(ls -i week01/file.txt | cut -d" " -f1)" >> ex2.txt
find week01/file.txt -inum "$(ls -i week01/file.txt | cut -d" " -f1)" -exec rm {} \; >> ex2.txt
