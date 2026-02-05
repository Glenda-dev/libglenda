#ifndef _STDARG_H
#define _STDARG_H

/* 定义 va_list 类型 */
typedef __builtin_va_list va_list;

/* 初始化 ap，last 是变参前的最后一个固定参数 */
#define va_start(ap, last) __builtin_va_start(ap, last)

/* 结束处理 */
#define va_end(ap) __builtin_va_end(ap)

/* 获取下一个参数，type 为参数类型 */
#define va_arg(ap, type) __builtin_va_arg(ap, type)

/* 复制 va_list (C99 新增) */
#define va_copy(dest, src) __builtin_va_copy(dest, src)

#endif /* _STDARG_H */