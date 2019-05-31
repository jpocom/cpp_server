#include "lib/server_http.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {
    // HTTP-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpServer server;
    server.config.port = 8080;
  
    // GET-example for the path /query?text={text}
    // Responds with request-information
    server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        stringstream stream;
        auto query_fields = request->parse_query_string();
        auto it = query_fields.find("text"); 
        if (it != query_fields.end()) { 
            // WRITE YOUR CODE HERE
          stream 
              << "{"
              << "  \"your_text\": \"" << it->second << "\""
              << "}";
        } else {
            stream << "Empty text: " << it->second << endl; 
        }
        response->write(stream);
    };
  
    // GET-example for the path /query?text={text}
    // Responds with request-information
    server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        auto path = "./web/"+request->path;

        SimpleWeb::CaseInsensitiveMultimap header;

        std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate);
        auto length = ifs.tellg();
        ifs.seekg(0, ios::beg);
        stringstream stream;
        stream << ifs.rdbuf();

        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length);
    };

    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
    };

    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));
  
    server_thread.join();
}