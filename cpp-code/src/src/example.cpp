#include "example.h"

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

	std::string httpGet(std::string url)
	{
		CURL *curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_DEFAULT);

		curl = curl_easy_init();
		if (curl)
		{
			std::string response;

			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			res = curl_easy_perform(curl);
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

			curl_easy_cleanup(curl);
			curl_global_cleanup();

			return response;
		}

		curl_global_cleanup();
		return "Response!!!";
	}
}
