/*******************************************************************************
* File Name: Port_D.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Port_D.h"

static Port_D_BACKUP_STRUCT  Port_D_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Port_D_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Port_D_SUT.c usage_Port_D_Sleep_Wakeup
*******************************************************************************/
void Port_D_Sleep(void)
{
    #if defined(Port_D__PC)
        Port_D_backup.pcState = Port_D_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Port_D_backup.usbState = Port_D_CR1_REG;
            Port_D_USB_POWER_REG |= Port_D_USBIO_ENTER_SLEEP;
            Port_D_CR1_REG &= Port_D_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Port_D__SIO)
        Port_D_backup.sioState = Port_D_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Port_D_SIO_REG &= (uint32)(~Port_D_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Port_D_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Port_D_Sleep() for an example usage.
*******************************************************************************/
void Port_D_Wakeup(void)
{
    #if defined(Port_D__PC)
        Port_D_PC = Port_D_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Port_D_USB_POWER_REG &= Port_D_USBIO_EXIT_SLEEP_PH1;
            Port_D_CR1_REG = Port_D_backup.usbState;
            Port_D_USB_POWER_REG &= Port_D_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Port_D__SIO)
        Port_D_SIO_REG = Port_D_backup.sioState;
    #endif
}


/* [] END OF FILE */
