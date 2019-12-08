#ifndef WORKFLOW_MODEL_BUILDER_H_
#define WORKFLOW_MODEL_BUILDER_H_

#include <memory>
#include <mutex>

#include "components/poker/entities/game_model_def.h"
#include "components/poker/entities/workflow_model_def.h"

namespace poker {

/// High level poker workflow. Instantiated from WorkflowSessionThread
class WorkflowModelBuilder {
 public:
  explicit WorkflowModelBuilder(const GameModel& gameModel);

  void HandleGameModelChange(const GameModel& gameModel);

  WorkflowModel GetModel() const;

 private:
  int FindActiveOpponents(const GameModel& game_model) const;
  WorkflowState FindCurrentState(const GameModel& game_model) const;

  WorkflowModel workflow_model_;
};

}  // namespace poker

#endif  // WORKFLOW_MODEL_BUILDER_H_
