#include "gtest/gtest.h"
#include <com/amazonaws/kinesis/video/utils/Include.h>

/**
 * Static variable for using later in the tests with callbacks
 */
HashEntry gEntries[110];
UINT32 gIteration = 0;
UINT64 gCallerData = 0x55555;

/**
 * Callbacks
 */
STATUS successCallbackFn(UINT64 callerData, PHashEntry pHashEntry)
{
    if (callerData != gCallerData) {
        return STATUS_INTERNAL_ERROR;
    } else {
        return STATUS_SUCCESS;
    }
}

STATUS errCallbackFn(UINT64 callerData, PHashEntry pHashEntry)
{
    if (callerData != gCallerData) {
        return STATUS_INTERNAL_ERROR;
    } else {
        return STATUS_INVALID_ARG;
    }
}

STATUS abortCallbackFn(UINT64 callerData, PHashEntry pHashEntry)
{
    STATUS status;

    if (callerData != gCallerData) {
        return STATUS_INTERNAL_ERROR;
    }

    if (gIteration == 50) {
        status = STATUS_HASH_ENTRY_ITERATION_ABORT;
    } else if (gIteration > 50) {
        status = STATUS_INTERNAL_ERROR;
    } else {
        status = STATUS_SUCCESS;
    }

    gEntries[gIteration++] = *pHashEntry;

    return status;
}

/**
 * Main tests
 */

TEST(NegativeInvalidInput, HashTableCreate)
{
    EXPECT_NE(STATUS_SUCCESS, hashTableCreate(NULL));
}

TEST(NegativeInvalidInput, HashTableCreateWithParams)
{
    PHashTable pHashTable;
    EXPECT_NE(STATUS_SUCCESS, hashTableCreateWithParams(0, 1, &pHashTable));
    EXPECT_NE(STATUS_SUCCESS, hashTableCreateWithParams(MIN_HASH_BUCKET_COUNT - 1, 1, &pHashTable));
    EXPECT_NE(STATUS_SUCCESS, hashTableCreateWithParams(MIN_HASH_BUCKET_COUNT, 0, &pHashTable));
    EXPECT_NE(STATUS_SUCCESS, hashTableCreateWithParams(MIN_HASH_BUCKET_COUNT, 1, NULL));
}

TEST(PositiveIdempotentInvalidInput, HashTableFree)
{
    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(NULL));
}

TEST(NegativeInvalidInput, HashTableClear)
{
    EXPECT_NE(STATUS_SUCCESS, hashTableClear(NULL));
}

TEST(NegativeInvalidInput, HashTableGetCount)
{
    PHashTable pHashTable = (PHashTable) 1;
    UINT32 count;
    EXPECT_NE(STATUS_SUCCESS, hashTableGetCount(NULL, &count));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetCount(pHashTable, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetCount(NULL, NULL));
}

TEST(NegativeInvalidInput, HashTableIsEmpty)
{
    PHashTable pHashTable = (PHashTable) 1;
    BOOL isEmpty;
    EXPECT_NE(STATUS_SUCCESS, hashTableIsEmpty(NULL, &isEmpty));
    EXPECT_NE(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableIsEmpty(NULL, NULL));
}

