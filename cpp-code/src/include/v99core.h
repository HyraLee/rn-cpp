#ifndef V99CORE_H
#define V99CORE_H
#include "curl/curl.h"
#include <string.h>
#include <iostream>

namespace v99core
{
  ////////////////////////////////////////////////////
  //////////          UTILITIES         /////////////
  ////////////////////////////////////////////////////
  const std::string ERR_REQUEST_CANCELLED = "REQUEST_CANCELLED!";
  std::atomic<bool> cancelRequested(false);
  long multiply(long a, long b);
  size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userptr);
  struct curl_slist *headers = NULL;
  ////////////////////////////////////////////////////
  //////////          HTTP REQUEST         ///////////
  ////////////////////////////////////////////////////
  std::string httpGet(std::string url);
  std::string httpPost(std::string url, std::string params);
  std::string httpDelete(std::string url);
  bool setHeader(std::string headerOption);
  bool cancelHttpRequest();
  bool openHttpRequest();
  ////////////////////////////////////////////////////
  //////////             CORE V99    ///////////
  ////////////////////////////////////////////////////
  bool init(const std::string &appId, const std::string &secretKey);
  void on(const std::string &appId);
  void exec(const std::string &redId, const std::string &actionType);
  std::string getPlatform();
}

#endif /* V99CORE_H */
