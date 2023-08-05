#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc,char* argv[]){

	char* server_IP = argv[1];
	int server_port = atoi(argv[2]);

	// Creating the client socket

	int client = socket(AF_INET,SOCK_STREAM,0); 

	// Storing the server address and port

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	inet_pton(AF_INET,server_IP,&server_address.sin_addr);

	// Connecting to the server

	int connection = connect(client,(struct sockaddr*)&server_address,sizeof(server_address));

	cout << endl;

	// If connection to server fails, then show an error message

	if (connection<0){

		cerr << "Error while connecting to the server" << endl;
		cout << endl;
		exit(1);

	}

	cout << "Connected to server" << endl;
	cout << endl;

	do{

		cout << "Enter the query to the server : ";

		// Take the 'string' input from the user

		string input;
		getline(cin, input);

		// Convert the 'string' input to 'const char*' input_query 

		const char* input_query = input.c_str();

		// Send query to the server

		send(client,input_query,strlen(input_query),0);

		// Receive reply from the server

		char buffer[1024] = {0};
		read(client,buffer,1024);

		cout << "Server replied : " << buffer << endl;
		cout << endl;

	} while(1);

	// Close the client socket

	close(client);

	return 0;

}
