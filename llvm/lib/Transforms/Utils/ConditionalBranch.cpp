#include "llvm/Transforms/Utils/ConditionalBranch.h"

using namespace llvm;

std::set<Value*> ConditionalBranchPass::getDependencies(Value *v) {
  std::set<Value*> deps;

  if (isa<Instruction>(v)) {
    Instruction *I = cast<Instruction>(v);
    for (unsigned int i = 0; i < I->getNumOperands(); i++) {
      Value *v2 = I->getOperand(i);
      if (strchr(v2->getNameOrAsOperand().c_str(), '%')) {
        // errs () << v2->getNameOrAsOperand() << "\n";
        deps.insert(v2);
        std::set<Value*> aux = getDependencies(v2);
        deps.merge(aux);
      }
    }
  }

  return deps;
}

PreservedAnalyses ConditionalBranchPass::run(Function &F, FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  for (Instruction &I : instructions(F)) {
    if (I.isTerminator()) {
      if (strcmp(I.getOpcodeName(), "br") == 0) {
        if (Instruction *cp = I.getPrevNode()) {
          // errs() << cp->getPredicate() << '\n';
          std::set<Value*> deps;
          for (unsigned int i = 0; i < cp->getNumOperands(); i++) {
            Value *v = cp->getOperand(i);
            if (strchr(v->getNameOrAsOperand().c_str(), '%')) {
              // errs () << v->getNameOrAsOperand() << "\n";
              deps.insert(v);
              std::set<Value*> aux = getDependencies(v);
              deps.merge(aux);
            }
          }
          conditionalBranches.insert(std::pair<Instruction*, std::set<Value*>>(&I, deps));
        }
      }
    }
  }

  for(std::pair<Instruction*, std::set<Value*>> p : conditionalBranches) {
    std::set<Value*> vals = p.second;
    std::map<Instruction*, std::set<Value*>>::iterator it = conditionalBranches.begin()++;
    while ((it != conditionalBranches.end()) && (p.first != it->first)) {
      it++;
    }
    it++;
    for (; it != conditionalBranches.end(); it++) {
      std::set<Value*> vals2 = it->second;
      std::set<Value*> intersection;
      std::set_intersection(vals.begin(), vals.end(), vals2.begin(), vals2.end(), std::inserter(intersection, intersection.begin()));
      if (!intersection.empty()) {
        errs() << "Instructions ";
        p.first->print(errs());
        errs() << " and ";
        it->first->print(errs());
        errs() << " have this common dependencies:\n\t\t";
        for( Value *v : intersection) {
          errs () << v->getNameOrAsOperand() << " ";
        }
        errs() << "\n";
      }
    }
  }

  return PreservedAnalyses::all();
}

