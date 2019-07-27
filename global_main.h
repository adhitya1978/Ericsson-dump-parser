#ifndef GLOBAL_MAIN_H
#define GLOBAL_MAIN_H

typedef struct MD_STRUCT    *MD;

typedef struct MFH_STRUCT   *MFH;

typedef struct NEID_STRUCT  *NEID;

typedef struct MI_STRUCT    *MI;

typedef struct MV_STRUCT    *MV;

typedef struct MDC_STRUCT   *MDC;

typedef enum _NODE_TYPE{

    NODE_TYPE_MD =0,

    NODE_TYPE_MFH,

    NODE_TYPE_NEID,

    NODE_TYPE_MI,

    NODE_TYPE_MV,

    NODE_TYPE_UKNOWN
}NODE_TYPE;



#endif // GLOBAL_MAIN_H
