#include "llvm/Transforms/Utils/ConditionalBranch.h"

using namespace llvm;

PreservedAnalyses ConditionalBranchPass::run(Function &F, FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  for (Instruction &I : instructions(F)) {
    if (I.isTerminator()) {
      if (strcmp(I.getOpcodeName(), "br") == 0)
        if (CmpInst *cp = dyn_cast<CmpInst>(I.getPrevNode())) {
          errs() << cp->getPredicate() << '\n';
          for (unsigned int i = 0; i < cp->getNumOperands(); i++) {
            Value *v = cp->getOperand(i);
            if (strchr(v->getNameOrAsOperand().c_str(), '%'))
              errs () << v->getNameOrAsOperand() << "\n";
          }
        }
    }
  }
  return PreservedAnalyses::all();
}

