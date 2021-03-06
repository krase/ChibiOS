/*
 * Licensed under ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    FlexPWM_v1/pwm_lld.h
 * @brief   SPC5xx low level PWM driver header.
 *
 * @addtogroup PWM
 * @{
 */

#include "spc5_flexpwm.h"

#ifndef _PWM_LLD_H_
#define _PWM_LLD_H_

#if HAL_USE_PWM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    STS register bits definitions
 * @{
 */
#define SPC5_FLEXPWM_STS_CMPF0                          (1U << 0)
#define SPC5_FLEXPWM_STS_CMPF1                          (1U << 1)
#define SPC5_FLEXPWM_STS_CMPF2                          (1U << 2)
#define SPC5_FLEXPWM_STS_CMPF3                          (1U << 3)
#define SPC5_FLEXPWM_STS_CMPF4                          (1U << 4)
#define SPC5_FLEXPWM_STS_CMPF5                          (1U << 5)
#define SPC5_FLEXPWM_STS_CFX0                           (1U << 6)
#define SPC5_FLEXPWM_STS_CFX1                           (1U << 7)
#define SPC5_FLEXPWM_STS_RF                             (1U << 12)
#define SPC5_FLEXPWM_STS_REF                            (1U << 13)
#define SPC5_FLEXPWM_STS_RUF                            (1U << 14)
/** @} */

/**
 * @name    PSC values definition
 * @{
 */
#define SPC5_FLEXPWM_PSC_1                              0U
#define SPC5_FLEXPWM_PSC_2                              1U
#define SPC5_FLEXPWM_PSC_4                              2U
#define SPC5_FLEXPWM_PSC_8                              3U
#define SPC5_FLEXPWM_PSC_16                             4U
#define SPC5_FLEXPWM_PSC_32                             5U
#define SPC5_FLEXPWM_PSC_64                             6U
#define SPC5_FLEXPWM_PSC_128                            7U
/** @} */

/**
 * @brief   Number of PWM channels per PWM driver.
 */
#define PWM_CHANNELS                            2

/**
 * @brief   Complementary output modes mask.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_MASK           0xF0

/**
 * @brief   Complementary output not driven.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_DISABLED       0x00

/**
 * @brief   Complementary output, active is logic level one.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH    0x10

/**
 * @brief   Complementary output, active is logic level zero.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW     0x20

/**
 * @brief   Edge-Aligned PWM functional mode.
 * @note    This is an SPC5-specific setting.
 */
#define EDGE_ALIGNED_PWM                        0x01

/**
 * @brief   Center-Aligned PWM functional mode.
 * @note    This is an SPC5-specific setting.
 */
#define CENTER_ALIGNED_PWM                      0x02

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
#if SPC5_HAS_FLEXPWM0
/**
 * @brief   PWMD1 driver enable switch.
 * @details If set to @p TRUE the support for PWMD1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD0) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD0                  TRUE
#endif

/**
 * @brief   PWMD2 driver enable switch.
 * @details If set to @p TRUE the support for PWMD2 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD1) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD1                  TRUE
#endif

/**
 * @brief   PWMD3 driver enable switch.
 * @details If set to @p TRUE the support for PWMD3 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD2) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD2                  TRUE
#endif

/**
 * @brief   PWMD4 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD3) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD3                  TRUE
#endif

/**
 * @brief   PWMD1 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD0_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD0_PRIORITY             7
#endif

/**
 * @brief   PWMD2 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD1_PRIORITY             7
#endif

/**
 * @brief   PWMD3 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD2_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD2_PRIORITY             7
#endif

/**
 * @brief   PWMD4 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD3_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD3_PRIORITY             7
#endif

/**
 * @brief   FlexPWM-0 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode. The defaults of the run modes
 *          are defined in @p hal_lld.h.
 */
#if !defined(SPC5_PWM_FLEXPWM0_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_PWM_FLEXPWM0_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   FlexPWM-0 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode. The defaults of the run modes
 *          are defined in @p hal_lld.h.
 */
#if !defined(SPC5_PWM_FLEXPWM0_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_PWM_FLEXPWM0_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif
#endif

#if SPC5_HAS_FLEXPWM1
/**
 * @brief   PWMD5 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD4) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD4                  TRUE
#endif

/**
 * @brief   PWMD6 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD5) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD5                  TRUE
#endif

/**
 * @brief   PWMD7 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD6) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD6                  FALSE
#endif

/**
 * @brief   PWMD8 driver enable switch.
 * @details If set to @p TRUE the support for PWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SPC5_PWM_USE_SMOD7) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_SMOD7                  TRUE
#endif

/**
 * @brief   PWMD5 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD4_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD4_PRIORITY          7
#endif

/**
 * @brief   PWMD6 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD5_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD5_PRIORITY          7
#endif

/**
 * @brief   PWMD7 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD6_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD6_PRIORITY          7
#endif

/**
 * @brief   PWMD8 interrupt priority level setting.
 */
#if !defined(SPC5_PWM_SMOD7_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PWM_SMOD7_PRIORITY          7
#endif

/**
 * @brief   FlexPWM-1 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode. The defaults of the run modes
 *          are defined in @p hal_lld.h.
 */
#if !defined(SPC5_PWM_FLEXPWM1_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_PWM_FLEXPWM1_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   FlexPWM-1 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode. The defaults of the run modes
 *          are defined in @p hal_lld.h.
 */
#if !defined(SPC5_PWM_FLEXPWM1_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_PWM_FLEXPWM1_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif
#endif

/*===========================================================================*/
/* Configuration checks.                                                     */
/*===========================================================================*/

#if SPC5_PWM_USE_SMOD0 && !SPC5_HAS_FLEXPWM0
#error "SMOD0 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMOD1 && !SPC5_HAS_FLEXPWM0
#error "SMOD1 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMDO2 && !SPC5_HAS_FLEXPWM0
#error "SMOD2 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMOD3 && !SPC5_HAS_FLEXPWM0
#error "SMOD3 not present in the selected device"
#endif

#if (!SPC5_PWM_USE_SMOD0 && !SPC5_PWM_USE_SMOD1 &&                           \
    !SPC5_PWM_USE_SMOD2 && !SPC5_PWM_USE_SMOD3) && SPC5_PWM_USE_FLEXPWM0
