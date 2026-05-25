#include <curl/curl.h>
#include <string>
#include <cstddef>
#include <json.hpp>
#include "Datatypes.hpp"




class Tasks
{
private:

private:
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
public:

nlohmann::json fetchStock(IncomingData sIncomingData);


};