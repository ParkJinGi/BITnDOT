# Help
How_To_Use:
	echo "\n\n\n모듈을 사용할 때 : make M\n\n모듈을 사용하지 않을 때 : make T\n\n모듈을 테스트할 때 : make C\n\n"
# Not using Modules
T: 
	gcc main.c
	./a.out
# To using Modules
M:
	sudo gcc main.c -D "FOR_MODULE=1" -lwiringPi
	sudo ./a.out
# check Modules
C:
	sudo gcc main.c -D "FOR_MODULE=1" -D "CHECK=1" -lwiringPi
	sudo ./a.out
