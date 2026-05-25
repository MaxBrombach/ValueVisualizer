#include "Tasks.hpp"


// Callback to store the HTTP response in a std::string
size_t Tasks::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

nlohmann::json Tasks::fetchStock(IncomingData sIncomingData)
{    
    std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/"  + sIncomingData.strStockticker + "?interval=" + sIncomingData.strGranularity + "&range="+ sIncomingData.strRange;
    nlohmann::json jsonresponse;
    CURL* curl = curl_easy_init();
    std::string response;
    

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res= curl_easy_perform(curl);

        if (res != CURLE_OK) {
           // std::cerr << "curl error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        jsonresponse = nlohmann::json::parse(response);
    
    }
    return jsonresponse;

}

