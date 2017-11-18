#define STANDALONE 0
#define USE_INTERFACE 1
#include <scheme.h>
#include <scheme-private.h>

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr

// Based on https://github.com/dchest/tinyscheme/blob/master/example.c

pointer cube(scheme* sc, pointer args)
{
    if (sc == nullptr)
    {
        std::cerr << "error: scheme* sc is nullptr\n";
        return nullptr;
    }

    if (args == sc->NIL || !sc->vptr->is_number(sc->vptr->pair_car(args)))
    {
        return sc->NIL;
    }

    double value = sc->vptr->rvalue(sc->vptr->pair_car(args));
    return sc->vptr->mk_real(sc, value * value * value);
}

pointer display(scheme* sc, pointer args)
{
    if (sc == nullptr)
    {
        std::cerr << "error: scheme* sc is nullptr\n";
        return nullptr;
    }

    if (args != sc->NIL)
    {
        if (sc->vptr->is_string(sc->vptr->pair_car(args)))
        {
            char* str = sc->vptr->string_value(sc->vptr->pair_car(args));
            printf("%s", str);
        }
    }
    return sc->NIL;
}

scheme* init_scheme()
{
    scheme* sc = scheme_init_new();

    if (sc == nullptr)
    {
        std::cerr << "error: scheme_init_new() failed\n";
        return nullptr;
    }

    FILE* init_file = fopen("init.scm", "r");

    if (init_file == nullptr)
    {
        std::cerr << "error loading init.scm\n";
        free(sc);
        return nullptr;
    }

    scheme_load_file(sc, init_file);
    fclose(init_file);

    sc->vptr->scheme_define(sc, sc->global_env, sc->vptr->mk_symbol(sc, "cube"), sc->vptr->mk_foreign_func(sc, cube));
    sc->vptr->scheme_define(sc, sc->global_env, sc->vptr->mk_symbol(sc, "display"), sc->vptr->mk_foreign_func(sc, display));

    return sc;
}

bool do_stuff(scheme* sc)
{
    if (sc == nullptr)
    {
        std::cerr << "error: scheme* sc is nullptr\n";
        return false;
    }

    FILE* hello_world_file = fopen("hello_world.scm", "r");

    if (hello_world_file == nullptr)
    {
        std::cerr << "error loading hello_world.scm\n";
        return false;
    }
    scheme_load_file(sc, hello_world_file);
    fclose(hello_world_file);

    /* eval a C string as Scheme code */
    const char* hello_world_char = "(display \"Hello world!\n\")";
    scheme_load_string(sc, hello_world_char);

    const char* cube_char = "(display (string-append \"5.0 cubed is \" (number->string (cube 5.0)) \"\n\"))";
    scheme_load_string(sc, cube_char);

    const char* see_you_char = "(display \"See you!\n\")";
    scheme_load_string(sc, see_you_char);

    return true;
}

int main(void)
{
    scheme* sc = init_scheme();

    if (sc == nullptr)
    {
        std::cerr << "error occurred in init_scheme function.\n";
        return 1;
    }

    if (!do_stuff(sc))
    {
        std::cerr << "error occurred in do_stuff function.\n";
        scheme_deinit(sc);
        return 1;
    }

    scheme_deinit(sc);
    return 0;
}
