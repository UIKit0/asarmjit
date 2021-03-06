#ifndef __INCLUDED_BLOCK_H
#define __INCLUDED_BLOCK_H

#include "as_jit_arm.h"
#include "as_jit_arm_op.h"
#include "registermanager.h"

class asCJitArm;
class ASRegister;
class Block
{
public:
    Block(asCJitArm *j, int start, int end);

    ~Block();

    void AddRegister(int id, bool writtenTo = false);

    void SetRegisterMapping(int id, int native);
    int GetNative(int asRegister, bool writeTo = false, ASRegisterType type = ASRegisterType_int);
    void WroteToRegister(int asRegister);

    void Start();
    void End();
    void Return(int flushmask = 0xffff);

    void Flush(int flushMask = 0xffff, int freeMask = 0xffff, int cond = COND_AL);

    void Suspend();

    void UpdateBC();

    int registerStoreMask;
    int registerLoadMask;

    int registerUseMask;

    bool hasUnimplementedBytecode;

    bool hasRegistersToLoad;
    bool hasRegistersToSave;

    int byteCodeStart;
    int byteCodeEnd;

    int nativeOffset;
    int loadInstructions;
    asCJitArm *jit;
    bool hasFlushed;

    bool ended;

    bool isCrossSuspendJumpTarget;
    bool isCrossSuspendJumpEnd;
    bool isJumpTarget;
    bool isSeparateStart;
    bool isSeparateEnd;
    bool endsWithCrossSuspendJump;
    std::vector<ASRegister>     registersUsed;
    std::vector<int>        targetBlocks;
};



#endif
