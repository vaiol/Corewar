.name "GodFather"
.comment "I'm gonna make him an offer he can't refuse"


fork		%:initfork
ld			%0, r16
base:
	sti		r1, %:initfork, %1
	sti		r1, %:initfork, %9
	sti		r1, %:initfork, %17
	sti		r1, %:usineforkeur, %1
	sti		r1, %:usineforkeur, %9
	sti		r1, %:usineforkeur, %17
	sti		r1, %:usineforkeur, %25
	sti		r1, %:usineforkeur, %33
	sti		r1, %:usineforkeur, %41
	sti		r1, %:wall, %1
	sti		r1, %:alive, %1
	sti		r1, %:attforker, %1
	sti		r1, %:attforker, %9
	sti		r1, %:forkeur, %1
	sti		r1, %:forkeur3, %1
	sti		r1, %:forkeur4, %1
	sti		r1, %:wall2, %1
	sti		r1, %:wall2, %9
	sti		r1, %:wall2, %17
	fork	%:wall2

initfork:
	live	%2863311530
	fork	%:wall
	live	%2863311530
	fork	%:usineforkeur
	live	%2863311530
	fork	%:initfork
	zjmp	%:initfork

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
	zjmp	%:wall

usineforkeur:
	live	%2863311530
	fork	%:wall
	live	%2863311530
	fork	%:wall2
	live	%2863311530
	fork	%:forkeur
	live	%2863311530
	fork	%:attforker
	live	%2863311530
	fork	%:usineforkeur
	live	%2863311530
	ld		%0, r16 # verifier dans la vrai
	fork	%:alive
	zjmp	%:usineforkeur

alive:
	live	%2863311530
	zjmp	%:alive

attforker:
	live	%2863311530
	fork	%:attforker
	live	%2863311530
	fork	%:forkeur
	zjmp	%:attforker

forkeur:
	live	%2863311530
	fork	%:forkeur4

forkeur3:
	live	%2863311530
	fork	%:init3

init1:
	ld      %150994955, r2
	ld      %388, r3
	ld		%0, r15
	zjmp    %:print

forkeur4:
	live	%2863311530
	fork	%:init4

init2:
	ld      %1409421059, r2
	ld      %392, r3
	ld		%0, r15
	zjmp    %:print

init3:
	#		33554431
	ld      %0, r2
	ld      %396, r3
	ld		%0, r15
	zjmp    %:print

init4:
	#		4278780185
	ld      %590205, r2
	ld      %400, r3
	ld		%0, r15
	zjmp    %:print

print:
	sti		r2, r15, r3
	zjmp	%386

wall2:
	live	%2863311530
	fork	%96
	live	%2863311530
	fork	%:wall2
	live	%2863311530
	ld			%655358, r13
	sti		r13, %:end, %4
	sti		r13, %:end, %8
	sti		r13, %:end, %12
	sti		r13, %:end, %16
	sti		r13, %:end, %20
	sti		r13, %:end, %24
	sti		r13, %:end, %28
	sti		r13, %:end, %32
	sti		r13, %:end, %36
	sti		r13, %:end, %40
	sti		r13, %:end, %44
	sti		r13, %:end, %48
	sti		r13, %:end, %52
	sti		r13, %:end, %56
	sti		r13, %:end, %60
	sti		r13, %:end, %64
	sti		r13, %:end, %68
	sti		r13, %:end, %72
	sti		r13, %:end, %76
	sti		r13, %:end, %80
	sti		r13, %:end, %84
	sti		r13, %:end, %88
	sti		r13, %:end, %92
	sti		r13, %:end, %96
	sti		r13, %:end, %100
	sti		r13, %:end, %104
	sti		r13, %:end, %108
	sti		r13, %:end, %112
	sti		r13, %:end, %116
	sti		r13, %:end, %120
	sti		r13, %:end, %124
	sti		r13, %:end, %128
	ld		%0, r16 # verifier dans la vrai
	zjmp	%:wall2

end:
