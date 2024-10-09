my program contains two folders, one client and one server

in the client folder there is client.cpp and Makefile

to run client.cpp call make this will create client.o
	then call ./client [hostname] [portNumber]
			for my testing i used csci-gnode-03 and 9003 respectivly.
	after it will display a message for instruction on how to exit and input a string to be reversed. 
	it will then print the reverse of the message typed in.

	call ./client [hostname] [portNumber] again for further input as the server remains active.

	once fin is typed the server will close and nif will be displayed to user
	
	


in the server folder there is server.cpp and Makefile

to run server.cpp call make, this will create server.o
	then call ./server followed by a port number, for my testing i used 9003
	it will then wait for commands from the client side.
	once input reaches the server it will show the input.
	once fin reaches the server it will reverse it, send reversed string back and then close the server. 


--------------------------------------------------------------------------------------------------------------------
I tested my program on the csegrid on my desktop running windows 10 pro version 21H2, wrote the program in notepad++
	