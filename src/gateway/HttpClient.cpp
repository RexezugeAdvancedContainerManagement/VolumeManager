#include "HttpClient.hpp"
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *s) {
  size_t newLength = size * nmemb;
  try {
    s->append((char *)contents, newLength);
  } catch (std::bad_alloc &e) {
    return 0;
  }
  return newLength;
}

std::string HttpClient::sendRequest(const std::string &url,
                                    const std::string &method) const {
  CURL *curl;
  CURLcode res;
  std::string response;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    if (method == "POST") {
      curl_easy_setopt(curl, CURLOPT_POST, 1L);
    }

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
  }
  return response;
}
