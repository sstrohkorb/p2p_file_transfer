client: error.c send_recieve.c  client01.c
	gcc -std=c11 -Wall error.c send_recieve.c client01.c -o client
	
server: error.c send_recieve.c server01.c
	gcc -std=c11 -Wall error.c send_recieve.c server01.c  -o server
	
client_swig: client_p.c error.c send_recieve.c client.i
	swig -python client.i
	gcc -c -fpic `python-config --includes` client_p.c error.c send_recieve.c client_wrap.c
	gcc -shared client_p.o client_wrap.o -o_client.so
	
server_swig: server_p.c error.c send_recieve.c server.i
	swig -python server.i
	gcc -c -fpic `python-config --includes` server_p.c error.c send_recieve.c server_wrap.c
	gcc -shared server_p.o server_wrap.o -o_server.so
	
clean: 
	rm -f *~ client server
	
clean_swig:
	rm -f *~ *.o *.so server.py client.py server.pyc client.pyc server_wrap.c client_wrap.c
	

FILES = client01.c  error.c  send_recieve.c  serv_cli.h  server01.c 
