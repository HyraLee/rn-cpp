#ifndef EXAMPLE_H
#define EXAMPLE_H
#include "curl/curl.h"
#include <string.h>
#include <iostream>

namespace example
{
  long multiply(long a, long b);
  size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userptr);
  std::string httpGet(std::string url);
}

#endif /* EXAMPLE_H */
