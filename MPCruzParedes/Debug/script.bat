nasm -f win64 mp2.asm
gcc -c mp2c.c -o mp2c.obj -m64
gcc mp2c.obj mp2.obj -o mp2c.exe -m64
mp2c.exe