TEST(NegativeInvalidInput, HashTablePut)
{
    PHashTable pHashTable;
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    EXPECT_NE(STATUS_SUCCESS, hashTablePut(NULL, 1, 2));

    // Put an item twice
    EXPECT_EQ(STATUS_SUCCESS, hashTablePut(pHashTable, 1, 2));
    EXPECT_NE(STATUS_SUCCESS, hashTablePut(pHashTable, 1, 2));

    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(NegativeInvalidInput, HashTableUpsert)
{
    PHashTable pHashTable;
    UINT64 value;
    BOOL contains;
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    EXPECT_NE(STATUS_SUCCESS, hashTableUpsert(NULL, 1, 2));

    // Put an item twice
    EXPECT_EQ(STATUS_SUCCESS, hashTableUpsert(pHashTable, 1, 2));
    EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, 1, &contains));
    EXPECT_TRUE(contains);
    EXPECT_EQ(STATUS_SUCCESS, hashTableGet(pHashTable, 1, &value));
    EXPECT_EQ(2, value);
    EXPECT_EQ(STATUS_SUCCESS, hashTableUpsert(pHashTable, 1, 2));
    EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, 1, &contains));
    EXPECT_TRUE(contains);
    EXPECT_EQ(STATUS_SUCCESS, hashTableGet(pHashTable, 1, &value));
    EXPECT_EQ(2, value);
    EXPECT_EQ(STATUS_SUCCESS, hashTableUpsert(pHashTable, 1, 3));
    EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, 1, &contains));
    EXPECT_TRUE(contains);
    EXPECT_EQ(STATUS_SUCCESS, hashTableGet(pHashTable, 1, &value));
    EXPECT_EQ(3, value);

    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(NegativeInvalidInput, HashTableGet)
{
    PHashTable pHashTable;
    UINT64 val;
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    EXPECT_NE(STATUS_SUCCESS, hashTableGet(NULL, 1, &val));
    EXPECT_NE(STATUS_SUCCESS, hashTableGet(pHashTable, 1, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableGet(NULL, 1, NULL));

    // Get a non-existing item
    EXPECT_NE(STATUS_SUCCESS, hashTableGet(pHashTable, 1, &val));

    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(NegativeInvalidInput, HashTableContains)
{
    PHashTable pHashTable;
    BOOL contains;
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    EXPECT_NE(STATUS_SUCCESS, hashTableContains(NULL, 1, &contains));
    EXPECT_NE(STATUS_SUCCESS, hashTableContains(pHashTable, 1, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableContains(NULL, 1, NULL));

    // Get a non-existing item
    EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, 1, &contains));
    EXPECT_FALSE(contains);

    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(NegativeInvalidInput, HashTableRemove)
{
    PHashTable pHashTable;
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    EXPECT_NE(STATUS_SUCCESS, hashTableRemove(NULL, 1));

    // Remove a non-existing item
    EXPECT_NE(STATUS_SUCCESS, hashTableRemove(pHashTable, 1));

    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(NegativeInvalidInput, HashTableGetBucketCount)
{
    PHashTable pHashTable = (PHashTable) 1;
    UINT32 count;
    EXPECT_NE(STATUS_SUCCESS, hashTableGetBucketCount(NULL, &count));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetBucketCount(pHashTable, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetBucketCount(NULL, NULL));
}

TEST(NegativeInvalidInput, HashTableGetAllEntries)
{
    PHashTable pHashTable = (PHashTable) 1;
    PHashEntry pHashEntries;
    UINT32 count;

    EXPECT_NE(STATUS_SUCCESS, hashTableGetAllEntries(NULL, NULL, &count));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetAllEntries(NULL, pHashEntries, &count));

    EXPECT_NE(STATUS_SUCCESS, hashTableGetAllEntries(pHashTable, NULL, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableGetAllEntries(pHashTable, pHashEntries, NULL));
}

TEST(NegativeInvalidInput, HashTableIterateEntries)
{
    PHashTable pHashTable = (PHashTable) 1;

    EXPECT_NE(STATUS_SUCCESS, hashTableIterateEntries(NULL, 0, NULL));
    EXPECT_NE(STATUS_SUCCESS, hashTableIterateEntries(NULL, 0, successCallbackFn));
    EXPECT_NE(STATUS_SUCCESS, hashTableIterateEntries(pHashTable, 0, NULL));
}

TEST(FunctionalTest, HashTableClear)
{
    PHashTable pHashTable;
    UINT64 count = 10000;
    UINT32 retCount;

    // Create the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    // Insert elements
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTablePut(pHashTable, i, i));
    }

    // Validate the count
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(count, (UINT64) retCount);

    // Clear the data
    EXPECT_EQ(STATUS_SUCCESS, hashTableClear(pHashTable));

    // Validate the count
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(0, (UINT64) retCount);

    // Destroy the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(FunctionalTest, HashTablePutContainsRemoveIsEmpty)
{
    PHashTable pHashTable;
    UINT64 count = 1000;
    UINT64 val;
    UINT32 retCount;
    BOOL contains;
    BOOL isEmpty;

    // Create the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreateWithParams(MIN_HASH_BUCKET_COUNT, 2, &pHashTable));

    // Validate the count and empty
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(0, retCount);
    EXPECT_EQ(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, &isEmpty));
    EXPECT_TRUE(isEmpty);

    // Insert elements
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTablePut(pHashTable, i, i));
    }

    // Validate the count and empty
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(count, (UINT64) retCount);
    EXPECT_EQ(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, &isEmpty));
    EXPECT_FALSE(isEmpty);

    // Check if element exists and get
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, i, &contains));
        EXPECT_TRUE(contains);

        EXPECT_EQ(STATUS_SUCCESS, hashTableGet(pHashTable, i, &val));
        EXPECT_EQ(val, i);
    }

    // Validate the count and empty hasn't changed
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(count, (UINT64) retCount);
    EXPECT_EQ(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, &isEmpty));
    EXPECT_FALSE(isEmpty);

    // Remove and check if element exists and get
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTableRemove(pHashTable, i));
        EXPECT_EQ(STATUS_HASH_KEY_NOT_PRESENT, hashTableRemove(pHashTable, i));

        EXPECT_EQ(STATUS_SUCCESS, hashTableContains(pHashTable, i, &contains));
        EXPECT_FALSE(contains);

        EXPECT_EQ(STATUS_HASH_KEY_NOT_PRESENT, hashTableGet(pHashTable, i, &val));

        // Validate the count
        EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
        EXPECT_EQ(count - i - 1, (UINT64) retCount);
    }

    // Validate the count and empty
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(0, retCount);
    EXPECT_EQ(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, &isEmpty));
    EXPECT_TRUE(isEmpty);

    // Clear the data
    EXPECT_EQ(STATUS_SUCCESS, hashTableClear(pHashTable));

    // Validate the count
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetCount(pHashTable, &retCount));
    EXPECT_EQ(0, (UINT64) retCount);
    EXPECT_EQ(STATUS_SUCCESS, hashTableIsEmpty(pHashTable, &isEmpty));
    EXPECT_TRUE(isEmpty);

    // Destroy the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(FunctionalTest, HashTableGetAllEntries)
{
    PHashTable pHashTable;
    UINT64 count = 100;
    UINT32 retCount;
    BOOL contains;

    // Create the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreateWithParams(MIN_HASH_BUCKET_COUNT, 2, &pHashTable));

    // Insert elements
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTablePut(pHashTable, i, i));
    }

    EXPECT_EQ(STATUS_SUCCESS, hashTableGetAllEntries(pHashTable, NULL, &retCount));
    EXPECT_EQ((UINT32)count, retCount);

    retCount = count + 1;
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetAllEntries(pHashTable, gEntries, &retCount));
    EXPECT_EQ((UINT32)count, retCount);

    // Validate all are present
    for (UINT64 i = 0; i < count; i++) {
        contains = FALSE;
        for (UINT32 j = 0; j < count; j++) {
            if (gEntries[j].value == i) {
                contains = TRUE;
                break;
            }
        }

        EXPECT_TRUE(contains);
    }

    // Destroy the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}

