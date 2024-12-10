# Opdracht 2: Het werken met een gemeenschapelijke buffer.

## A

1. Download opgave2 pak de file uit en compileer ( voer het make commando uit ) of zet de files in een ide. Run vervolgens het programma (./opgave2a) een aantal keren. Wat valt op?

    De code geeft altijd hetzelfde resultaat.

2. Vergroot het aantal in de main naar b.v. 10000 compileer en run opnieuw het programma. Wat valt op?

    De code geeft nu een ander resultaat dan toen het aantal 100 was. Elke keer dat de code draait geeft het wel hetzelfde resultaat als de andere keren met aantal 10000.

3. Zet het aantal in de main weer terug op de 100. Zet verder de usleep ook in de functie zetInBuf (boven de while). Wat is het resultaat?

    Het resultaat is niet altijd hetzelfde meer.

4. Verwijder alle usleep, compileer en run het programma nogmaals een aantal keren, wat is het resultaat? Wat gaat er fout?

    de code loopt vast na start.

## B

Zolang aantal in de main hetzelfde is elke keer dat het programma draait dan is het resultaat ook hetzelfde.

## C