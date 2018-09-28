define s7print
print s7_object_to_c_string(cur_sc, $arg0)
end
document s7print
interpret the argument as an s7 value and display it
end

# the current expression is sc->cur_code
# the current environment is sc->envir
# the error environment is sc->owlet
# so for example, to see the current local variables, s7p sc->envir
# source ~/.gdbinit reloads

# set print elements 123123 in gdb to get full string

define s7eval
print s7_object_to_c_string(cur_sc, s7_eval_c_string(cur_sc, $arg0))
end
document s7eval
eval the argument (a string)
end


define s7stack
print s7_object_to_c_string(cur_sc, s7_stacktrace(sc))
end
document s7stack
display the currently active local environments
end


define s7value
print s7_object_to_c_string(cur_sc, s7_name_to_value(cur_sc, $arg0))
end
document s7value
print the value of the variable passed by its print name: s7v "*features*"
end


define s7let
print s7_show_let(cur_sc)
end
document s7let
show all non-global variables that are currently accessible
end


define s7history
print s7_show_history(cur_sc)
end
document s7history
show the entries in the history buffer
end

define s7crawl
print s7_show_stack(cur_sc)
end
document s7history
show the ops in the stack
end


define s7bt
set logging overwrite on
set logging redirect on
set logging on
if $argc == 1
  bt $arg0
end
if $argc == 0)
  bt
end
set logging off
# now gdb.txt has the backtrace
print s7_decode_bt(cur_sc)
end
document s7bt
print a C backtrace with s7 objects decoded as much as possible
end

define s7btfull
set logging overwrite on
set logging redirect on
set logging on
if $argc == 1
  bt full $arg0
end
if $argc == 0)
  bt full
end
set logging off
print s7_decode_bt(cur_sc)
end
document s7btfull
print a full C backtrace with s7 objects decoded as much as possible
end
