#include "unp.h"

int inet_pton_loose(int family, const char *strptr, void *addrptr) {
  int status;
  if ((status = inet_pton(family, strptr, addrptr)) < 0) return status;
  if (status == 0 && (status = inet_aton(strptr, addrptr)) <= 0) return status;
  return 1;
}
