#
# Warrior qui a gagne
# l'annee derniere
#     VOALA
#
.name		"OK"
.comment	"Jour J"

l2:
    sti r1, %:live, %1
    sti r1, %:copy, %1
    sti r1, %:spawn, %1
    ld  %4, r5;
    and r1, %0, r1

live:
    live %555
    fork %:spawn
copy:
    live %555;
    ldi %:live, r2, r3;
    sti r3, %200, r2;
    add r2, r5, r2;
    ld %0, r16;
    zjmp %:copy;
spawn:
    live %555
    fork %:spawn
