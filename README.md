Lab 1 : Socket Programming 

Khushal Damor (B21AI018)

1) server1.cpp

A single-process math server that can handle only one client at a time.

Steps to compile :

g++ server1.cpp -o server1
./server1 8080

2) server2.cpp

A multi-process math server that can handle multiple clients at a time.

Steps to compile :

g++ server2.cpp -o server2
./server2 8080

3) client.cpp

A client program that can chat with the math server.

Steps to compile :

g++ client.cpp -o client
./client 127.0.0.1 8080

Note :

(i) The above-mentioned programs can be terminated with CTRL+C.
(ii) The server program must be executed before executing the client program.
(iii) Link of the video in which i've showcased the assignment : https://www.youtube.com/watch?v=8J1KEMWMXws