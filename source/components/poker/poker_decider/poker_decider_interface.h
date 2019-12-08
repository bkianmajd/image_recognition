#ifndef POKER_DECIDER_INTERFACE_H_
#define POKER_DECIDER_INTERFACE_H_

#include "components/poker/entities/workflow_model_def.h"

namespace poker {

enum DecisionType {
  DEC_UNKNOWN,
  DEC_FOLD,
  DEC_CHECK_FOLD,
  DEC_CHECK,
  DEC_CALL,
  DEC_RAISE,
};

struct Decision {
  DecisionType decisionType;
  double ammount = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Decision& decision) {
  switch (decision.decisionType) {
    case DecisionType::DEC_UNKNOWN:
      os << "Unknown";
      break;
    case DecisionType::DEC_FOLD:
      os << "Fold";
      break;
    case DecisionType::DEC_CHECK_FOLD:
      os << "Check Fold";
      break;
    case DecisionType::DEC_CHECK:
      os << "Check";
      break;
    case DecisionType::DEC_CALL:
      os << "Call";
      break;
    case DecisionType::DEC_RAISE:
      os << "Raise " << decision.ammount;
      break;
  }
  return os;
}

// High level API to decide what to do each hand
class PokerDeciderInterface {
 public:
  virtual ~PokerDeciderInterface() {}

  virtual Decision Deicide(const WorkflowModel& workflow_model) = 0;
};

}  // namespace poker

#endif  // POKER_DECIDER_INTERFACE_H_
