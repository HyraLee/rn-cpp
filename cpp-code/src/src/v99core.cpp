#include "v99core.h"
#include "certificate.h"
#include "curl/curl.h"
#include "openssl/err.h"
#include "openssl/ssl.h"
#include <iostream>
#include <string>

namespace v99core
{
	std::atomic<bool> cancelRequest(false);

	// Function to cancel the HTTP request
	void CancelHttpRequest()
	{
		cancelRequest.store(true);
	}

	long multiply(long a, long b)
	{
		return a * b;
	}

	size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userptr)
	{
		((std::string *)userptr)->append((char *)contents, size * nmemb);
		return size * nmemb;
	}

	static CURLcode sslctx_function(CURL *curl, void *sslctx, void *parm)
	{
		CURLcode rv = CURLE_ABORTED_BY_CALLBACK;

		/** This example uses two (fake) certificates **/
		BIO *cbio = BIO_new_mem_buf(pem_from_haxx_se, sizeof(pem_from_haxx_se));
		X509_STORE *cts = SSL_CTX_get_cert_store((SSL_CTX *)sslctx);
		int i;
		STACK_OF(X509_INFO) * inf;
		(void)curl;
		(void)parm;

		if (!cts || !cbio)
		{
			return rv;
		}

		inf = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

		if (!inf)
		{
			BIO_free(cbio);
			return rv;
		}

		for (i = 0; i < sk_X509_INFO_num(inf); i++)
		{
			X509_INFO *itmp = sk_X509_INFO_value(inf, i);
			if (itmp->x509)
			{
				X509_STORE_add_cert(cts, itmp->x509);
			}
			if (itmp->crl)
			{
				X509_STORE_add_crl(cts, itmp->crl);
			}
		}

		sk_X509_INFO_pop_free(inf, X509_INFO_free);
		BIO_free(cbio);

		rv = CURLE_OK;
		return rv;
	}

	std::string httpGet(std::string url)
	{
		CURL *curl = curl_easy_init();
		std::string response = "";
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
			curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, *sslctx_function);

			curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
			curl_easy_setopt(curl, CURLOPT_CAPATH, NULL);

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "HTTP GET: curl_easy_perform() failed: "
						  << curl_easy_strerror(res) << std::endl;
			}
			else
			{
				std::cout << "HTTP GET: curl_easy_perform() success!!!"
						  << std::endl;
			}
			return response;
		}
		return "";
	}

	std::string httpPost(std::string url, std::string params)
	{
		CURL *curl = curl_easy_init();
		std::string response = "";

		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
			curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, *sslctx_function);

			curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
			curl_easy_setopt(curl, CURLOPT_CAPATH, NULL);

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "HTTP GET: curl_easy_perform() failed: "
						  << curl_easy_strerror(res) << std::endl;
			}
			else
			{
				std::cout << "HTTP GET: curl_easy_perform() success!!!"
						  << std::endl;
			}
			return response;
		}
		return response;
	}

	std::string httpDelete(std::string url)
	{
		CURL *curl = curl_easy_init();
		std::string response = "";

		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

			curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
			curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, *sslctx_function);

			curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
			curl_easy_setopt(curl, CURLOPT_CAPATH, NULL);

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "HTTP GET: curl_easy_perform() failed: "
						  << curl_easy_strerror(res) << std::endl;
			}
			else
			{
				std::cout << "HTTP GET: curl_easy_perform() success!!!"
						  << std::endl;
			}
			return response;
		}
		return response;
	}

	std::string getPlatform()
	{
#if defined(TARGET_OS_IOS)
		return "iOS";
#endif
#if defined(__ANDROID__)
		return "Android";
#endif
		return "iOS";
	}
}