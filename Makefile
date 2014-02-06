assgn1: assgn1.o log.o
	gcc assgn1.o log.o -o assgn1

job: job.o log.o
	gcc job.o log.o -o job

job.o: job.c
	gcc -c job.c
assgn1.o: assgn1.c
	gcc -c assgn1.c
log.o: log.c
	gcc -c log.c

clean: rm -rf *.o assgn1
