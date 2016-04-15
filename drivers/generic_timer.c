#include <stdio.h>
#include <arch/armv7.h>
#include <arch/irq.h>

#include <core/timer.h>

#include <config.h>

#define NS_PL2_PTIMER_IRQ   26
#define NS_VTIMER_IRQ       27
#define PL1_PTIMER_IRQ      29
#define NS_PL1_PTIMER_IRQ   30

enum generic_timer_type {
    GENERIC_TIMER_HYP,      /* IRQ 26 PL2 Hyp */
    GENERIC_TIMER_VIR,      /* IRQ 27 Virtual */
    GENERIC_TIMER_NSP,      /* IRQ 30 Non-secure Physical */
    GENERIC_TIMER_NUM_TYPES
};

enum {
    GENERIC_TIMER_REG_FREQ,
    GENERIC_TIMER_REG_HCTL,
    GENERIC_TIMER_REG_KCTL,
    GENERIC_TIMER_REG_HYP_CTRL,
    GENERIC_TIMER_REG_HYP_TVAL,
    GENERIC_TIMER_REG_HYP_CVAL,
    GENERIC_TIMER_REG_PHYS_CTRL,
    GENERIC_TIMER_REG_PHYS_TVAL,
    GENERIC_TIMER_REG_PHYS_CVAL,
    GENERIC_TIMER_REG_VIRT_CTRL,
    GENERIC_TIMER_REG_VIRT_TVAL,
    GENERIC_TIMER_REG_VIRT_CVAL,
    GENERIC_TIMER_REG_VIRT_OFF,
};

#define GENERIC_TIMER_CTRL_ENABLE       (1 << 0)
#define GENERIC_TIMER_CTRL_IMASK        (1 << 1)
#define GENERIC_TIMER_CTRL_ISTATUS      (1 << 2)

static inline void generic_timer_reg_write(int reg, uint32_t val)
{
    switch (reg) {
    case GENERIC_TIMER_REG_FREQ:
        write_cntfrq(val);
        break;
    case GENERIC_TIMER_REG_HCTL:
        write_cnthctl(val);
        break;
    case GENERIC_TIMER_REG_KCTL:
        write_cntkctl(val);
        break;
    case GENERIC_TIMER_REG_HYP_CTRL:
        write_cnthp_ctl(val);
        break;
    case GENERIC_TIMER_REG_HYP_TVAL:
        write_cnthp_tval(val);
        break;
    case GENERIC_TIMER_REG_PHYS_CTRL:
        write_cntp_ctl(val);
        break;
    case GENERIC_TIMER_REG_PHYS_TVAL:
        write_cntp_tval(val);
        break;
    case GENERIC_TIMER_REG_VIRT_CTRL:
        write_cntv_ctl(val);
        break;
    case GENERIC_TIMER_REG_VIRT_TVAL:
        write_cntv_tval(val);
        break;
    default:
        printf("Trying to write invalid generic-timer register\n\r");
        break;
    }
    isb();
}

static inline uint32_t generic_timer_reg_read(int reg)
{
    uint32_t val;
    switch (reg) {
    case GENERIC_TIMER_REG_FREQ:
        val = read_cntfrq();
        break;
    case GENERIC_TIMER_REG_HCTL:
        val = read_cnthctl();
        break;
    case GENERIC_TIMER_REG_KCTL:
        val = read_cntkctl();
        break;
    case GENERIC_TIMER_REG_HYP_CTRL:
        val = read_cnthp_ctl();
        break;
    case GENERIC_TIMER_REG_HYP_TVAL:
        val = read_cnthp_tval();
        break;
    case GENERIC_TIMER_REG_PHYS_CTRL:
        val = read_cntp_ctl();
        break;
    case GENERIC_TIMER_REG_PHYS_TVAL:
        val = read_cntp_tval();
        break;
    case GENERIC_TIMER_REG_VIRT_CTRL:
        val = read_cntv_ctl();
        break;
    case GENERIC_TIMER_REG_VIRT_TVAL:
        val = read_cntv_tval();
        break;
    default:
        printf("Trying to read invalid generic-timer register\n\r");
        break;
    }
    return val;
}

