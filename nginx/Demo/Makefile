CC=g++

.PHONY:test deploy clean reload spawn full-deploy

test:test/test_scanner test/test_reflection

test/test_scanner:test/test_scanner.cpp stringutils.o scanner.o 
	${CC} test/test_scanner.cpp scanner.o stringutils.o -o test/test_scanner

test/test_reflection:test/test_reflection.cpp classfactory.h classfactory.o
	${CC} test/test_reflection.cpp classfactory.o -o test/test_reflection

classfactory.o:classfactory.h classfactory.cpp
	${CC} -c classfactory.cpp -o classfactory.o

stringutils.o:stringutils.h stringutils.cpp
	${CC} -c stringutils.cpp -o stringutils.o

scanner:scanner.h scanner.cpp stringutils.o
	${CC} -c scanner.cpp -o scanner.o

pipe:pipe.h pipe.cpp os.h
	${CC} -c pipe.cpp -o pipe.o

urlparse:urlparse.h urlparse.cpp
	${CC} -c urlparse.cpp -o urlparse.o

demo:main.cpp urlparse pipe 
	${CC} main.cpp urlparse.o pipe.o -o demo -I./ -L/usr/local/lib -lfcgi -Wl,-R /usr/local/lib -ljsonlib

deploy:clean demo
	sh script/kill.sh
	/usr/local/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 9000 -C 25 -f /usr/local/nginx/Demo/demo
	sh script/reload.sh
clean:
	find . -type f | sed -n '/~/p' | xargs -i rm -f {}
	rm -f demo
	rm -f *.o
reload:
	sh script/reload.sh

spawn:
	/usr/local/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 9000 -C 25 -f /usr/local/nginx/Demo/demo

full-deploy:
	sh script/start.sh
	/usr/local/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 9000 -C 25 -f /usr/local/nginx/Demo/demo
	sh script/reload.sh
