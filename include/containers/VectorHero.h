#ifndef CONTAINERS_VECTORHEROHero
#define CONTAINERS_VECTORHEROHero


#include <stddef.h>
#include <stdbool.h>

struct Hero;

struct VectorHero {
  struct Hero **items;
  size_t capacity;
  size_t size;
};

void initVectorHero(struct VectorHero *vec, size_t initialCapacity);
size_t getSizeVectorHero(const struct VectorHero *vec);
bool isEmptyVectorHero(const struct VectorHero *vec);
void resizeVectorHero(struct VectorHero *vec, size_t newSize);
void reserveVectorHero(struct VectorHero *vec, size_t newCapacity);
void pushElementVectorHero(struct VectorHero *vec, struct Hero* elem);
void setElementVectorHero(struct VectorHero *vec, size_t idx, struct Hero* elem);
struct Hero* getElementVectorHero(const struct VectorHero *vec, size_t idx);
struct Hero* backElementVectorHero(struct VectorHero *vec);
void deleteElementVectorHero(struct VectorHero *vec, size_t idx);
void popElementVectorHero(struct VectorHero *vec);
void clearElementsVectorHero(struct VectorHero *vec);
void shrinkToFitVectorHero(struct VectorHero *vec);
void shallowCopyVectorHero(const struct VectorHero *from, struct VectorHero *to);
void deepCopyVectorHero(const struct VectorHero *from, struct VectorHero *to);
void freeVectorHero(struct VectorHero *vec);

#endif 