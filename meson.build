project('fibonacci', ['c', 'cpp'], default_options: ['buildtype=release', 'cpp_std=c++20'])

c = 'test_recursion.c'
cc = 'test_recursion.cc'
cc_vector = 'test_with_unwinding.cc'

foreach opt : ['-O0', '-O2', '-O3']
  executable('test-c' + opt, c, c_args: [opt])
  foreach exc: ['no_unwind', 'unwind_dontcare', 'unwind_noexcept', 'unwind_throwing', 'unwind_catching']
    args = [opt]
    if exc == 'no_unwind'
      args += ['-fno-exceptions', '-fno-rtti', '-fno-unwind-tables', '-fomit-frame-pointer']
    else
      args += ['-fexceptions', '-frtti']
    endif
    args += ['-D' + exc]
    executable('test-cc' + opt + '-' + exc, cc, cpp_args: args)
    executable('test-vector-cc' + opt + '-' + exc, cc_vector, cpp_args: args)
  endforeach
endforeach
