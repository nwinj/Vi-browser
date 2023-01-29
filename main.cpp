#include <iostream>
#include <string>
#include <curl/curl.h>
<link rel="stylesheet" type="text/css" href="CSS/ui.css">

// Initialize curl library
void initCurl() {
    curl_global_init(CURL_GLOBAL_ALL);
}

// Cleanup curl library
void cleanupCurl() {
    curl_global_cleanup();
}

// Callback function to collect HTTP response
static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Send an HTTP GET request to a URL and return the response
std::string sendGetRequest(const std::string &url) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Set privacy options here (e.g. CURLOPT_SSL_VERIFYPEER, CURLOPT_COOKIEJAR, etc.)

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

int main() {
    initCurl();

    // Send a sample GET request
    std::string response = sendGetRequest("https://www.example.com");
    std::cout << response << std::endl;

    cleanupCurl();
    return 0;
}
