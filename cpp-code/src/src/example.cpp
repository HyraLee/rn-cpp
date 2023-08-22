#include "example.h"
#include <iostream>
#include <string>

namespace example
{
	long multiply(long a, long b)
	{
		return a * b;
	}

	size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userptr)
	{
		((std::string *)userptr)->append((char *)contents, size * nmemb);
		return size * nmemb;
	}

	std::string httpGet(std::string url, std::string caPath)
	{
		CURL *curl = curl_easy_init();
		std::string response = "";
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_CAINFO, caPath.c_str());
			curl_easy_setopt(curl, CURLOPT_PROTOCOLS,
							 CURLPROTO_HTTP | CURLPROTO_HTTPS);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "curl_easy_perform() failed: "
						  << curl_easy_strerror(res) << std::endl;
			}
			else
			{
				std::cout << "Response:\n"
						  << response << std::endl;
			}
			return response;
		}
		return "";
	}
}