static inline void generic_timer_reg_write64(int reg, uint64_t val)
{
    switch (reg) {
    case GENERIC_TIMER_REG_HYP_CVAL:
        write_cnthp_cval(val);
        break;
    case GENERIC_TIMER_REG_PHYS_CVAL:
        write_cntp_cval(val);
        break;
    case GENERIC_TIMER_REG_VIRT_CVAL:
        write_cntv_cval(val);
        break;
    case GENERIC_TIMER_REG_VIRT_OFF:
        write_cntvoff(val);
        break;
    default:
        printf("Trying to write invalid generic-timer register\n\r");
        break;
    }
    isb();
}

static inline uint64_t generic_timer_reg_read64(int reg)
{
    uint64_t val;
    switch (reg) {
    case GENERIC_TIMER_REG_HYP_CVAL:
        val = read_cnthp_cval();
        break;
    case GENERIC_TIMER_REG_PHYS_CVAL:
        val = read_cntp_tval();
        break;
    case GENERIC_TIMER_REG_VIRT_CVAL:
        val = read_cntv_cval();
        break;
    case GENERIC_TIMER_REG_VIRT_OFF:
        val = read_cntvoff();
        break;
    default:
        printf("Trying to read invalid generic-timer register\n\r");
        break;
    }
    return val;
}

/** @brief Configures time interval by PL2 physical timerValue register.
 *  Read CNTHP_TVAL into R0.
 *
 *  "CNTHP_TVAL" characteristics
 *  -Holds the timer values for the Hyp mode physical timer.
 *  -Only accessible from Hyp mode, or from
 *   Monitor mode when SCR.NS is  set to 1.
 */
static hvmm_status_t generic_timer_set_tval(enum generic_timer_type timer_type,
                                            uint32_t tval)
{
    hvmm_status_t result = HVMM_STATUS_UNSUPPORTED_FEATURE;

    if (timer_type == GENERIC_TIMER_HYP) {
        generic_timer_reg_write(GENERIC_TIMER_REG_HYP_TVAL, tval);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_VIR) {
        generic_timer_reg_write(GENERIC_TIMER_REG_VIRT_TVAL, tval);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_NSP) {
        generic_timer_reg_write(GENERIC_TIMER_REG_PHYS_TVAL, tval);
        result = HVMM_STATUS_SUCCESS;
    }

    return result;
}

static hvmm_status_t generic_timer_set_cval(enum generic_timer_type timer_type,
                                            uint64_t cval)
{
    hvmm_status_t result = HVMM_STATUS_UNSUPPORTED_FEATURE;

    if (timer_type == GENERIC_TIMER_HYP) {
        generic_timer_reg_write64(GENERIC_TIMER_REG_HYP_CVAL, cval);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_VIR) {
        generic_timer_reg_write64(GENERIC_TIMER_REG_VIRT_CVAL, cval);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_NSP) {
        generic_timer_reg_write64(GENERIC_TIMER_REG_PHYS_CVAL, cval);
        result = HVMM_STATUS_SUCCESS;
    }

    return result;
}

/** @brief Enables the timer interrupt such as hypervisor timer event
 *  by PL2 Physical Timer Control register(VMSA : CNTHP_CTL)
 *  The Timer output signal is not masked.
 *
 *  The Cortex-A15 processor implements a 5-bit version of the interrupt
 *  priority field for 32 interrupt priority levels.
 */
