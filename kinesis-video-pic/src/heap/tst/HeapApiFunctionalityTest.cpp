#include "HeapTestFixture.h"

class HeapApiFunctionalityTest : public HeapTestBase {
};

VOID singleLargeAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, MIN_HEAP_SIZE, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID singleByteAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handle)));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID multipleMapUnmapByteAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    PVOID pAlloc;
    UINT32 size;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1000, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));

    // Try multiple times
    for (UINT32 i = 0; i < NUM_ITERATIONS; i++) {
        EXPECT_TRUE(STATUS_SUCCEEDED(heapMap(pHeap, handle, &pAlloc, &size)));
        EXPECT_EQ(size, 1000);
        EXPECT_TRUE(pAlloc != NULL);

        EXPECT_TRUE(STATUS_SUCCEEDED(heapMap(pHeap, handle, &pAlloc, &size)));
        EXPECT_EQ(size, 1000);
        EXPECT_TRUE(pAlloc != NULL);

        EXPECT_TRUE(STATUS_SUCCEEDED(heapUnmap(pHeap, pAlloc)));
        EXPECT_TRUE(STATUS_SUCCEEDED(heapUnmap(pHeap, pAlloc)));
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handle)));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID multipleLargeAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    UINT32 size = MIN_HEAP_SIZE / NUM_ITERATIONS;
    UINT32 i;

    for (i = 0; i < NUM_ITERATIONS - 1; i++) {
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID minBlockFitAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    UINT32 size = MIN_HEAP_SIZE / NUM_ITERATIONS;
    ALLOCATION_HANDLE handles[NUM_ITERATIONS];
    UINT32 i;
    BOOL succeeded = TRUE;
    UINT32 retSize;
    PVOID pAlloc;

    // Set to default
    MEMSET(handles, INVALID_ALLOCATION_HANDLE_VALUE, NUM_ITERATIONS);

    // Iterate until we can't allocate a large block
    for (i = 0; i < NUM_ITERATIONS - 1; i++) {
        // Allocate a larger block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        handles[i] = handle;
    }

    // Free the third block
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[2])));

    // Try to allocate a smaller blocks which would fit in the freed allocation
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size / 3, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size / 3, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));

    // Free the second block
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[1])));

    // Try to allocate slightly smaller block which would still take the entire free block space
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size - 10, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));

    // Ensure the size is correct and the entire block hasn't been used
    EXPECT_TRUE(STATUS_SUCCEEDED(heapMap(pHeap, handle, &pAlloc, &retSize)));
    EXPECT_EQ(retSize, size - 10);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapUnmap(pHeap, pAlloc)));

    // Free the first block
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[0])));

    // Try to allocate same size
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));

    // Ensure the size is correct
    EXPECT_TRUE(STATUS_SUCCEEDED(heapMap(pHeap, handle, &pAlloc, &retSize)));
    EXPECT_EQ(retSize, size);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapUnmap(pHeap, pAlloc)));

    // Free the block and try to allocate slightly smaller
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handle)));

    // Try to allocate slightly larger
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size + 1, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));

    heapDebugCheckAllocator(pHeap, TRUE);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID blockCoalesceAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    UINT32 size = MIN_HEAP_SIZE / NUM_ITERATIONS;
    ALLOCATION_HANDLE handles[NUM_ITERATIONS];
    UINT32 i;
    BOOL succeeded = TRUE;

    // Set to default
    MEMSET(handles, INVALID_ALLOCATION_HANDLE_VALUE, NUM_ITERATIONS);

    // Iterate until we can't allocate a large block
    for (i = 0; i < NUM_ITERATIONS - 1; i++) {
        // Allocate a larger block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        handles[i] = handle;
    }

    // Try to allocate anything large
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));

    // Free the second block
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[1])));
    // Try to allocate anything large
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size + 1, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));
    // Free the third block
    EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[2])));
    // Try to allocate anything large = should fit due to free block coalescense
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size + 1, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));

    heapDebugCheckAllocator(pHeap, TRUE);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

