#ifndef __SMART_ASSERT
#define __SMART_ASSERT

#include <assert.h>

// this library must include only .c file!!!!!!!!!!!!!!!!

//#define NDEBUG


void __M_Assert(const char* expr_str, unsigned char expr, const char* file, int line, const char* msg);
void __M_Error(const char* expr_str, unsigned char expr, const char* file, int line, const char* msg);
void __M_Error_variadic(const char* expr_str, unsigned char expr, const char* file, int line, const char* msg, ...);
void __M_Warning(const char* expr_str, unsigned char expr, const char* file, int line, const char* msg);
void __M_valueObserver(const char* msg, ...);

#ifndef NDEBUG

/*
 * ***********************************************************************************************************************************************
 *  defines for break program and dont save checking when NDEBUG
 * ***********************************************************************************************************************************************
 */

#   define M_Assert_Break(Expr, Msg, afterExpr)\
    do{\
        if (Expr) {\
            __M_Error((#Expr), (Expr), (__FILE__), (__LINE__), (Msg));\
            afterExpr;\
        }\
    }while(0L)


#   define M_Assert_Break_var(Expr, beforeExpr, afterExpr, Msg, arg...)\
    do{\
        if (Expr) {\
            beforeExpr;\
            __M_Error_variadic((#Expr), (Expr), (__FILE__), (__LINE__), (Msg), ##arg);\
            afterExpr;\
        }\
    }while(0L)

/*
 * ***********************************************************************************************************************************************
 *  defines for break program and save checking when NDEBUG (WARNING!!! only after breakExpr saving)
 * ***********************************************************************************************************************************************
 */

#   define M_Assert_BreakSaveCheck(Expr, Msg, afterExpr)\
    do{\
        if (Expr) {\
            __M_Error((#Expr), (Expr), (__FILE__), (__LINE__), (Msg));\
            afterExpr;\
        }\
    }while(0L)

/*
 * ***********************************************************************************************************************************************
 *  defines no break program
 * ***********************************************************************************************************************************************
 */

#   define M_Assert_Warning(Expr, Msg)\
    do{\
        if (Expr) {\
            __M_Warning((#Expr), (Expr), (__FILE__), (__LINE__), (Msg));\
        }\
    }while(0L)

#   define M_Assert_WarningSaveCheck(Expr, Msg, afterExpr)\
    do{\
        if (Expr) {\
            __M_Warning((#Expr), (Expr), (__FILE__), (__LINE__), (Msg));\
            afterExpr;\
        }\
    }while(0L)


#else
#   define M_Assert_Break(Expr, Msg, afterExpr)
#   define M_Assert_Break_par(Expr, beforeExpr, afterExpr, Msg, arg...)

#   define M_Assert_BreakSaveCheck(Expr, Msg, afterExpr)\
    do{\
        if (Expr) {\
            afterExpr;\
        }\
    }while(0L)

#   define M_Assert_Warning(Expr, Msg)

#   define M_Assert_WarningSaveCheck(Expr, Msg, afterExpr)\
    do{\
        if (Expr) {\
            afterExpr;\
        }\
    }while(0L)
#endif





#define PRINT_ONCE(...) \
    do{ \
        static int __printed = 0; \
        if(!__printed) { \
            printf(__VA_ARGS__); \
            __printed=1; \
        } \
    }while(0L)


#define TO_TXT(a) #a

#endif // __SMART_ASSERT
