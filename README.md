# cpp_server

This code is using the library `https://github.com/eidheim/Simple-Web-Server`. 
You don't need to install anything because I copied the required file in `lib` folder.

### Compilation 
`g++ -std=c++11 server.cpp -o server`

### Running
`./server`

At this point, you should open your browser with the address `http://localhost:8080/index.html`. 
In case you want to test the server, this id the address `http://localhost:8080/query?text=mytext`
