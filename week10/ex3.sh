echo "God bless Herman" >> _ex3.txt
rm ex3.txt

ls -l _ex3.txt >> ex3.txt
chmod -x _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod 707 _ex3.txt >> ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod -R g=u _ex3.txt >> ex3.txt
ls -l _ex3.txt >> ex3.txt

echo "660 means that only owner and group can r/w file" >> ex3.txt
echo "775 means that owner and group has all rights for file and others can only read/execute" >> ex3.txt
echo "777 means everyone has all rights" >> ex3.txt
