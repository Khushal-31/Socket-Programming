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

float getResult(string str){

    // Creating a 'stringstream' object ss

    stringstream ss;

    // Adding the 'string' str to the 'stringstream' ss
    
    ss << str;
    
    // Creating a 'float vector' to store the operands

    vector< float > operands;
    
    // Creating a 'char vector' to store the operators
    
    vector< char > operators;

    string temp;

    float number;
    
    while (!ss.eof()) {

        ss >> temp;

        if (stringstream(temp) >> number){

        	// Pushing the operand into the 'vector' operands

            operands.push_back(number); 

        }

        if ((temp == "+") or (temp == "-") or (temp == "*") or (temp == "/")){
        
        	// Pushing the operator into the 'vector' operators
        
        	const char* temp_char = temp.c_str();

        	operators.push_back(*temp_char);

        }

    }
    
    // Extracting the 1st operand from the 'vector' operators

    float x = operands[0];
    
    // Extracting the 2nd operand from the 'vector' operators
    
    float y = operands[1];
    
    // Creating a 'float' object answer to store the result of the operation

    float answer;

    // Performing the required operation based on the operator stored in the 'vector' operators

    if (operators[0] == '+'){

		answer = x + y;

	}

	else if (operators[0] == '-'){

		answer = x - y;

	}

	else if (operators[0] == '*'){

		answer = x * y;

	}

	else if (operators[0] == '/'){

		answer = x / y;

	}

    return answer;

}

int main(int argc,char* argv[]){

	cout << endl;
	cout << "Math Server Running" << endl;
	cout << endl;

	while(1){
	
		int server_port = atoi(argv[1]);

		// Creating the server socket

		int server = socket(AF_INET,SOCK_STREAM,0); 

		// Storing the server address and port

		struct sockaddr_in server_address;

		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(server_port);
		server_address.sin_addr.s_addr = INADDR_ANY;

		// Bind the socket to the server address and port

		bind(server,(struct sockaddr*)&server_address,sizeof(server_address));

		// Listen for incoming connections

		listen(server,1);

		cout << endl;

		// Accept incoming connections

		int client;

		struct sockaddr_in client_address;
		socklen_t addrlen = sizeof(client_address);
		client = accept(server,(struct sockaddr*)&client_address,&addrlen);

		cout << "Connected with client number (" << client << ")" << endl;
		cout << endl;

		// Close the server socket

		close(server);

		do{

			// Receive query from the client

			char buffer[1024] = {0};
			read(client,buffer,1024);

			// If buffer has null character, then client has disconnected. Therefore, terminate the loop.

			if (buffer[0]=='\0'){   

				cout << "Client number (" << client << ") has disconnected" << endl;
				cout << endl;
				break;

		    }

			cout << "Client number (" << client << ") sent query : " << buffer << endl;

			// Converting 'char' buffer to 'string' str_buffer

			string str_buffer = buffer;

			// Getting the result of the query

			float answer = getResult(str_buffer);

			cout << "Sending reply to client number ("<< client <<") : "<< answer << endl;

			// Converting 'float' result to 'const char*' reply 

			string temp_c = to_string(answer);
			const char* reply = temp_c.c_str();

			// Send reply to the client

			send(client,reply,strlen(reply),0);

			cout << endl;

		} while(1);

		// Close the client socket

		close(client);

	}

	return 0;

}
