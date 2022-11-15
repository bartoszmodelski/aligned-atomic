external cache_line_size : unit -> int = "caml_cache_line_size"
external check_aligned : 'a Atomic.t -> bool = "caml_check_aligned"

external make : 'a -> 'a Atomic.t = "caml_make_aligned"