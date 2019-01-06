#ifndef HELPERS_COMPARE_H_
#define HELPERS_COMPARE_H_

namespace helpers {

inline bool CompareEpsilon(float val1, float val2, float epsilon) {
  if (val1 - val2 < epsilon && val2 - val1 < epsilon) {
    return true;
  }
  return false;
}

}  // namespace helpers

#endif  // HELPERS_COMPARE_H_
