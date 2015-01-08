54.173.57.151

-created a server (ip 54.173.57.151 on Amazon ec2)
-programed a client in C that connects to the server
	-then communicates with the server
-starting the program
	-command line: type in make
		-then ./nsl 8.8.8.8 www.google.com 
			-for www.google.com
		-./nsl -t CNAME 8.8.8.8 www.google.com
		-./nsl -t NS 8.8.8.8 www.google.com
		-./nsl -t txt 8.8.8.8 www.google.com
-Could also do ./nsl 54.173.57.151 cs3357.fake 
	-this might not work because at the time server will most likely be down
