/*******************************************************************************
* File Name: C_Reg_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "C_Reg.h"

/* Check for removal by optimization */
#if !defined(C_Reg_Sync_ctrl_reg__REMOVED)

static C_Reg_BACKUP_STRUCT  C_Reg_backup = {0u};

    
/*******************************************************************************
* Function Name: C_Reg_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void C_Reg_SaveConfig(void) 
{
    C_Reg_backup.controlState = C_Reg_Control;
}


/*******************************************************************************
* Function Name: C_Reg_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void C_Reg_RestoreConfig(void) 
{
     C_Reg_Control = C_Reg_backup.controlState;
}


/*******************************************************************************
* Function Name: C_Reg_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void C_Reg_Sleep(void) 
{
    C_Reg_SaveConfig();
}


/*******************************************************************************
* Function Name: C_Reg_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void C_Reg_Wakeup(void)  
{
    C_Reg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
