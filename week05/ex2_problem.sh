while :
do
    echo -n "\n$(($(tail -n 1 a.txt) + 1))" >> a.txt
done