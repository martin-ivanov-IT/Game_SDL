//Corresponding header
#include "utils/containers/VectorInt.h"

//C system headers
#include <stdlib.h>

//Other libraries headers

//Own components headers

void initVectorInt(struct VectorInt *vec, size_t initialCapacity) {
  vec->capacity = initialCapacity;
  vec->size = 0;

  if (0 != initialCapacity) {
    vec->integers = malloc(sizeof(int32_t*) * vec->capacity);
  } else {
    vec->integers = NULL;
  }
}

size_t getSizeVectorInt(const struct VectorInt *v) {
  return v->size;
}

bool isEmptyVectorInt(const struct VectorInt *vec) {
  return vec->size == 0;
}

void resizeVectorInt(struct VectorInt *vec, size_t newSize) {
  //memory is still kept reserved even if the size shrinks
  if (newSize <= vec->size) {
    vec->size = newSize;
    return;
  }

  int32_t **integers = realloc(vec->integers, sizeof(int32_t*) * newSize);
  if (integers) {
    vec->integers = integers;
    vec->capacity = newSize;
    vec->size = newSize;
  }
}

void reserveVectorInt(struct VectorInt *vec, size_t newCapacity) {
  int32_t **integers = realloc(vec->integers, sizeof(int32_t*) * newCapacity);
  if (integers) {
    vec->integers = integers;
    vec->capacity = newCapacity;

    //shrink elements if needed
    if (newCapacity < vec->size) {
      vec->size = newCapacity;
    }
  }
}

void pushElementVectorInt(struct VectorInt *vec, int32_t* item) {
  if (0 == vec->capacity) {
    reserveVectorInt(vec, 1);
  }
  else if (vec->capacity == vec->size) {
    reserveVectorInt(vec, vec->capacity * 2);
  }
  vec->integers[vec->size] = item;
  vec->size++;
}

void setElementVectorInt(struct VectorInt *vec, size_t idx, int32_t* item) {
  if (idx < vec->size) {
    vec->integers[idx] = item;
  }
}

int32_t* getElementVectorInt(const struct VectorInt *vec, size_t idx) {
  if (idx < vec->size) {
    return vec->integers[idx];
  }
  return NULL;
}

int32_t* backElementVectorInt(struct VectorInt *vec) {
  if (0 == vec->size) {
    return NULL;
  }

  return vec->integers[vec->size - 1];
}

void deleteElementVectorInt(struct VectorInt *vec, size_t idx) {
  if (idx >= vec->size) {
    return;
  }

  vec->integers[idx] = NULL;

  for (size_t i = idx; i < vec->size - 1; ++i) {
      vec->integers[i] = vec->integers[i + 1];
      vec->integers[i + 1] = NULL;
  }

  vec->size--;
}

void popElementVectorInt(struct VectorInt *vec) {
  if (vec->size == 0) {
    return;
  }

  vec->size--;
}

void clearElementsVectorInt(struct VectorInt *vec) {
  resizeVectorInt(vec, 0);
}

void shrinkToFitVectorInt(struct VectorInt *vec) {
  if (vec->capacity >= vec->size) {
    return;
  }

  int32_t **integers = realloc(vec->integers, sizeof(int32_t*) * vec->capacity);
  if (integers) {
    vec->integers = integers;
    vec->size = vec->capacity;
  }
}

void deepCopyVectorInt(const struct VectorInt *from, struct VectorInt *to) {
  to->size = from->size;
  to->capacity = from->capacity;
  if (NULL != from->integers) {
    to->integers = malloc(sizeof(int32_t*) * from->capacity);
    for (size_t i = 0; i < to->capacity; ++i) {
      to->integers[i] = from->integers[i];
    }
  }
}

void freeVectorInt(struct VectorInt *vec) {
  if (vec->integers != NULL) {
    free(vec->integers);
    vec->integers = NULL;
    vec->size = 0;
    vec->capacity = 0;
  }
}

