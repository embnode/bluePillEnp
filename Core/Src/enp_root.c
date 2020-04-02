#include "enp_root.h"
#include "flash.h"
#include "stm32f1xx_hal.h"
#include "enStoring.h"
#include "eNode.h"

static uint32_t DEVICE_Error = 0; // Флаги ошибок

const ENP_Node_t* pEnpNodeList[ENP_NODENUM];

// Identificators for variables
enum ROOT_VAR {
    ROOT_VAR_ERROR, // error code
    ROOT_VAR_DEV_ID, // device id
    ROOT_VAR_TIME, // up time
    ROOT_VAR_NUM
};

// Attributes device
static const ENP_Attr_t attr[ROOT_VAR_NUM] = {
    { "Error code", ENP_TYPE_HEX | ENP_PROP_ERROR },
    { "Device id", ENP_TYPE_UINT | ENP_PROP_READONLY },
    { "Up time (hh:mm:ss)", ENP_TYPE_TIME | ENP_PROP_READONLY },
};

// function supply configuration
static uint16_t _varGet(uint16_t, uint16_t, void*);
static uint16_t _varSet(uint16_t, uint16_t, void*);

static const ENP_Node_t rootNodeList[] = {
    { "BluePill", NODE_ROOT, NODE_ROOT, ROOT_VAR_NUM, attr,
        _varGet, _varSet },
};

void ENP_DevInit()
{
    int nodeNum = GET_NODES_NUM(rootNodeList);
    ENP_NodeListInit(pEnpNodeList, ENP_NODENUM);
    ENP_InsertNodes(rootNodeList, nodeNum);
}

// Read variable
uint16_t _varGet(uint16_t nodeid, uint16_t varid, void* value)
{
    if (value)
        switch (nodeid) {
        case NODE_ROOT:
            switch (varid) {
            case ROOT_VAR_ERROR:
                *(uint32_t*)value = DEVICE_Error;
                break;
            case ROOT_VAR_DEV_ID:
                *(uint32_t*)value = 1;
                break;
            case ROOT_VAR_TIME:
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
            case ROOT_VAR_ERROR:
                DEVICE_Error = *(uint32_t*)value;
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
