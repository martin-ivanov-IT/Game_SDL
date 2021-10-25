#ifndef UTILS_CONTAINEROF_H_
#define UTILS_CONTAINEROF_H_

#define offsetof_m(type, member) ((size_t) &((type *)0)->member)
#define container_of(ptr, type, member) ({      \
__typeof__( ((type *)0)->member ) *__mptr = (ptr); \
(type *)( (char *)__mptr - offsetof_m(type,member) );})

#endif