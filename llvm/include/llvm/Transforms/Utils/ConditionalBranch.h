#ifndef LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H
#define LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstrTypes.h"
#include <set>
#include <map>

namespace llvm {

class ConditionalBranchPass : public PassInfoMixin<ConditionalBranchPass> {
private:
  std::map<Instruction*, std::set<Value*>> conditionalBranches;

  std::set<Value*> getDependencies(Value *v);

public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H