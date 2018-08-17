#include "HeapTestFixture.h"

/**
 * Static mock return values
 */
UINT32 HeapTestBase::mVramGetMax;
UINT32 HeapTestBase::mVramInit;
UINT32 HeapTestBase::mVramAlloc;
UINT32 HeapTestBase::mVramFree;
PVOID HeapTestBase::mVramLock;
UINT32 HeapTestBase::mVramUnlock;
UINT32 HeapTestBase::mVramUninit;

UINT32 HeapTestBase::mVramGetMaxCount;
UINT32 HeapTestBase::mVramInitCount;
UINT32 HeapTestBase::mVramAllocCount;
UINT32 HeapTestBase::mVramFreeCount;
UINT32 HeapTestBase::mVramLockCount;
UINT32 HeapTestBase::mVramUnlockCount;
UINT32 HeapTestBase::mVramUninitCount;

PVOID HeapTestBase::mDlOpen;
INT32 HeapTestBase::mDlClose;
BOOL HeapTestBase::mDlSym;

UINT32 HeapTestBase::mDlOpenCount;
UINT32 HeapTestBase::mDlErrorCount;
UINT32 HeapTestBase::mDlSymCount;
UINT32 HeapTestBase::mDlCloseCount;

UINT8 HeapTestBase::mScratchBuf[];

VOID HeapTestBase::SetUpInternal()
{
    mVramGetMax = MIN_HEAP_SIZE * 2;
    mVramInit = 0;
    mVramFree = 0;
    mVramAlloc = 1;
    mVramLock = mScratchBuf;
    mVramUnlock = 0;
    mVramUninit = 0;
    mVramGetMaxCount = 0;
    mVramInitCount = 0;
    mVramAllocCount = 0;
    mVramFreeCount = 0;
    mVramLockCount = 0;
    mVramUnlockCount = 0;
    mVramUninitCount = 0;

    mDlOpen = (PVOID) MOCK_LIB_HANDLE;
    mDlClose = 0;
    mDlSym = TRUE;

    mDlOpenCount = 0;
    mDlErrorCount = 0;
    mDlSymCount = 0;
    mDlCloseCount = 0;
}

VOID HeapTestBase::SetUpTestCase()
{
    globalDlOpen = HeapTestBase::mockDlOpen;
    globalDlClose = HeapTestBase::mockDlClose;
    globalDlSym = HeapTestBase::mockDlSym;
    globalDlError = HeapTestBase::mockDlError;
}

VOID HeapTestBase::SetUp()
{
    SetUpInternal();
}

//
// Mock dynamic library loading functions
//
PVOID HeapTestBase::mockDlOpen(PCHAR filename, UINT32 flag)
{
    DLOGI("Calling mock dlOpen()");
    mDlOpenCount++;
    return mDlOpen;
}

INT32 HeapTestBase::mockDlClose(PVOID handle)
{
    DLOGI("Calling mock dlClose()");
    mDlCloseCount++;
    return mDlClose;
}

PVOID HeapTestBase::mockDlSym(PVOID handle, PCHAR symbol)
{
    DLOGI("Calling mock dlSym() with symbol %s", symbol);
    mDlSymCount++;
    if (!mDlSym) {
        return NULL;
    } else if (0 == STRCMP(symbol, VRAM_INIT_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramInit;
    } else if (0 == STRCMP(symbol, VRAM_ALLOC_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramAlloc;
    } else if (0 == STRCMP(symbol, VRAM_FREE_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramFree;
    } else if (0 == STRCMP(symbol, VRAM_LOCK_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramLock;
    } else if (0 == STRCMP(symbol, VRAM_UNLOCK_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramUnlock;
    } else if (0 == STRCMP(symbol, VRAM_UNINIT_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramUninit;
    } else if (0 == STRCMP(symbol, VRAM_GETMAX_FUNC_SYMBOL_NAME)) {
        return (PVOID) HeapTestBase::mockVramGetMax;
    }

    return NULL;
}

PCHAR HeapTestBase::mockDlError()
{
    DLOGI("Calling mock dlError()");
    mDlErrorCount++;
    return "Mock error from the dlError() function";
}

UINT32 HeapTestBase::mockVramInit()
{
    mVramInitCount++;
    return mVramInit;
}

UINT32 HeapTestBase::mockVramAlloc(UINT32)
{
    mVramAllocCount++;
    return mVramAlloc;
}

UINT32 HeapTestBase::mockVramFree(UINT32)
{
    mVramFreeCount++;
    return mVramFree;
}

PVOID HeapTestBase::mockVramLock(UINT32 alloc)
{
    mVramLockCount++;
    return mVramLock;
}

UINT32 HeapTestBase::mockVramUnlock(UINT32 handle)
{
    mVramUnlockCount++;
    return mVramUnlock;
}

UINT32 HeapTestBase::mockVramUninit()
{
    mVramUninitCount++;
    return mVramUninit;
}

UINT32 HeapTestBase::mockVramGetMax()
{
    mVramGetMaxCount++;
    return mVramGetMax;
}
