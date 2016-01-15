#ifndef __CALLBACK_HPP_INCLUDED
#define __CALLBACK_HPP_INCLUDED

// callback typedefs in alphabetical order.
typedef bool (*BoolToBoolCallback)(bool);
typedef float (*BoolToFloatCallback)(bool);
typedef int (*BoolToIntCallback)(bool);
typedef void (*BoolToVoidCallback)(bool);
typedef bool (*FloatToBoolCallback)(float);
typedef float (*FloatToFloatCallback)(float);
typedef int (*FloatToIntCallback)(float);
typedef void (*FloatToVoidCallback)(float);
typedef bool (*IntToBoolCallback)(int);
typedef float (*IntToFloatCallback)(int);
typedef int (*IntToIntCallback)(int);
typedef void (*IntToVoidCallback)(int);
typedef bool (*VoidToBoolCallback)(void);
typedef float (*VoidToFloatCallback)(void);
typedef int (*VoidToIntCallback)(void);
typedef void (*VoidToVoidCallback)(void);
typedef void (*WorldToVoidCallback)(model::World*);

#endif
