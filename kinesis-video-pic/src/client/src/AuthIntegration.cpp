/**
 * Kinesis Video Auth integration
 */
#define LOG_CLASS "KinesisVideoAuthIntegration"
#include "Include_i.h"

/**
 * Integrates with the client authentication sub-system
 *
 * NOTE: if the device is not provisioned then the auth mode will be undefined
 */
STATUS getAuthInfo(PKinesisVideoClient pKinesisVideoClient)
{
    ENTERS();
    STATUS retStatus = STATUS_SUCCESS;
    PBYTE pAuthData = NULL;
    UINT32 authDataSize = 0;
    UINT64 authExpiration = 0;

    CHK(pKinesisVideoClient != NULL, STATUS_NULL_ARG);

    // Try to integrate with the security token first
    if (pKinesisVideoClient->clientCallbacks.getSecurityTokenFn != NULL) {
        CHK_STATUS(pKinesisVideoClient->clientCallbacks.getSecurityTokenFn(pKinesisVideoClient->clientCallbacks.customData,
                                                                     &pAuthData,
                                                                     &authDataSize,
                                                                     &authExpiration));

        if (authDataSize != 0 && pAuthData != NULL) {
            // Got the token successfully - store it
            CHK(authDataSize <= MAX_AUTH_LEN, STATUS_INVALID_AUTH_LEN);
            pKinesisVideoClient->tokenAuthInfo.type = AUTH_INFO_TYPE_STS;
            pKinesisVideoClient->tokenAuthInfo.version = AUTH_INFO_CURRENT_VERSION;
            pKinesisVideoClient->tokenAuthInfo.expiration = authExpiration;
            pKinesisVideoClient->tokenAuthInfo.size = authDataSize;
            MEMCPY(pKinesisVideoClient->tokenAuthInfo.data, pAuthData, authDataSize);

            // Successful early return
            CHK(FALSE, retStatus);
        }
    }

    if (pKinesisVideoClient->clientCallbacks.getDeviceCertificateFn != NULL) {
        CHK_STATUS(pKinesisVideoClient->clientCallbacks.getDeviceCertificateFn(pKinesisVideoClient->clientCallbacks.customData,
                                                                         &pAuthData,
                                                                         &authDataSize,
                                                                         &authExpiration));

        if (authDataSize != 0 && pAuthData != NULL) {
            // Got the token successfully - store it
            CHK(authDataSize <= MAX_AUTH_LEN, STATUS_INVALID_AUTH_LEN);
            pKinesisVideoClient->certAuthInfo.type = AUTH_INFO_TYPE_CERT;
            pKinesisVideoClient->certAuthInfo.version = AUTH_INFO_CURRENT_VERSION;
            pKinesisVideoClient->certAuthInfo.expiration = authExpiration;
            pKinesisVideoClient->certAuthInfo.size = authDataSize;
            MEMCPY(pKinesisVideoClient->certAuthInfo.data, pAuthData, authDataSize);

            // Successful early return
            CHK(FALSE, retStatus);
        }
    }

    // We need to do provisioning at this stage

CleanUp:

    LEAVES();
    return retStatus;
}

/**
 * Returns the current auth integration type
 */
AUTH_INFO_TYPE getCurrentAuthType(PKinesisVideoClient pKinesisVideoClient)
{
    ENTERS();
    AUTH_INFO_TYPE authType = AUTH_INFO_UNDEFINED;

    // Check the token auth info first. If it's provided - either STS or none then return it. Otherwise, probe the cert.
    if (pKinesisVideoClient->tokenAuthInfo.type != AUTH_INFO_UNDEFINED) {
        authType = pKinesisVideoClient->tokenAuthInfo.type;
    } else if (pKinesisVideoClient->certAuthInfo.type != AUTH_INFO_UNDEFINED) {
        authType = pKinesisVideoClient->certAuthInfo.type;
    }

    LEAVES();
    return authType;
}

/**
 * Returns the current auth expiration
 */
UINT64 getCurrentAuthExpiration(PKinesisVideoClient pKinesisVideoClient)
{
    ENTERS();
    UINT64 expiration = 0;

    // Check the token auth info first. If it's provided - either STS or none then return it. Otherwise, probe the cert.
    if (pKinesisVideoClient->tokenAuthInfo.type != AUTH_INFO_UNDEFINED) {
        expiration = pKinesisVideoClient->tokenAuthInfo.expiration;
    } else if (pKinesisVideoClient->certAuthInfo.type != AUTH_INFO_UNDEFINED) {
        expiration = pKinesisVideoClient->certAuthInfo.expiration;
    }

    LEAVES();
    return expiration;
}

/**
 * Performs the producer client provisioning
 * NOTE: This is a long running operation
 */
STATUS provisionKinesisVideoProducer(PKinesisVideoClient pKinesisVideoClient)
{
    ENTERS();
    STATUS retStatus = STATUS_SUCCESS;
    PCHAR pDeviceFingerprint = NULL;

    CHK(pKinesisVideoClient != NULL, STATUS_NULL_ARG);

    // We should certainly have the fingerprint function defined
    if (pKinesisVideoClient->clientCallbacks.getDeviceFingerprintFn != NULL) {
        // Get the device fingerprint
        CHK_STATUS(pKinesisVideoClient->clientCallbacks.getDeviceFingerprintFn(pKinesisVideoClient->clientCallbacks.customData, &pDeviceFingerprint));
    }

    // Validate the length if we got valid device fingerprint
    if (pDeviceFingerprint != NULL && pDeviceFingerprint[0] != '\0') {
        // Validate and store
        CHK(STRNLEN(pDeviceFingerprint, MAX_DEVICE_FINGERPRINT_LENGTH) < MAX_DEVICE_FINGERPRINT_LENGTH, STATUS_DEVICE_FINGERPRINT_LENGTH);
        STRNCPY(pKinesisVideoClient->deviceFingerprint, pDeviceFingerprint, MAX_DEVICE_FINGERPRINT_LENGTH);
    } else {
        // Generate one
        createRandomName(pKinesisVideoClient->deviceFingerprint,
                         MAX_DEVICE_FINGERPRINT_LENGTH,
                         pKinesisVideoClient->clientCallbacks.getRandomNumberFn,
                         pKinesisVideoClient->clientCallbacks.customData);
    }

    // TODO: Implement provisioning

CleanUp:

    LEAVES();
    return retStatus;
}