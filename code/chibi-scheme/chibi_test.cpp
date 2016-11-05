// #include <chibi/eval.h>
// #include <chibi/features.h>
#include <dlfcn.h>
#include <chibi/sexp.h>

// extern "C" SEXP_API sexp sexp_c_string(sexp ctx, const char *str, sexp_sint_t slen);

void dostuff(sexp ctx)
{
    /* declare and preserve local variables */
    sexp_gc_var2(obj1, obj2);
    sexp_gc_preserve2(ctx, obj1, obj2);

    /* load a file containing Scheme code */
    obj1 = sexp_c_string(ctx, "../code/chibi-scheme/hello_world.scm", -1);
    sexp_load(ctx, obj1, NULL);

    /* eval a C string as Scheme code */
    sexp_eval_string(ctx, "(some scheme expression)", -1, NULL);

    /* construct a Scheme expression to eval */
    obj1 = sexp_intern(ctx, "my-procedure", -1);
    obj2 = sexp_cons(ctx, obj1, SEXP_NULL);
    sexp_eval(ctx, obj2, NULL);

    /* release the local variables */
    sexp_gc_release2(ctx);
}

// int main(int argc, char** argv)
int main(void)
{
    sexp ctx;
    ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
    sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
    sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 0);
    dostuff(ctx);
    sexp_destroy_context(ctx);
}
