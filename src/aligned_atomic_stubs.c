#include <caml/mlvalues.h>
#include <caml/gc.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

size_t cache_line_size()
{
  return sysconf (_SC_LEVEL1_DCACHE_LINESIZE);
}

value caml_cache_line_size(value v)
{
  return Val_int(cache_line_size());
}

value caml_check_aligned(value v)
{
  //printf("v: %" PRIu64 "\n", v);
  size_t size = cache_line_size();
  if (((v - 8) % size) == 0)
  {
    return Val_true;
  }
  else
  {
    return Val_false;
  }
}

value caml_make_aligned(value val) 
{
  size_t size = cache_line_size();
  value chunk = caml_alloc( /* 3x cache line */ 3 * size / 8, 0); 
  
  size_t overshot = chunk % size;
    
  value var1 = chunk; 
  value var2 = var1 + 2 * size - overshot + 8; /* +8 for header */
  value var3 = var2 + 16; 

  size_t size_var1 = (var2 - 8) - var1; /* -8 for header */
  size_t size_var2 = (var3 - 8) - var2;
  size_t size_var3 = ((var1 + 3 * size - 8) - var3);

  *Hp_val(var1) =  Make_header(size_var1 / 8, 0, 0);
  *Hp_val(var2) =  Make_header(size_var2 / 8, 0, 0);
  *Hp_val(var3) =  Make_header(size_var3 / 8, 0, 0);

  caml_initialize(&Field(var2, 0), val);

  printf("hdr1: %" PRIu64 ", sz1: %" PRIu64 "\n", var1-8, size_var1);
  printf("hdr2: %" PRIu64 ", sz2: %" PRIu64 "\n", var2-8, size_var2);
  printf("hdr3: %" PRIu64 ", sz3: %" PRIu64 "\n", var3-8, size_var3);

  return var2;
}