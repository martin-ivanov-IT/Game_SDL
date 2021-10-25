#ifndef UTILS_CONTAINERS_VECTORINT_H_
#define UTILS_CONTAINERS_VECTORINT_H_

// C system headers
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


// Other libraries headers

// Own components headers

// Forward declarations

struct VectorInt {
  int32_t **integers;
  size_t capacity;
  size_t size;
};

void initVectorInt(struct VectorInt *vec, size_t initialCapacity);
size_t getSizeVectorInt(const struct VectorInt *vec);
bool isEmptyVectorInt(const struct VectorInt *vec);
void resizeVectorInt(struct VectorInt *vec, size_t newSize);
void reserveVectorInt(struct VectorInt *vec, size_t newCapacity);
void pushElementVectorInt(struct VectorInt *vec, int32_t *elem);
void setElementVectorInt(struct VectorInt *vec, size_t idx, int32_t *elem);
int32_t* getElementVectorInt(const struct VectorInt *vec, size_t idx);
int32_t* backElementVectorInt(struct VectorInt *vec);
void deleteElementVectorInt(struct VectorInt *vec, size_t idx);
void popElementVectorInt(struct VectorInt *vec);
void clearElementsVectorInt(struct VectorInt *vec);
void shrinkToFitVectorInt(struct VectorInt *vec);
void deepCopyVectorInt(const struct VectorInt *from, struct VectorInt *to);
void freeVectorInt(struct VectorInt *vec);

#endif /* UTILS_CONTAINERS_VECTOR_H_ */

