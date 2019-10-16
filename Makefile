
all: overflow format1 format2 format3 env tocttou

sploits: sploit_overflow sploit_format1 sploit_env sploit_tocttou

sploit_overflow: sploit_overflow.c
		gcc -fno-stack-protector -ggdb -z execstack -o sploit_overflow sploit_overflow.c

sploit_format1: sploit_format1.c
		gcc -Wno-format-security -ggdb -o sploit_format1 sploit_format1.c

sploit_env: sploit_env.c
		gcc -ggdb -o sploit_env sploit_env.c

sploit_tocttou: sploit_tocttou.c
		gcc -ggdb -o sploit_tocttou sploit_tocttou.c

overflow: overflow.c
		gcc -fno-stack-protector -ggdb -z execstack -o overflow overflow.c

format1: format1.c
		gcc -Wno-format-security -ggdb -o format1 format1.c

format2: format2.c
		gcc -Wno-format-security -ggdb -o format2 format2.c

format3: format3.c
		gcc -Wno-format-security -ggdb -o format3 format3.c

env: env.c
	gcc -ggdb -o env env.c

tocttou: tocttou.c
	gcc -ggdb -o tocttou tocttou.c

clean:
	rm -f overflow format1 format2 format3 env tocttou sploit_overflow sploit_format1 sploit_format2 sploit_format3 sploit_env sploit_tocttou

