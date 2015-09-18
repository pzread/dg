#ifndef _LLVM_REACHING_DEFS_ANALYSIS_H_
#define _LLVM_REACHING_DEFS_ANALYSIS_H_

#include "analysis/DataFlowAnalysis.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>

namespace llvm {
    class DataLayout;
    class ConstantExpr;
};

namespace dg {

class LLVMDependenceGraph;
class LLVMNode;

namespace analysis {

class LLVMReachingDefsAnalysis : public DataFlowAnalysis<LLVMNode>
{
    LLVMDependenceGraph *dg;
    const llvm::DataLayout *DL;
public:
    LLVMReachingDefsAnalysis(LLVMDependenceGraph *dg);

    /* virtual */
    bool runOnNode(LLVMNode *node);
    void handleNode(LLVMNode *);
private:
    Pointer getConstantExprPointer(const llvm::ConstantExpr *);
    LLVMNode *getOperand(LLVMNode *node,
                         const llvm::Value *val, unsigned int idx);

    bool handleCallInst(LLVMDependenceGraph *, LLVMNode *, DefMap *);
    bool handleUndefinedCall(LLVMNode *, DefMap *);
    bool handleCallInst(LLVMNode *, DefMap *);
};

} // namespace analysis
} // namespace dg

#endif