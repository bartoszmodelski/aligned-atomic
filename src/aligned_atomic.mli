val cache_line_size : unit -> int
(** get cache line size in bytes *)

val check_aligned : 'a Atomic.t -> bool
(** check if integer is aligned *)

val make : 'a -> 'a Atomic.t