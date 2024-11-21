# Opdracht 1: Het werken met prosessen en threads.

## A: van sequentieel naar parallel met behulp van fork()

1. Voer het programma (./prog1) 5 * uit en noteer de tijden.

- run 1: 40008  40008418820
- run 2: 40008  40008971707
- run 3: 40009  40009443253
- run 4: 40009  40009032525
- run 5: 40009  40009218963

2. Maak de usleep commentaar, compileer het programma en voer het programma 5 * uit en noteer de tijden.

- run 1: 0  49144
- run 2: 0  47411
- run 3: 0  56157
- run 4: 0  49475
- run 5: 0  45337

3. Laat de functie doeIets parallel aan elkaar uitvoeren zodat er 1 parent en 3 child processen aanwezig zijn. Voer het programma 5 * uit en noteer de tijden.

- run 1: 16003  16003492955
- run 2: 16002  16002156627
- run 3: 16003  16003295632
- run 4: 16003  16003011042
- run 5: 16003  16003012151

4. Maak de usleep commentaar, compileer het programma en voer het programma 5 * uit en noteer de tijden.

- run 1: 0  271190
- run 2: 0  262753
- run 3: 0  283253
- run 4: 0  238387
- run 5: 0  244629

De code met child processes is ongeveer twee keer zo snel als de code zonder child processes.

## Deel B, Communicatie tussen processen.


1. Pas het programma uit opgave A zodanig aan, zodat de drie child processen de characters in de pipe zetten en het parent proces de characters uit de pipe leest en deze uitprint.

👍

## Deel C, van sequentieel naar parallel door middel van threads.

1. Laat de functie doeIets nu parallel lopen door middel van 4 threads.

👍

2. Het voordeel van het werken met threads, is dat bij onderlinge communicatie geen gebruik hoeft te worden gemaakt van het operating systeem, zoals het leggen van een pipe bij processen. Laat 3 threads ieder een character in een queue van de STL zetten en een 4 thread die uit de queue leest en de characters uitprint. Maak hiervoor een klasse Werker met een methoden plaatsIets en haalIets en een std queue als een static variabele. 

👍