#error "PWM driver activated but no SubModule assigned"
#endif

#if SPC5_PWM_USE_SMOD4 && !SPC5_HAS_FLEXPWM1
#error "SMOD4 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMOD5 && !SPC5_HAS_FLEXPWM1
#error "SMOD5 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMDO6 && !SPC5_HAS_FLEXPWM1
#error "SMOD6 not present in the selected device"
#endif

#if SPC5_PWM_USE_SMOD7 && !SPC5_HAS_FLEXPWM1
#error "SMOD7 not present in the selected device"
#endif

#if (!SPC5_PWM_USE_SMOD4 && !SPC5_PWM_USE_SMOD5 &&                           \
    !SPC5_PWM_USE_SMOD6 && !SPC5_PWM_USE_SMOD7) && SPC5_PWM_USE_FLEXPWM1
#error "PWM driver activated but no SubModule assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   PWM mode type.
 */
typedef uint32_t pwmmode_t;

/**
 * @brief   PWM channel type.
 */
typedef uint8_t pwmchannel_t;

/**
 * @brief   PWM counter type.
 */
typedef uint16_t pwmcnt_t;

/**
 * @brief   PWM driver channel configuration structure.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  pwmmode_t                 mode;
  /**
   * @brief Channel callback pointer.
   * @note  This callback is invoked on the channel compare event. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /* End of the mandatory fields.*/
} PWMChannelConfig;

/**
 * @brief   PWM driver configuration structure.
 */
typedef struct {
  /**
   * @brief   Timer clock in Hz.
   * @note    The low level can use assertions in order to catch invalid
   *          frequency specifications.
   */
  uint32_t                  frequency;
  /**
   * @brief   PWM period in ticks.
   * @note    The low level can use assertions in order to catch invalid
   *          period specifications.
   */
  pwmcnt_t                  period;
  /**
   * @brief Periodic callback pointer.
   * @note  This callback is invoked on PWM counter reset. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /**
   * @brief Channels configurations.
   */
  PWMChannelConfig          channels[PWM_CHANNELS];
  /* End of the mandatory fields.*/
  /**
   * @brief PWM functional mode.
   */
  pwmmode_t                 mode;
} PWMConfig;

/**
 * @brief   Structure representing a PWM driver.
 */
struct PWMDriver {
  /**
   * @brief Driver state.
   */
  pwmstate_t                state;
  /**
   * @brief Current driver configuration data.
   */
  const PWMConfig           *config;
  /**
   * @brief   Current PWM period in ticks.
   */
  pwmcnt_t                  period;
#if defined(PWM_DRIVER_EXT_FIELDS)
  PWM_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @Pointer to the volatile FlexPWM registers block.
   */
  volatile struct spc5_flexpwm *flexpwmp;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if SPC5_PWM_USE_SMOD0 && !defined(__DOXYGEN__)
extern PWMDriver PWMD1;
#endif

#if SPC5_PWM_USE_SMOD1 && !defined(__DOXYGEN__)
extern PWMDriver PWMD2;
#endif

#if SPC5_PWM_USE_SMOD2 && !defined(__DOXYGEN__)
extern PWMDriver PWMD3;
#endif

#if SPC5_PWM_USE_SMOD3 && !defined(__DOXYGEN__)
extern PWMDriver PWMD4;
#endif

#if SPC5_PWM_USE_SMOD4 && !defined(__DOXYGEN__)
extern PWMDriver PWMD5;
#endif

#if SPC5_PWM_USE_SMOD5 && !defined(__DOXYGEN__)
extern PWMDriver PWMD6;
#endif

#if SPC5_PWM_USE_SMOD6 && !defined(__DOXYGEN__)
extern PWMDriver PWMD7;
#endif

#if SPC5_PWM_USE_SMOD7 && !defined(__DOXYGEN__)
extern PWMDriver PWMD8;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void pwm_lld_init(void);
  void pwm_lld_start(PWMDriver *pwmp);
  void pwm_lld_stop(PWMDriver *pwmp);
  void pwm_lld_enable_channel(PWMDriver *pwmp,
                              pwmchannel_t channel,
                              pwmcnt_t width);
  void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel);
  void pwm_lld_change_period(PWMDriver *pwmp, pwmcnt_t period);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PWM */

#endif /* _PWM_LLD_H_ */

/** @} */
