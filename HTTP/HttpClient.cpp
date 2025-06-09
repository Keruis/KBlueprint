#include "HttpClient.h"

std::string HttpClient::get(const std::string& url) {
    char* res = http_get(url.c_str());
    std::string result = res ? std::string(res) : "";
    http_free_string(res);
    return result;
}

std::string HttpClient::post(const std::string& url, const std::string& json_body) {
    char* res = http_post(url.c_str(), json_body.c_str());
    std::string result = res ? std::string(res) : "";
    http_free_string(res);
    return result;
}

std::string HttpClient::put(const std::string& url, const std::string& json_body) {
    char* res = http_put(url.c_str(), json_body.c_str());
    std::string result = res ? std::string(res) : "";
    http_free_string(res);
    return result;
}

std::string HttpClient::del(const std::string& url) {
    char* res = http_delete(url.c_str());
    std::string result = res ? std::string(res) : "";
    http_free_string(res);
    return result;
}