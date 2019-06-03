#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

//------------------------------------------------------------------------------
#define errorHandler(msg)\
    do{\
        perror(msg);\
        return -1;\
    }while(0)

//------------------------------------------------------------------------------
#endif // ERROR_HANDLER_H

