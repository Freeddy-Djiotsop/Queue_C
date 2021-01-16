#include <stdio.h>
#include <stdlib.h>

#define Q_size 50

typedef int Q_datentyp;

typedef struct
{
    Q_datentyp element[Q_size];//Ich speichere die Daten in einem Feld der Groesse 50
    int head;
    int tail;
}Queue;

void q_create(Queue *q)
{
    q->head = -1;
    q->tail = -1;
}


//Daten in Queue einfügen
//Bei dem Queue wird Datum am Schwanz eingefügt und am Kopf geloescht.
void q_enqueue(Q_datentyp e, Queue *q)
{
    double next_pos = (q->head +1) % Q_size;//Naechste Freie position in Queue

    if(next_pos==q->tail)
    {
        printf("Fehler: Queue ist gerade voll!\n");
        exit(EXIT_FAILURE);
    }

    q->head = next_pos;

    q->element[q->head] = e;
    if(q->tail==-1)//Wenn Queue leer ist und erstes Datum hinzugefügt wurde
        q->tail = q->head;
}

void q_dequeue(Queue *q, Q_datentyp *e)
{
    if(q->tail==-1)
    {
        printf("Fehler: Queue ist bereits leer!\n");
        exit(EXIT_FAILURE);
    }

    *e = q->element[q->tail];//Datum, das ich jetzt loesche

    if(q->head==q->tail)//Es war nur ein Datun in Queue gespeichert
    {
        q->head = -1;
        q->tail = -1;
    }
    else
        q->tail = (q->tail+1) % Q_size;
}

int q_empty(Queue *q)
{
    return (q->head!=-1);//ich habe ein leeres Queue mit q->head=-1 erzeugt
}

void q_write(Queue *q)//Queue ausgeben
{
    printf("Queue: Tail(");
    for(int i=q->tail; i!=q->head; i = (i+1) % Q_size)//Ich gebe hier nur bis vor dem head aus
        printf("%d ", q->element[i]);
    if(q->head!=-1)
        printf("%d", q->element[q->head]);//Und hier gebe ich entwerder das einzige Datum oder das letzte aus
    printf(") Head");
}

int main()
{
    Queue q;
    Q_datentyp e=0, weiter=1;
    char c;

    //Das Menue zur Auswahl
    while(weiter)
    {
        printf("\nc [create] Queue erzeugen\n");
        printf("i [enqueue] Element einfuegen\n");
        printf("d [dequeue] Element entfernen\n");
        printf("e [empty] Queue leer?\n");
        printf("q [quit] Programm verlassen\n\n");

        c = getchar();
        switch(c)
        {
        case 'c':
            q_create(&q);
            break;
        case 'i':
            printf("Zahl eingeben:\t");
            scanf("%d", &e);
            q_enqueue(e,&q);
            break;
        case 'd':
            q_dequeue(&q,&e);
            printf("Entferntes Element: %d\n", e);
            break;

        case 'e':
            if(q_empty(&q))
                printf("Queue ist nicht leer!\n");
            else
                printf("Queue ist leer!\n");
            break;

        case 'q':
            weiter = 0;
            break;
        default:
            printf("Eingabe nicht definiert, Wiederholen Bitte\n");
            break;
        }

        q_write(&q);
        getchar();
        printf("\n");
    }


    printf("\n");
    return 0;
}
