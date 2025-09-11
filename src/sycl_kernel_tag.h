/* sycl_kernel_tag.h */
#ifndef SYCL_KERNEL_TAG_H
#define SYCL_KERNEL_TAG_H

#ifndef FILE_TAG
/* fallback if build system didn't inject FILE_TAG */
#define FILE_TAG FT_unknown_file
#endif

/* token-pasting helpers */
#define _KERNEL_PASTE2(a,b) a##_##b
#define _KERNEL_PASTE3(a,b,c) a##_##b##_##c
#define _KERNEL_PASTE4(a,b,c,d) a##_##b##_##c##_##d

/* Primary kernel identifier macro that does NOT use __COUNTER__.
   Reason: easier to declare at namespace scope and re-use the same name
   when instantiating parallel_for later in the same TU.
*/
#define KERNEL_NAME(f,o,s) _KERNEL_PASTE3(f, o, s)

/* Declare an empty struct at namespace scope for the composed name.
   Use this macro at top-level (not inside a function), after ORDER_TXT/SPIN_TXT
   are defined for that inclusion of work_lda_inc.c.
*/
#define DECLARE_KERNEL_TYPE_NSCOPE(f,o,s) \
  struct KERNEL_NAME(f,o,s) { };          \
  /* no alias here — the struct itself is the type */

/* Helper to expand the type name where you need it (inside the function) */
#define KERNEL_TYPE(f,o,s) KERNEL_NAME(f,o,s)

#endif /* SYCL_KERNEL_TAG_H */
