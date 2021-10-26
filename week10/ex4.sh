rm -rf tmp
mkdir tmp
touch tmp/file1
touch tmp/file2
link tmp/file1 tmp/link1
# touch tmp/file3
# link tmp/file3 tmp/h1
# link tmp/file3 tmp/h2
# link tmp/file3 tmp/h3
# link tmp/file3 tmp/h4
gcc ex4.c -o ex4 && ./ex4 > ex4.txt
