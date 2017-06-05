.name "GodFather"
.comment "I'm gonna make him an offer he can't refuse"

add			r1, r11, r11
ld			%589824, r13
ld			%0, r16
base:
	sti		r11, %:alive, %1
	sti		r11, %:initfork, %1
	sti		r11, %:initfork, %9
	sti		r11, %:initfork, %17
	sti		r11, %:wall, %1
	sti		r11, %:usine, %1
	sti		r11, %:usine, %9
	sti		r11, %:usine, %17
	sti		r11, %:usine, %25
	sti		r11, %:usine, %33
	sti		r11, %:attforker, %1
	sti		r11, %:attforker, %9
	sti		r11, %:attforker, %17
	sti		r11, %:salve, %1
	sti		r11, %:salve, %9
	sti		r11, %:salve, %17
	sti		r11, %:salve3, %1
	sti		r11, %:salve4, %1
	sti		r11, %:salve5, %1
	sti		r11, %:initsalve1, %2
	sti		r11, %:initsalve5, %2
	live	%4294967295
	fork	%:wall

initfork:
	live	%2863311530
	fork	%:salve
	live	%2863311530
	fork	%:usine
	live	%2863311530
	fork	%:initfork
	zjmp	%:initfork

wall:
	live	%2863311530
	st		r13, -43
	st		r13, -52
	st		r13, -61
	st		r13, -70
	st		r13, -79
	st		r13, -88
	st		r13, -97
	st		r13, -106
	st		r13, -115
	st		r13, -124
	st		r13, -133
	st		r13, -142
	st		r13, -151
	st		r13, -160
	st		r13, -169
	st		r13, -178
	st		r13, -187
	st		r13, -196
	st		r13, -205
	st		r13, -214
	st		r13, -223
	st		r13, -238
	st		r13, -251
	st		r13, -264
	st		r13, -277
	st		r13, -290
	st		r13, -303
	st		r13, -316
	st		r13, -329
	st		r13, -342
	zjmp	%:wall


usine:
	live	%2863311530
	fork	%:salve
	live	%2863311530
	fork	%:wall
	live	%2863311530
	fork	%:attforker
	live	%2863311530
	fork	%:usine
	live	%2863311530
	fork	%:alive
	zjmp	%:usine

alive:
	live	%2863311530
	zjmp	%:alive

attforker:
	live	%2863311530
	fork	%:salve
	live	%2863311530
	fork	%:salve
	ld		%0, r16
	zjmp	%:attforker

salve:
	live	%2863311530
	fork	%:salve
	live	%2863311530
	fork	%:salve_2

salve_1:
	live	%2863311530
	fork	%:salve4

salve3:
	live	%2863311530
	fork	%:initsalve3

initsalve1:
	# add		r16, r11, r2
	ld		%0, r2
	ld      %22, r3
	ld		%0, r15
	zjmp    %:printsalve

salve4:
	live	%2863311530
	fork	%:initsalve4

initsalve2:
	ld      %1409421059, r2
	ld      %17, r3
	ld		%0, r15
	zjmp    %:printsalve

salve_2:
	live	%2863311530
	fork	%:salve5

salve5:
	live	%2863311530
	fork	%:initsalve6

initsalve5:
	# add		r16, r11, r2
	ld		%0, r2
	ld      %502, r3
	ld		%0, r15
	zjmp    %:printsalve

initsalve3:
	# add		r16, r11, r2
	ld      %27962026, r2
	ld      %21, r3
	ld		%0, r15
	zjmp    %:printsalve

initsalve4:
	ld      %2852716550, r2
	ld      %25, r3
	ld		%0, r15
	zjmp    %:printsalve

initsalve6:
	ld      %150994955, r2
	ld      %13, r3
	ld		%0, r15
	zjmp    %:printsalve

printsalve:
	sti		r2, r15, r3
	zjmp	%10