static hvmm_status_t generic_timer_enable(enum generic_timer_type timer_type)
{
    uint32_t ctrl;
    hvmm_status_t result = HVMM_STATUS_UNSUPPORTED_FEATURE;

    if (timer_type == GENERIC_TIMER_HYP) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_HYP_CTRL);
        ctrl |= GENERIC_TIMER_CTRL_ENABLE;
        ctrl &= ~GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_HYP_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_VIR) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_VIRT_CTRL);
        ctrl |= GENERIC_TIMER_CTRL_ENABLE;
        ctrl &= ~GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_VIRT_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_NSP) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_PHYS_CTRL);
        ctrl |= GENERIC_TIMER_CTRL_ENABLE;
        ctrl &= ~GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_PHYS_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    }

    return result;
}

/** @brief Disable the timer interrupt such as hypervisor timer event
 *  by PL2 physical timer control register.The Timer output signal is not masked.
 */
static hvmm_status_t generic_timer_disable(enum generic_timer_type timer_type)
{
    uint32_t ctrl;
    hvmm_status_t result = HVMM_STATUS_UNSUPPORTED_FEATURE;

    if (timer_type == GENERIC_TIMER_HYP) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_HYP_CTRL);
        ctrl &= ~GENERIC_TIMER_CTRL_ENABLE;
        ctrl |= GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_HYP_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_VIR) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_VIRT_CTRL);
        ctrl &= ~GENERIC_TIMER_CTRL_ENABLE;
        ctrl |= GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_VIRT_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    } else if (timer_type == GENERIC_TIMER_NSP) {
        ctrl = generic_timer_reg_read(GENERIC_TIMER_REG_PHYS_CTRL);
        ctrl &= ~GENERIC_TIMER_CTRL_ENABLE;
        ctrl |= GENERIC_TIMER_CTRL_IMASK;
        generic_timer_reg_write(GENERIC_TIMER_REG_PHYS_CTRL, ctrl);
        result = HVMM_STATUS_SUCCESS;
    }

    return result;
}

static hvmm_status_t timer_disable()
{
    return generic_timer_disable(GENERIC_TIMER_HYP);
}

static hvmm_status_t timer_enable()
{
    return generic_timer_enable(GENERIC_TIMER_HYP);
}

static hvmm_status_t timer_set_cval(uint64_t val)
{
    return generic_timer_set_cval(GENERIC_TIMER_HYP, val);
}

uint32_t have_set_cval_by_delta_ever_called[NR_CPUS] = {0};
static hvmm_status_t timer_set_cval_by_delta(uint64_t val)
{
    uint64_t previous_cval; /* FIXME:(igkang) this calculation have to be moved to timer.c */

    if (have_set_cval_by_delta_ever_called[NR_CPUS]) {
        previous_cval = generic_timer_reg_read64(GENERIC_TIMER_REG_HYP_CVAL);
        val = previous_cval + val;
    } else { /* when if this is the very first call of timer_set_cval_by_delta */
        previous_cval = read_cntpct();
        val = previous_cval + val;
    }
    return generic_timer_set_cval(GENERIC_TIMER_HYP, val);
}

static hvmm_status_t timer_set_tval(uint32_t tval)
{
    return generic_timer_set_tval(GENERIC_TIMER_HYP, tval);
}

/** @brief dump at time.
 *  @todo have to write dump with meaningful printing.
 */
static hvmm_status_t timer_dump(void)
{
    return HVMM_STATUS_SUCCESS;
}

static uint64_t timer_read_phys_counter(void) {
    return read_cntpct();
}

#if 0
static uint64_t timer_read_virt_counter(void) {
    return read_cntvct();
}
#endif

/* TODO:(igkang) add/rename functions - by phys/virt, Hyp/Normal */
struct timer_ops _timer_ops = {
    .enable = timer_enable,
    .disable = timer_disable,
    .get_counter = timer_read_phys_counter,
    .set_absolute = timer_set_cval,
    .set_interval_relative = timer_set_tval,
    .set_interval_absolute = timer_set_cval_by_delta,
    .dump = timer_dump,
};

struct timer_module _timer_module = {
    .name = "K-Hypervisor Timer Module",
    .author = "Kookmin Univ.",
    .ops = &_timer_ops,
};
