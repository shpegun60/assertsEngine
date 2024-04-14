#include "assert_engine.h"
#include <stdio.h>
#include <stdarg.h>

#ifndef NDEBUG /* ---------------------------------------------------------------------------------------------------------- */

#include <assert.h>

#define __M_IF_ASSERT_ADDITION_DATA(msg) (((msg)[0] == '[') && ((msg)[2] == ']'))
#define __M_ASSERT_DATA(msg) ((msg)[1])

static inline void __M_SEND_ASSERT_MSG(const char* const header,
                                const char* const expr_str, const unsigned char expr,
                                const char* const file, const int line, const char* const func_name,
                                const char* const msg, va_list args)
{
#if !defined(M_ASSERT_MSG_TEXT_DISABLE)
    int assertEna 	= 1;
    char* descr 	= 0;
    const int _additional_data_ex = __M_IF_ASSERT_ADDITION_DATA(msg);

    if(_additional_data_ex) {

        switch(__M_ASSERT_DATA(msg)) {

        case 'd':
            // get library info
            assertEna = va_arg(args, const int);
            descr = va_arg(args, char*);
            break;

        case 's':
            // get library info
            assertEna = 1;
            descr = va_arg(args, char*);
            break;

        case 'e':
            // get library info
            assertEna   = va_arg(args, const int);
            descr       = 0;
            break;

        case '0':
            descr = va_arg(args, char*);
#	if !defined(M_MESSAGE_ALWAYS_ENABLE)
            return;
#   endif /* !defined(M_MESSAGE_ALWAYS_ENABLE) */
            break;

        default:  descr = va_arg(args, char*); break;

        }

    }
    (void)assertEna;
#endif /* defined(M_ASSERT_MSG_TEXT_DISABLE) */


#if !defined(M_MESSAGE_ALWAYS_ENABLE) && !defined(M_ASSERT_MSG_TEXT_DISABLE)
    // send message if enabled message
    if(assertEna) {
#endif /* !defined(M_MESSAGE_ALWAYS_ENABLE) && !defined(M_ASSERT_MSG_TEXT_DISABLE) */

        // print header-------------------------------------------------------
        fprintf(stderr, "\n%s\n", header);
        // print function if enable ------------------------------------------
#if !defined(M_ASSERT_FUNCTION_NAME_TEXT_DISABLE)
        fprintf(stderr, "Function:\t%s \n", func_name);
#endif /* !defined(M_ASSERT_FUNCTION_NAME_TEXT_DISABLE) */

#if !defined(M_ASSERT_MSG_TEXT_DISABLE)
        // print library name if exists and enable ------------------------------------------
        if(descr) {
            fprintf(stderr, "Library Name:\t%s\n", descr);
        }
        // print msg text if enable ------------------------------------------
        fprintf(stderr, "Assert failed:\t");
        if(_additional_data_ex) {
            vfprintf(stderr, &msg[3], args);
        } else {
            vfprintf(stderr, msg, args);
        }
        fprintf(stderr, "\n");
#endif /* defined(M_ASSERT_MSG_TEXT_DISABLE) */

        // print expression text if enable ------------------------------------------
#if !defined(M_ASSERT_EXPR_DISABLE)
        fprintf(stderr, "Expression:\t%s, value: %d\n", expr_str, expr);
#endif /* defined(M_ASSERT_EXPR_TEXT_DISABLE) */

        // print file & line if enable ------------------------------------------
#if !defined(M_ASSERT_FILE_LINE_TEXT_DISABLE)
            fprintf(stderr, "Source:\t\t%s, line: %d\n", file, line);
#endif /* defined(M_ASSERT_FILE_LINE_TEXT_DISABLE) */

        fflush(stderr);
#if !defined(M_MESSAGE_ALWAYS_ENABLE) && !defined(M_ASSERT_MSG_TEXT_DISABLE)
    }
#endif /* !defined(M_MESSAGE_ALWAYS_ENABLE) && !defined(M_ASSERT_MSG_TEXT_DISABLE) */

    (void)header;
    (void)expr_str;
    (void)expr;
    (void)file;
    (void)line;
    (void)func_name;
    (void)msg;
    (void)args;
}

void __M_Error(const char* const expr_str, const unsigned char expr,
                            const char* const file, const int line, const char* const func_name,
                            const char* const msg, ...)
{
    va_list args;
    va_start(args, msg);
    __M_SEND_ASSERT_MSG("PROGRAMM EXIT WITH ERROR!!!", expr_str, expr, file, line, func_name, msg, args);
    va_end(args);
    //abort(); // exit programm
}

void __M_Warning(const char* const expr_str, const unsigned char expr,
                            const char* const file, const int line, const char* const func_name,
                            const char* const msg, ...)
{
    va_list args;
    va_start(args, msg);
    __M_SEND_ASSERT_MSG("WARNING!!!", expr_str, expr, file, line, func_name, msg, args);
    va_end(args);
}

#undef __M_IF_ASSERT_ADDITION_DATA
#undef __M_ASSERT_DATA

#endif /* NDEBUG ---------------------------------------------------------------------------------------------------------- */

void __M_DBG(const char* const msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\n");
    fflush(stdout);
    va_end(args);
}

void __M_DBG_ERR(const char* const msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    fflush(stderr);
    va_end(args);
}

void __M_DBG_FILE(FILE * file, const char* const msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(file, msg, args);
    fprintf(file, "\n");
    fflush(file);
    va_end(args);
}

void __M_assert_test()
{
    int i = 1;
    M_Assert_Break(1, M_EMPTY, M_EMPTY, "RUNTIME ERROR Assert test: M_Assert_Break without parameters");
    M_Assert_Break(1, M_EMPTY, M_EMPTY, "RUNTIME ERROR Assert test: M_Assert_Break with parameter: %d", 123);
    M_Assert_Break(1, M_EMPTY, M_EMPTY, "RUNTIME ERROR Assert test:" "M_Assert_Break with two parameter: %d, %d", 123, 456);


    M_Assert_Warning(1, M_EMPTY, M_EMPTY, "RUNTIME WARNING Assert test: M_Assert_Break without parameters");
    M_Assert_Warning(1, ++i, M_EMPTY, "RUNTIME WARNING Assert test: M_Assert_Break with parameter: %d", i);
    M_Assert_Warning(1, M_EMPTY, ++i, "RUNTIME WARNING Assert test: M_Assert_Break with two parameter: %d, %d", i, 456);
    M_Assert_Warning(1, M_EMPTY, M_EMPTY, "RUNTIME WARNING Assert test:" "M_Assert_Break with two parameter: %d, %d", i, 456);
    M_Assert_Break(1, ++i, M_EMPTY, "RUNTIME ERROR Assert test: M_Assert_Break with two parameter: %d, %d", i, 456);

    M_Assert_Break(1, ++i, M_EMPTY, M_LIB_DATA_DEF"With library: M_Assert_Break with two parameter: %d, %d", 0, "hui", i, 456);
    i=0;
    M_Assert_SafeFunctionCall(i, printf("hello "));
    (void)i;
}





