if ! [ -f ex2.txt ]
then
    echo -n 0 >> ex2.txt
fi

while :
do
    echo -n "\n$(($(tail -n 1 ex2.txt) + 1))" >> ex2.txt
done