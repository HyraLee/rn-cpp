#ifndef V99CORE_H
#define V99CORE_H
#include "curl/curl.h"
#include <string.h>
#include <iostream>

namespace v99core
{
  long multiply(long a, long b);
  size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userptr);
  std::string httpGet(std::string url);
}

#endif /* V99CORE_H */
