.name "GodFather"
.comment "I'm gonna make him an offer he can't refuse"


fork		%:alive
ld			%0, r16
base:
sti		r1, %:alive, %1
sti		r1, %:alive, %9
sti		r1, %:alive, %17
sti		r1, %:alive, %25
sti		r1, %:usineforkeur, %1
sti		r1, %:usineforkeur, %9
sti		r1, %:usineforkeur, %17
sti		r1, %:usineforkeur, %25
sti		r1, %:wall, %1
sti		r1, %:pouette, %1
sti		r1, %:attforker, %1
sti		r1, %:attforker, %9
sti		r1, %:attaque, %1
sti		r1, %:attaque, %9
sti		r1, %:forkeur, %1
sti		r1, %:forkeur3, %1
sti		r1, %:forkeur4, %1


alive:
live	%2863311530
fork	%:wall
live	%2863311530
fork	%:usineforkeur
live	%2863311530
fork	%:alive
live	%2863311530
fork	%:pouette
zjmp    %:alive

wall:
live	%2863311530
sti		r16, %:base, %120
sti		r16, %:base, %116
sti		r16, %:base, %112
sti		r16, %:base, %108
sti		r16, %:base, %104
sti		r16, %:base, %100
sti		r16, %:base, %96
sti		r16, %:base, %92
sti		r16, %:base, %88
sti		r16, %:base, %84
sti		r16, %:base, %80
sti		r16, %:base, %76
sti		r16, %:base, %72
sti		r16, %:base, %68
sti		r16, %:base, %64
sti		r16, %:base, %60
sti		r16, %:base, %56
sti		r16, %:base, %52
sti		r16, %:base, %48
sti		r16, %:base, %44
sti		r16, %:base, %40
sti		r16, %:base, %36
sti		r16, %:base, %32
sti		r16, %:base, %28
sti		r16, %:base, %24
sti		r16, %:base, %20
sti		r16, %:base, %16
sti		r16, %:base, %12
sti		r16, %:base, %8
sti		r16, %:base, %4
sti		r16, %:base, %0
sti		r16, %:base, %-4
sti		r16, %:base, %-8
sti		r16, %:base, %-12
sti		r16, %:base, %-16
sti		r16, %:base, %-20
sti		r16, %:base, %-24
sti		r16, %:base, %-28
sti		r16, %:base, %-32
sti		r16, %:base, %-36
zjmp	%:wall

usineforkeur:
live	%2863311530
fork	%:wall
live	%2863311530
fork	%:pouette
live	%2863311530
fork	%:attforker
live	%2863311530
fork	%:usineforkeur
zjmp   	%:usineforkeur

pouette:
live	%2863311530
zjmp	%:pouette

attforker:
live	%2863311530
fork	%:attforker
live	%2863311530
fork	%:attaque
zjmp	%:attforker

attaque:
live	%2863311530
fork	%:forkeur
zjmp	%:attaque

forkeur:
live	%2863311530
fork	%:forkeur4

forkeur3:
live	%2863311530
fork	%:init3

init1:
ld      %150994955, r2
ld      %498, r3
ld		%0, r15
zjmp    %:print

forkeur4:
live	%2863311530
fork	%:init4

init2:
ld      %1409421059, r2
ld      %502, r3
ld		%0, r15
zjmp    %:print

init3:
ld      %33554431, r2
ld      %506, r3
ld		%0, r15
zjmp    %:print

init4:
ld      %4278780395, r2
ld      %510, r3
ld		%0, r15
zjmp    %:print

print:
sti		r2, r15, r3
zjmp	%496
