/**
 * @file       cbuffer.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       26/06/2024
 * @author     Minh Phung Nhat
 *             Hung Pham Duc
 *             Khoi Nguyen Thanh
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       None
 * @example    cbuffer_t cb;
 *             uint8_t cb_buff[6];
 *             uint8_t a;
 *             void main(void)
 *             {
 *                 int res = 0;
 *                 cb_init(&cb, cb_buff, 100);
 *                 cb_clear(&cb);
 *                 char a[] = {0, 1, 2, 3, 4};
 * 
 *                 int c = 5;
 *                 res = cb_write(&cb, a, 5);
 *                 char b[5];
 *                 res = cb_read(&cb, a, 5);
 *             }
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __CBUFFER_H
#define __CBUFFER_H

/* Includes ----------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_compiler.h"

/* Public defines ----------------------------------------------------- */
#define CB_MAX_SIZE (0x00800000) /*!< Max size of circular buffer */

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Circular buffer struct definition
 */
typedef struct
{
    uint8_t *data;
    uint32_t size;
    uint32_t writer;
    uint32_t reader;
    uint32_t overflow;
    bool active;
} cbuffer_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 * @param[in]       buf     Pointer to array
 * @param[in]       size    Size of buffer
 *
 * @return          none
 */
void cb_init(cbuffer_t *cb, void *buf, uint32_t size);

/**
 * @brief           Clear circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 *
 * @return          none
 */
void cb_clear(cbuffer_t *cb);

/**
 * @brief           Read data from circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 * @param[out]      buf     Pointer to data buffer 
 * @param[in]       size    Size of data that want to read
 *
 * @return          Number of successfully read byte
 */
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes);

/**
 * @brief           Write data to circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 * @param[in]       buf     Pointer to data buffer
 * @param[in]       size    Size of data that want to read
 *
 * @return          Number of successfully written byte
 */
uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes);

/**
 * @brief           Return a number of byte in circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 *
 * @return          Number of byte in circular buffer
 */
uint32_t cb_data_count(cbuffer_t *cb);

/**
 * @brief           Return a number of space (in byte unit) in circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 *
 * @return          Number of space (in byte unit) in circular buffer
 */
uint32_t cb_space_count(cbuffer_t *cb);

#endif                     // __CBUFFER_H

/* End of file -------------------------------------------------------- */
