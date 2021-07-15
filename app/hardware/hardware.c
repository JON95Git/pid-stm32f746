#include "hardware.h"
#include "fatfs.h"
#include "stm32746g_discovery.h"
#include "sd_diskio.h"

char SDPath[4]; /* SD logical drive path */
FATFS SDFatFS;  /* File system object for SD logical drive */
FIL SDFile;     /* File object for SD */
uint8_t workBuffer[2 * _MAX_SS];
uint32_t byteswritten, bytesread;                     /* File write/read counts */
uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
uint8_t rtext[100];
FRESULT fat_res = FR_OK;

static volatile uint32_t timer_counter = 0;

void hardware_init(void)
{
    BSP_LED_Init(LED_GREEN);
    // encoder_init();
    // pwm_timer_init();
    // init_fatfs();
}

void pwm_timer_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

uint32_t timer_get_current_tick(void)
{
    return (timer_counter);
}

void timer_update_callback(void)
{
    ++timer_counter;
}

void encoder_init(void)
{
    HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}

void encoder_stop(void)
{
    HAL_TIM_Encoder_Stop_IT(&htim3, TIM_CHANNEL_ALL);
}

void init_fatfs(void)
{
    fat_res = f_mount(&SDFatFS, (TCHAR const *)SDPath, 0);
    if (fat_res != FR_OK) {
        error_handler();
    }

    fat_res = f_mkfs((TCHAR const *)SDPath, FM_ANY, 0, workBuffer, sizeof(workBuffer));
    if (fat_res != FR_OK) {
        error_handler();
    }

    fat_res = f_open(&SDFile, "jon.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (fat_res != FR_OK) {
        error_handler();
    }

    fat_res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);
    if (fat_res != FR_OK) {
        error_handler();
    }
    f_close(&SDFile);

  /*##-11- Unlink the micro SD disk I/O driver ###############################*/
  FATFS_UnLinkDriver(SDPath);
}