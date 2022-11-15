let () = 
  Printf.printf "cache ln size: %d\n" (Aligned_atomic.cache_line_size ());
  let a = Aligned_atomic.make 123 in 
  Printf.printf "aligned? %b\n" (Aligned_atomic.check_aligned a);
  Atomic.fetch_and_add a 1000 |> ignore;
  Printf.printf "Atomic.get a = %d\n" (Atomic.get a);;