VOID defragmentationAlloc(PHeap pHeap)
{
    ALLOCATION_HANDLE handle;
    UINT32 size = MIN_HEAP_SIZE / NUM_ITERATIONS;
    ALLOCATION_HANDLE handles[NUM_ITERATIONS];
    UINT32 i, blocks;
    BOOL succeeded = TRUE;

    // Set to default
    MEMSET(handles, INVALID_ALLOCATION_HANDLE_VALUE, NUM_ITERATIONS);

    // Iterate until we can't allocate a large block
    for (blocks = 0; succeeded;) {
        // Allocate a larger block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
        succeeded = IS_VALID_ALLOCATION_HANDLE(handle);
        handles[blocks++] = handle;

        // Allocate a smaller block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size - 1, &handle)));
        succeeded = IS_VALID_ALLOCATION_HANDLE(handle);
        handles[blocks++] = handle;
    }

    // Free all smaller blocks
    for (i = 0; i < blocks; i++) {
        if (i % 2 != 0 &&
                IS_VALID_ALLOCATION_HANDLE(handles[i])) {
            // Free the smaller block
            EXPECT_TRUE(STATUS_SUCCEEDED(heapFree(pHeap, handles[i])));
        }
    }

    // Expect an allocation of a single large block to fail whereas smaller one would succeed
    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size, &handle)));
    EXPECT_FALSE(IS_VALID_ALLOCATION_HANDLE(handle));

    EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, size - 1, &handle)));
    EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
    heapDebugCheckAllocator(pHeap, TRUE);

    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

TEST_F(HeapApiFunctionalityTest, GetHeapSizeAndGetAllocSize)
{
    PHeap pHeap;
    UINT32 i, size;
    UINT64 heapSize;
    ALLOCATION_HANDLE handle;

    // AIV heap
    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    for (i = 0; i < 10; i++) {
        // Allocate a block block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1000, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        EXPECT_TRUE(STATUS_SUCCEEDED(heapGetAllocSize(pHeap, handle, &size)));
        EXPECT_EQ(1000, size);
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapGetSize(pHeap, &heapSize)));
    EXPECT_EQ(10 * (1000 + aivGetAllocationHeaderSize() + aivGetAllocationFooterSize()), heapSize);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));

    // System heap
    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_SYSTEM_HEAP, &pHeap)));
    for (i = 0; i < 10; i++) {
        // Allocate a block block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1000, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        EXPECT_TRUE(STATUS_SUCCEEDED(heapGetAllocSize(pHeap, handle, &size)));
        EXPECT_EQ(1000, size);
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapGetSize(pHeap, &heapSize)));
    EXPECT_EQ(10 * (1000 + sysGetAllocationHeaderSize() + sysGetAllocationFooterSize()), heapSize);
    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));

    // AIV hybrid heap
    EXPECT_EQ(STATUS_SUCCESS, heapInitialize(MIN_HEAP_SIZE * 2 + 100000, 50, FLAGS_USE_AIV_HEAP | FLAGS_USE_HYBRID_VRAM_HEAP, &pHeap));
    for (i = 0; i < 10; i++) {
        // Allocate a block block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1000, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        EXPECT_TRUE(STATUS_SUCCEEDED(heapGetAllocSize(pHeap, handle, &size)));
        EXPECT_EQ(1000, size);
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));

    // System hybrid heap
    EXPECT_EQ(STATUS_SUCCESS, heapInitialize(MIN_HEAP_SIZE * 2 + 100000, 50, FLAGS_USE_SYSTEM_HEAP | FLAGS_USE_HYBRID_VRAM_HEAP, &pHeap));
    for (i = 0; i < 10; i++) {
        // Allocate a block block
        EXPECT_TRUE(STATUS_SUCCEEDED(heapAlloc(pHeap, 1000, &handle)));
        EXPECT_TRUE(IS_VALID_ALLOCATION_HANDLE(handle));
        EXPECT_TRUE(STATUS_SUCCEEDED(heapGetAllocSize(pHeap, handle, &size)));
        EXPECT_EQ(1000, size);
    }

    EXPECT_TRUE(STATUS_SUCCEEDED(heapRelease(pHeap)));
}

TEST_F(HeapApiFunctionalityTest, SingleLargeAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    singleLargeAlloc(pHeap);

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_SYSTEM_HEAP, &pHeap)));
    singleLargeAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, MultipleLargeAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    multipleLargeAlloc(pHeap);

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_SYSTEM_HEAP, &pHeap)));
    multipleLargeAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, DefragmentationAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    defragmentationAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, SingleByteAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    singleByteAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, AivHeapMinBlockFitAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    minBlockFitAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, AivHeapBlockCoallesceAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    blockCoalesceAlloc(pHeap);
}

TEST_F(HeapApiFunctionalityTest, MultipleMapUnmapByteAlloc)
{
    PHeap pHeap;

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_AIV_HEAP, &pHeap)));
    multipleMapUnmapByteAlloc(pHeap);

    EXPECT_TRUE(STATUS_SUCCEEDED(heapInitialize(MIN_HEAP_SIZE, 20, FLAGS_USE_SYSTEM_HEAP, &pHeap)));
    multipleMapUnmapByteAlloc(pHeap);
}