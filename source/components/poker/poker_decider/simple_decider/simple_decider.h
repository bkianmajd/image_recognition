#ifndef SIMPLE_DECIDER_H_
#define SIMPLE_DECIDER_H_

#include "components/poker/poker_decider/poker_decider_interface.h"
#include "components/poker/statistics/hand_calculator/hand_calculator.h"

namespace poker {

class SimpleDecider : public PokerDeciderInterface {
 public:
  SimpleDecider();
  ~SimpleDecider() override = default;

  Decision Deicide(const WorkflowModel& workflow_model) override {
    Decision decision;
    decision.decisionType = DecisionType::DEC_CHECK_FOLD;

    if (workflow_model.player_hand.FirstCard().suit == SUIT_HIDDEN) {
      return decision;
    }
    if (workflow_model.player_hand.SecondCard().suit == SUIT_HIDDEN) {
      return decision;
    }

    Table table(workflow_model.dealer_cards[0], workflow_model.dealer_cards[1],
                workflow_model.dealer_cards[2], workflow_model.dealer_cards[3],
                workflow_model.dealer_cards[4]);
    statistics::HandStatistic handStatistic =
        hand_calculator_.CalculateHandProbability(
            workflow_model.player_hand, table,
            workflow_model.number_of_active_opponents);

    std::cout << "tie probability: " << handStatistic.tie_probability
              << std::endl;
    std::cout << "losing probability: " << handStatistic.losing_probability
              << std::endl;
    return decision;
  }

 private:
  statistics::HandCalculator hand_calculator_;
};

}  // namespace poker

#endif  // SIMPLE_DECIDER_H_
