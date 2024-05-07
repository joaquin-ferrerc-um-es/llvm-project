#ifndef LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H
#define LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstrTypes.h"
#include <set>
#include <map>
#include <cmath>

#define STAT_SIZE 11

namespace llvm {

class ConditionalBranchPass : public PassInfoMixin<ConditionalBranchPass> {
private:
  std::map<Instruction*, std::set<Value*>> conditionalBranches;

  std::set<Value*> getDependencies(Value *v, std::set<Value*> prevDeps);

public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
  int correlationStats[STAT_SIZE] = {0};
  int meanCorrelation = 0;
  int totalBranches = 0;
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H