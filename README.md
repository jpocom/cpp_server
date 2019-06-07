# cpp_server

This code is using the library `https://github.com/eidheim/Simple-Web-Server`. 
This library is copied in `lib` folder.
However, you have to still the boost library, specially the `asia` component. 
If you are using a mac with hombrew you can do it by running: 
`brew install boost`

### Compilation 
`g++ -std=c++11 server.cpp -o server -I/usr/local/include`

### Running
`./server`

At this point, you should open your browser with the address `http://localhost:8080/index.html`. 
In case you want to test the server, this id the address `http://localhost:8080/query?text=mytext`
