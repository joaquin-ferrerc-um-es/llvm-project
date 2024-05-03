#include "llvm/Transforms/Utils/ConditionalBranch.h"

using namespace llvm;

std::set<Value*> ConditionalBranchPass::getDependencies(Value *v, std::set<Value*> prevDeps) {
  std::set<Value*> deps;

  if (isa<Instruction>(v)) {
    Instruction *I = cast<Instruction>(v);
    for (unsigned int i = 0; i < I->getNumOperands(); i++) {
      Value *v2 = I->getOperand(i);
      if (strchr(v2->getNameOrAsOperand().c_str(), '%')) {
        if (prevDeps.find(v2) == prevDeps.end()) {
          // errs () << v2->getNameOrAsOperand() << "\n";
          std::set<Value*> deps2 = prevDeps;
          deps.insert(v2);
          deps2.insert(v2);
          std::set<Value*> aux = getDependencies(v2, deps2);
          deps.merge(aux);
        }
      }
    }
  }

  return deps;
}

PreservedAnalyses ConditionalBranchPass::run(Function &F, FunctionAnalysisManager &AM) {
  conditionalBranches.clear();

  bool printed = false;
  
  for (Instruction &I : instructions(F)) {
    if (I.isTerminator()) {
      if (strcmp(I.getOpcodeName(), "br") == 0) {
        Instruction *ip = I.getPrevNode();
        if ((ip != nullptr)) {
          CmpInst *cp = dyn_cast<CmpInst>(ip);
          if (cp != nullptr) {
            // errs() << cp->getPredicate() << '\n';
            std::set<Value*> deps;
            for (unsigned int i = 0; i < cp->getNumOperands(); i++) {
              Value *v = cp->getOperand(i);
              if (strchr(v->getNameOrAsOperand().c_str(), '%')) {
                // errs () << v->getNameOrAsOperand() << "\n";
                deps.insert(v);
                std::set<Value*> aux = getDependencies(v, deps);
                deps.merge(aux);
              }
            }
            conditionalBranches.insert(std::pair<Instruction*, std::set<Value*>>(&I, deps));
          }
        }
      }
    }
  }

  for(std::pair<Instruction*, std::set<Value*>> p : conditionalBranches) {
    std::set<Value*> vals = p.second;
    if(vals.size() > 0){
      meanCorrelation += vals.size();
      totalBranches++;
    }else{
      numNonDepBranches++;
    }
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
        float correlation1 = (float)intersection.size()/(float)vals.size();
        float correlation2 = (float)intersection.size()/(float)vals2.size();
        int pos = ceil(std::min(correlation1, correlation2)*10);
        correlationStats[pos]++;
        if (!printed) {
          errs() << "\n\n\n" << F.getName() << "\n";
          printed = true;
        }
        errs() << "\tInstructions:\n\t\t"; 
        p.first->print(errs());
        // errs() << " " << vals.size();
        errs() << "\n\tand\n\t\t";
        it->first->print(errs());
        // errs() << " " << vals2.size();
        errs() << "\n\thave this common dependencies:\n\t\t\t";
        for( Value *v : intersection) {
          errs () << v->getNameOrAsOperand() << " ";
        }
        errs() << "\n\n";
      }else{
        correlationStats[0]++;
      }
    }
  }

  errs() << "Correlation of the benchmark branches:\n\n";
  errs() << "0\%;" << correlationStats[0] << ";\n";

  int min = 1;
  int max = 10;
  for (int i = 1; i < STAT_SIZE; i++) {
    errs() << min <<"\%-" << max << "\%;" << correlationStats[i] << "\n";
    min += 10;
    max += 10;
  }

  errs() << "\nMean of dependencies per branch: " << (float)meanCorrelation/(float)totalBranches;

  errs() << "\nPercentaje of branches with dependencies: " << (float)totalBranches/(float)(numNonDepBranches+ totalBranches);

  errs() << "\n\n\n";

  return PreservedAnalyses::all();
}

