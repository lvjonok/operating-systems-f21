if ! [ -f ex2.txt ]
then
    echo -n 0 >> ex2.txt
fi

while :
do
    if ln ex2.txt ex2.txt.lock 2>/dev/null; then
        echo -n "\n$(($(tail -n 1 ex2.txt) + 1))" >> ex2.txt.lock
        rm ex2.txt.lock
    fi
done