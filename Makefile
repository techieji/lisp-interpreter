build:
	gcc main.c parse.c exec.c env.c stl.c utils.c -Os -Wall

debug:
	gcc main.c parse.c exec.c env.c stl.c utils.c -Os -Wall -g
	gdb ./a.out -ex=r --silent
