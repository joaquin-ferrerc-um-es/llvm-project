#include "llvm/Transforms/Utils/ConditionalBranch.h"

using namespace llvm;

PreservedAnalyses ConditionalBranchPass::run(Function &F, FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  for (Instruction &I : instructions(F)) {
    if (I.isTerminator()) {
      if (strcmp(I.getOperand(0)->getName().str().c_str(), "cmp") == 0)
        if (CmpInst *cp = dyn_cast<CmpInst>(I.getPrevNode()))
          errs() << cp->getPredicate() << '\n';
    }
  }
  return PreservedAnalyses::all();
}

