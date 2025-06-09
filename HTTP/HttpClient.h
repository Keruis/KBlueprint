#ifndef BLUEPRINT_HTTPCLIENT_H
#define BLUEPRINT_HTTPCLIENT_H

#include <string>

extern "C" {
    char* http_get(const char* url);
    char* http_post(const char* url, const char* body);
    char* http_put(const char* url, const char* body);
    char* http_delete(const char* url);
    void http_free_string(char* s);
}

class HttpClient {
public:
    HttpClient() = default;
    ~HttpClient() = default;

    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& json_body);
    std::string put(const std::string& url, const std::string& json_body);
    std::string del(const std::string& url);
};

#endif //BLUEPRINT_HTTPCLIENT_H