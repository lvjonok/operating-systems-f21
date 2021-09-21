# We should check existence of this file before writing to it anything
if ! [ -f ex2.txt ]
then
    echo -n 0 >> ex2.txt
fi

while :
do
    # nothing stops other processes to execute some operations on file ex2 here
    # that means two processes easily could read the same last integer and
    # result in missed pattern in the resulting file
    echo -n "\n$(($(tail -n 1 ex2.txt) + 1))" >> ex2.txt
done