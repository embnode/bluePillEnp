#include "enp_root.h"
#include "flash.h"
#include "stm32f1xx_hal.h"

__usrdata ENP_Data_t DEVICE_UsrData; // Данные пользовательской конфигурации
static uint32_t DEVICE_Error = 0; // Флаги ошибок

const ENP_Node_t* pEnpNodeList[ENP_NODENUM];

// Attributes device
const ENP_Attr_t ENP_ROOT_VAR_ATTR[ENP_ROOT_VAR_NUM] = {
    { "Error code", ENP_TYPE_HEX | ENP_PROP_ERROR },
    { "Device id", ENP_TYPE_UINT | ENP_PROP_READONLY },
    { "Up time (hh:mm:ss)", ENP_TYPE_TIME | ENP_PROP_READONLY },
};

// function supply configuration
static uint16_t _varGet(uint16_t, uint16_t, void*);
static uint16_t _varSet(uint16_t, uint16_t, void*);

static const ENP_Node_t enpAppNodeList[] = {
    { "ENP_Demo", NODE_ROOT, NODE_ROOT, ENP_ROOT_VAR_NUM, ENP_ROOT_VAR_ATTR,
        _varGet, _varSet, ENP_VarGetAttr, ENP_NodeName },
};

void ENP_DevInit()
{
    ENP_Init(pEnpNodeList, ENP_NODENUM, 0, FLASH_APP_Erase, FLASH_APP_Write);
    ENP_InsertNode(enpAppNodeList, sizeof(enpAppNodeList) / sizeof(ENP_Node_t));
}

// Read variable
uint16_t _varGet(uint16_t nodeid, uint16_t varid, void* value)
{
    if (value)
        switch (nodeid) {
        case NODE_ROOT:
            switch (varid) {
            case ENP_ROOT_VAR_ERROR:
                *(uint32_t*)value = DEVICE_Error;
                break;
            case ENP_ROOT_VAR_DEV_ID:
                *(uint32_t*)value = 0;
                break;
            case ENP_ROOT_VAR_TIME:
                *(uint32_t*)value = HAL_GetTick();
                break;
            default:
                return ENP_ERROR_VARID;
            }
            break;
        default:
            return ENP_ERROR_NODEID;
        }
    return ENP_ERROR_NONE;
}

// Write variables
uint16_t _varSet(uint16_t nodeid, uint16_t varid, void* value)
{
    if (value)
        switch (nodeid) {
        case NODE_ROOT:
            switch (varid) {
            case ENP_ROOT_VAR_ERROR:
                DEVICE_Error = *(uint32_t*)value;
                break;
            case ENP_ROOT_VAR_DEV_ID:
                // P_Pars.DevId = *(uint32_t *)value; // TODO
                break;
            default:
                return ENP_ERROR_VARID;
            }
            break;
        default:
            return ENP_ERROR_NODEID;
        }
    return ENP_ERROR_NONE;
}
