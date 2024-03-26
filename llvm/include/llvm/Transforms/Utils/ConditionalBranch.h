#ifndef LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H
#define LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class ConditionalBranchPass : public PassInfoMixin<ConditionalBranchPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_CONDITIONALBRANCH_H