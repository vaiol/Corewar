.name "ubiyca"
.comment "mama ama kriminal"

start:
    sti     r1, %:copy, %1
    sti     r1, %:spawn, %1
    ld      %4, r3

#fork:
 #   fork    %:spawn

copy:
    live    %555
    lldi    %:copy, r4, r2
    sti     r2, r4, %33
    add     r4, r3, r4
    and     %0, %0, r1
    zjmp    %:copy

spawn:
    live    %555
    fork    %:spawn
