if ! [ -f ex2.txt ]
then
    echo -n 0 >> ex2.txt
fi

while :
do
    # link our file to .lock and modify only .lock
    # ln will return non zero exit code when the link is already present,
    # so it will block another processes to access the data
    if ln ex2.txt ex2.txt.lock 2>/dev/null; then
        echo -n "\n$(($(tail -n 1 ex2.txt) + 1))" >> ex2.txt.lock
        rm ex2.txt.lock
    fi
done