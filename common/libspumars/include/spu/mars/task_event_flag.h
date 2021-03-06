#ifndef __MARS_TASK_EVENT_FLAG_H__
#define __MARS_TASK_EVENT_FLAG_H__

#include <stdint.h>

#include <mars/task_event_flag_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_mars_task_event_flag
 * \brief <b>[host/MPU]</b> Clears the bits specified in the task event flag.
 *
 * This function will clear all bits currently set in the event flag.
 * Tasks waiting on some events will remain in the waiting state.
 *
 * <b>Key Parameters</b>:
 * \n \n
 * \e bits
 * - Specify only the bits you want to be cleared from the event flag bits.
 *
 * \param[in] event_flag_ea	- ea of initialized event flag instance
 * \param[in] bits		- bits to clear
 * \return
 *	MARS_SUCCESS		- successfully cleared event flag bits
 * \n	MARS_ERROR_NULL		- ea is 0\n
 * \n	MARS_ERROR_ALIGN	- ea not aligned properly
 */
int mars_task_event_flag_clear(uint64_t event_flag_ea, uint32_t bits);

/**
 * \ingroup group_mars_task_event_flag
 * \brief <b>[host/MPU]</b> Sets the bits specified in the task event flag.
 *
 * This function will set the bits specified. The bits are OR'd with bits
 * already set in the event flag at the time of this call.
 * If there are any tasks in the waiting state, and this call satisfies the
 * release condition of those tasks, all those tasks will be returned to the
 * ready state.
 *
 * <b>Key Parameters</b>:
 * \n \n
 * \e bits
 * - Specify only the bits you want to set in the event flag bits.
 *
 * \param[in] event_flag_ea	- ea of initialized event flag instance
 * \param[in] bits		- bits to set
 * \return
 *	MARS_SUCCESS		- successfully cleared event flag bits
 * \n	MARS_ERROR_NULL		- ea is 0
 * \n	MARS_ERROR_ALIGN	- ea not aligned properly
 * \n	MARS_ERROR_STATE	- invalid direction
 */
int mars_task_event_flag_set(uint64_t event_flag_ea, uint32_t bits);

/**
 * \ingroup group_mars_task_event_flag
 * \brief <b>[host/MPU]</b> Waits on a task event flag.
 * <b>(Task Switch Call)</b>
 *
 * \note The <b>[MPU]</b> call may result in a task switch and put this
 * task into the waiting state. Understand all the limitations before calling
 * a <b>Task Switch Call</b> (<b>See</b> \ref sec_7_5).
 *
 * This call will put the task into a waiting state until the specified event
 * flag condition is met.
 *
 * <b>Key Parameters</b>:
 * \n \n
 * \e mask
 * - Specify only the bits you want to test against in the event flag bits set.
 * - Whether the test condition is satisfied or not will depend on \e mask_mode.
 *
 * \e mask_mode
 * - Specify how to test the mask bits against the event flag bits set.
 * - Specify \ref MARS_TASK_EVENT_FLAG_MASK_OR (\e mask | event flag bits), so
 * the condition is satisfied if any bits specified in \e mask is set in the
 * event flag bits.
 * - Specify \ref MARS_TASK_EVENT_FLAG_MASK_AND (\e mask & event flag bits) so
 * the condition is satisfied if all bits specified in \e mask are set in the
 * event flag bits.
 *
 * \e bits
 * - Specify a pointer to a variable where the event flag bits can be returned.
 * - The resulting bits will be the state of bits in the event flag prior to any
 * automatic clearing of bits (if \ref MARS_TASK_EVENT_FLAG_CLEAR_AUTO was
 * specified at creation).
 * - The returned bits are only valid when MARS_SUCCESS is returned.
 *
 * \param[in] event_flag_ea	- ea of initialized event flag instance
 * \param[in] mask		- bit mask to test event flag bits against
 * \param[in] mask_mode		- specifies how to mask bits (AND, OR)
 * \param[out] bits		- pointer of instance to return bits state
 * \return
 *	MARS_SUCCESS		- successfully received event
 * \n	MARS_ERROR_NULL		- ea is 0
 * \n	MARS_ERROR_ALIGN	- ea not aligned properly
 * \n	MARS_ERROR_PARAMS	- invalid mask_mode
 * \n	MARS_ERROR_STATE	- invalid direction
 * \n	MARS_ERROR_LIMIT	- exceeded limit of max waiting tasks
 * \n	MARS_ERROR_FORMAT	- no context save area specified
 */
int mars_task_event_flag_wait(uint64_t event_flag_ea,
			      uint32_t mask, uint8_t mask_mode,
			      uint32_t *bits);

/**
 * \ingroup group_mars_task_event_flag
 * \brief <b>[host/MPU]</b> Waits on a task event flag.
 *
 * This call will test to see if the specified event flag condition is met
 * returns immediately with \ref  MARS_ERROR_BUSY if it did not.
 *
 * <b>Key Parameters</b>:
 * \n \n
 * \e mask
 * - Specify only the bits you want to test against in the event flag bits set.
 * - Whether the test condition is satisfied or not will depend on \e mask_mode.
 *
 * \e mask_mode
 * - Specify how to test the mask bits against the event flag bits set.
 * - Specify \ref MARS_TASK_EVENT_FLAG_MASK_OR (\e mask | event flag bits), so
 * the condition is satisfied if any bits specified in \e mask is set in the
 * event flag bits.
 * - Specify \ref MARS_TASK_EVENT_FLAG_MASK_AND (\e mask & event flag bits) so
 * the condition is satisfied if all bits specified in \e mask are set in the
 * event flag bits.
 *
 * \e bits
 * - Specify a pointer to a variable where the event flag bits can be returned.
 * - The resulting bits will be the state of bits in the event flag prior to any
 * automatic clearing of bits (if \ref MARS_TASK_EVENT_FLAG_CLEAR_AUTO was
 * specified at creation).
 * - The returned bits are only valid when MARS_SUCCESS is returned.
 *
 * \param[in] event_flag_ea	- ea of initialized event flag instance
 * \param[in] mask		- bit mask to test event flag bits against
 * \param[in] mask_mode		- specifies how to mask bits (AND, OR)
 * \param[out] bits		- pointer of instance to return bits state
 * \return
 *	MARS_SUCCESS		- successfully received event
 * \n	MARS_ERROR_NULL		- ea is 0
 * \n	MARS_ERROR_ALIGN	- ea not aligned properly
 * \n	MARS_ERROR_PARAMS	- invalid mask_mode
 * \n	MARS_ERROR_STATE	- invalid direction
 * \n	MARS_ERROR_BUSY		- event not yet received
 */
int mars_task_event_flag_try_wait(uint64_t event_flag_ea,
				  uint32_t mask, uint8_t mask_mode,
				  uint32_t *bits);

#ifdef __cplusplus
	}
#endif

#endif
