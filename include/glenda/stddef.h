#ifndef _STDDEF_H
#define _STDDEF_H

/* NULL 定义 */
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

/* 基础类型：使用编译器内置宏 */
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
typedef __WCHAR_TYPE__ wchar_t;

/* C11 新增：最大对齐类型 */
#if __STDC_VERSION__ >= 201112L
typedef struct
{
    long long __ll __attribute__((__aligned__(__alignof__(long long))));
    long double __ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
#endif

/* offsetof 宏 */
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif /* _STDDEF_H */