TEST(FunctionalTest, HashTableIterateEntries)
{
    PHashTable pHashTable;
    UINT64 count = 100;
    UINT32 retCount;
    HashEntry entries[110];

    // Create the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableCreate(&pHashTable));

    // Make sure we can run an error callback on empty table
    EXPECT_EQ(STATUS_SUCCESS, hashTableIterateEntries(pHashTable, gCallerData, errCallbackFn));

    // Insert elements
    for (UINT64 i = 0; i < count; i++) {
        EXPECT_EQ(STATUS_SUCCESS, hashTablePut(pHashTable, i, i));
    }

    // Get all of the entries
    retCount = (UINT32) count;
    EXPECT_EQ(STATUS_SUCCESS, hashTableGetAllEntries(pHashTable, entries, &retCount));
    EXPECT_EQ((UINT64) retCount, count);

    // Make sure the error callback fires and it returns the same error
    EXPECT_EQ(STATUS_INVALID_ARG, hashTableIterateEntries(pHashTable, gCallerData, errCallbackFn));

    // Set the iteration counter
    gIteration = 0;

    // Iterate and abort at half
    EXPECT_EQ(STATUS_SUCCESS, hashTableIterateEntries(pHashTable, gCallerData, abortCallbackFn));
    EXPECT_EQ(count / 2, gIteration - 1);

    // Validate all are present
    for (UINT64 i = 0; i < count / 2; i++) {
        EXPECT_EQ(gEntries[i].key, entries[i].key);
        EXPECT_EQ(gEntries[i].value, entries[i].value);
    }

    // Destroy the table
    EXPECT_EQ(STATUS_SUCCESS, hashTableFree(pHashTable));
}
