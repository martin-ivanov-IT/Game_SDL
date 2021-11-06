//Corresponding header
#include "include/containers/VectorHero.h"
#include "Game/Entities/Hero.h"
#include <stdlib.h>


//Other libraries headers

//Own components headers

void initVectorHero(struct VectorHero *vec, size_t initialCapacity) {
  vec->capacity = initialCapacity;
  vec->size = 0;

  if (0 != initialCapacity) {
    vec->items = malloc(sizeof(struct Hero*) * vec->capacity);
  } else {
    vec->items = NULL;
  }
}

size_t getSizeVectorHero(const struct VectorHero *v) {
  return v->size;
}

bool isEmptyVectorHero(const struct VectorHero *vec) {
  return vec->size == 0;
}

void resizeVectorHero(struct VectorHero *vec, size_t newSize) {
  //memory is still kept reserved even if the size shrinks
  if (newSize <= vec->size) {
    vec->size = newSize;
    return;
  }

  struct Hero **items = realloc(vec->items, sizeof(struct Hero*) * newSize);
  if (items) {
    vec->items = items;
    vec->capacity = newSize;
    vec->size = newSize;
  }
}

void reserveVectorHero(struct VectorHero *vec, size_t newCapacity) {
  struct Hero **items = realloc(vec->items, sizeof(struct Hero*) * newCapacity);
  if (items) {
    vec->items = items;
    vec->capacity = newCapacity;

    //shrink elements if needed
    if (newCapacity < vec->size) {
      vec->size = newCapacity;
    }
  }
}

void pushElementVectorHero(struct VectorHero *vec, struct Hero *item) {
  if (0 == vec->capacity) {
    reserveVectorHero(vec, 1);
  }
  else if (vec->capacity == vec->size) {
    reserveVectorHero(vec, vec->capacity * 2);
  }
  vec->items[vec->size] = item;
  vec->size++;
}

void setElementVectorHero(struct VectorHero *vec, size_t idx, struct Hero *item) {
  if (idx < vec->size) {
    vec->items[idx] = item;
  }
}

struct Hero* getElementVectorHero(const struct VectorHero *vec, size_t idx) {
  if (idx < vec->size) {
    return vec->items[idx];
  }
  return NULL;
}

struct Hero* backElementVectorHero(struct VectorHero *vec) {
  if (0 == vec->size) {
    return NULL;
  }

  return vec->items[vec->size - 1];
}

void deleteElementVectorHero(struct VectorHero *vec, size_t idx) {
  if (idx >= vec->size) {
    return;
  }

  vec->items[idx] = NULL;

  for (size_t i = idx; i < vec->size - 1; ++i) {
      vec->items[i] = vec->items[i + 1];
      vec->items[i + 1] = NULL;
  }

  vec->size--;
}

void popElementVectorHero(struct VectorHero *vec) {
  if (vec->size == 0) {
    return;
  }

  vec->size--;
}

void clearElementsVectorHero(struct VectorHero *vec) {
  resizeVectorHero(vec, 0);
}

void shrinkToFitVectorHero(struct VectorHero *vec) {
  if (vec->capacity >= vec->size) {
    return;
  }

  struct Hero **items = realloc(vec->items, sizeof(struct Hero*) * vec->capacity);
  if (items) {
    vec->items = items;
    vec->size = vec->capacity;
  }
}

void deepCopyVectorHero(const struct VectorHero *from, struct VectorHero *to) {
  to->size = from->size;
  to->capacity = from->capacity;
  if (NULL != from->items) {
    to->items = malloc(sizeof(struct Hero*) * from->capacity);
    for (size_t i = 0; i < to->capacity; ++i) {
      to->items[i] = from->items[i];
    }
  }
}

void freeVectorHero(struct VectorHero *vec) {
  if (vec->items != NULL) {
    free(vec->items);
    vec->items = NULL;
    vec->size = 0;
    vec->capacity = 0;
  }
}

void shallowCopyVectorHero(const struct VectorHero *from, struct VectorHero *to){
  to->size = from->size;
  to->capacity = from->capacity;to->size = from->size;
  to->items = from->items;
}
