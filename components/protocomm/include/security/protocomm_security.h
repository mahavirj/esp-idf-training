// Copyright 2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <esp_err.h>

/**
 * @brief   Proof Of Possesion for authenticating a secure session
 */
typedef struct protocomm_security_pop {
    /**
     * Pointer to buffer containing the proof of possesion data
     */
    const uint8_t *data;

    /**
     * Length (in bytes) of the proof of possesion data
     */
    uint16_t len;
} protocomm_security_pop_t;

/**
 * @brief   Protocomm security object structure.
 *
 * The member functions are used for implementing secure
 * protocomm sessions.
 *
 * @note    This structure should not have any dynamic
 *          members to allow re-entrancy
 */
typedef struct protocomm_security {
    /**
     * Unique version number of security implmentation
     */
    int ver;

    /**
     * Function for initialising/allocating security
     * infrastructure
     */
    esp_err_t (*init)();

    /**
     * Function for deallocating security infrastructure
     */
    esp_err_t (*cleanup)();

    /**
     * Starts new secure transport session with specified ID
     */
    esp_err_t (*new_transport_session)(uint32_t session_id);

    /**
     * Closes a secure transport session with specified ID
     */
    esp_err_t (*close_transport_session)(uint32_t session_id);

    /**
     * Handler function for authenticating connection
     * request and establishing secure session
     */
    esp_err_t (*security_req_handler)(const protocomm_security_pop_t *pop,
                                      uint32_t session_id,
                                      const uint8_t *inbuf, ssize_t inlen,
                                      uint8_t **outbuf, ssize_t *outlen,
                                      void *priv_data);

    /**
     * Function which implements the encryption algorithm
     */
    esp_err_t (*encrypt)(uint32_t session_id,
                         const uint8_t *inbuf, ssize_t inlen,
                         uint8_t *outbuf, ssize_t *outlen);

    /**
     * Function which implements the decryption algorithm
     */
    esp_err_t (*decrypt)(uint32_t session_id,
                         const uint8_t *inbuf, ssize_t inlen,
                         uint8_t *outbuf, ssize_t *outlen);
} protocomm_security_t;
