/*
Program to generate text based on the context provided by input prompts.
Skeleton program written by Artem Polyvyanyy, http://polyvyanyy.com/,
September 2023, with the intention that it be modified by students
to add functionality, as required by the assignment specification.
All included code is (c) Copyright University of Melbourne, 2023.

Student Authorship Declaration:

(1) I certify that except for the code provided in the initial skeleton file,
the program contained in this submission is completely my own individual
work, except where explicitly noted by further comments that provide details
otherwise. I understand that work that has been developed by another student,
or by me in collaboration with other students, or by non-students as a result
of request, solicitation, or payment, may not be submitted for assessment in
this subject. I understand that submitting for assessment work developed by
or in collaboration with other students or non-students constitutes Academic
Misconduct, and may be penalized by mark deductions, or by other penalties
determined via the University of Melbourne Academic Honesty Policy, as
described at https://academicintegrity.unimelb.edu.au.

(2) I also certify that I have not provided a copy of this work in either
softcopy or hardcopy or any other form to any other student, and nor will I
do so until after the marks are released. I understand that providing my work
to other students, regardless of my intention or any undertakings made to me
by that other student, is also Academic Misconduct.

(3) I further understand that providing a copy of the assignment specification
to any form of code authoring or assignment tutoring service, or drawing the
attention of others to such services and code that may have been made
available via such a service, may be regarded as Student General Misconduct
(interfering with the teaching activities of the University and/or inciting
others to commit Academic Misconduct). I understand that an allegation of
Student General Misconduct may arise regardless of whether or not I personally
make use of such solutions or sought benefit from such actions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* #DEFINE'S -----------------------------------------------------------------*/
#define SDELIM "==STAGE %d============================\n" // stage delimiter
#define MDELIM "-------------------------------------\n"  // delimiter of -'s
#define THEEND "==THE END============================\n"  // end message
#define NOSFMT "Number of statements: %d\n"               // no. of statements
#define NOCFMT "Number of characters: %d\n"               // no. of chars
#define NPSFMT "Number of states: %d\n"                   // no. of states
#define TFQFMT "Total frequency: %d\n"                    // total frequency

#define CRTRNC '\r' // carriage return character
#define BLANK ' '
#define STAGE_ZERO 0
#define STAGE_ONE 1
#define EMPTY '\0'
#define MAX_DIGITS 37
#define ASCII_NUM 48
#define STAGE_TWO 2

/* TYPE DEFINITIONS ----------------------------------------------------------*/
typedef struct state state_t; // a state in an automaton
typedef struct node node_t;   // a node in a linked list

struct node
{                   // a node in a linked list of transitions has
    char *str;      // ... a transition string
    state_t *state; // ... the state reached via the string, and
    node_t *next;   // ... a link to the next node in the list.
};

typedef struct
{                 // a linked list consists of
    node_t *head; // ... a pointer to the first node and
    node_t *tail; // ... a pointer to the last node in the list.
} list_t;

struct state
{                      // a state in an automaton is characterized by
    unsigned int id;   // ... an identifier,
    unsigned int freq; // ... frequency of traversal,
    int visited;       // ... visited status flag, and
    list_t *outputs;   // ... a list of output states.
};

typedef struct
{                     // an automaton consists of
    state_t *ini;     // ... the initial state, and
    unsigned int nid; // ... the identifier of the next new state.
    unsigned int statements;
    unsigned int characters;
} automaton_t;
int count = 0;
/* USEFUL FUNCTIONS ----------------------------------------------------------*/
int mygetchar(int n); // getchar() that skips carriage returns

automaton_t *make_EmptyAutomaton(automaton_t *automaton);

void make_state(automaton_t *automaton, state_t *state);

void make_node(automaton_t *automaton, node_t *node, char *c);

void make_FirstRun(automaton_t *automaton);

void stage0(automaton_t *automaton);

void stage1(automaton_t *automaton);

void stage2(automaton_t *automaton);

/* WHERE IT ALL HAPPENS ------------------------------------------------------*/
int main(int argc, char *argv[])
{
    automaton_t automaton = *make_EmptyAutomaton(&automaton);
    make_FirstRun(&automaton);
    stage0(&automaton);
    stage1(&automaton);
    stage2(&automaton);
    return EXIT_SUCCESS;
}

void stage2(automaton_t *automaton)
{
    char curr_c = mygetchar(count++), past_c = BLANK;
    int steps = 0, tens = 1;
    while (curr_c >= 48 && curr_c <= 57)
    {
        steps = (curr_c - ASCII_NUM) * tens;
        tens *= 10;
        past_c = curr_c;
        curr_c = mygetchar(count++);
    }
    printf(SDELIM, STAGE_TWO);

    while (steps > 0)
    {
        break;
    }
}

void stage1(automaton_t *automaton)
{
    node_t *curr_ptr = automaton->ini->outputs->head;
    char curr_c = mygetchar(count++), past_c = BLANK;
    node_t *most_freq = curr_ptr;
    unsigned int most_freqNum = 0;
    char most_freqChar = '\0';
    int digit_count = MAX_DIGITS;
    printf(SDELIM, STAGE_ONE);
    while (1)
    {
        // Ends stage 1 when empty line is detected
        if (curr_c == '\n' && past_c == '\n')
        {
            break;
        }
        digit_count = MAX_DIGITS;
        // Traversing the automaton until new line character detected
        while (curr_c != '\n')
        {
            if (digit_count > 0)
            {
                printf("%c", curr_c);
                digit_count--;
            }
            while (1)
            {
                if (*(curr_ptr->str) == EMPTY)
                {
                    break;
                }
                else if (*(curr_ptr->str) == curr_c)
                {
                    break;
                }
                else
                {
                    curr_ptr = curr_ptr->next;
                }
            }
            if (*(curr_ptr->str) == EMPTY)
            {
                break;
            }
            else if (*(curr_ptr->str) == curr_c)
            {
                curr_ptr = curr_ptr->state->outputs->head;
                past_c = curr_c;
                curr_c = mygetchar(count++);
                continue;
            }
        }
        // Prints the ellipses
        if (digit_count > 0)
        {
            printf(".");
            digit_count--;
        }
        if (digit_count > 0)
        {
            printf(".");
            digit_count--;
        }
        if (digit_count > 0)
        {
            printf(".");
            digit_count--;
        }
        // Prints most frequent character until leaf node
        while (1)
        {
            if (*(curr_ptr->str) == EMPTY)
            {
                break;
            }
            while (*(curr_ptr->str) != EMPTY)
            {
                if (curr_ptr->state->freq == most_freqNum)
                {
                    if (most_freqChar == EMPTY)
                    {
                        most_freqChar = *(curr_ptr->str);
                        most_freqNum = curr_ptr->state->freq;
                        most_freq = curr_ptr;
                    }
                    else if (*(curr_ptr->str) == most_freqChar)
                    {
                        break;
                    }
                    else if (*(curr_ptr->str) > most_freqChar)
                    {
                        most_freqChar = *(curr_ptr->str);
                        most_freqNum = curr_ptr->state->freq;
                        most_freq = curr_ptr;
                    }
                }
                else if (curr_ptr->state->freq > most_freqNum)
                {
                    most_freqNum = curr_ptr->state->freq;
                    most_freq = curr_ptr;
                    most_freqChar = *(curr_ptr->str);
                }
                curr_ptr = curr_ptr->next;
            }

            printf("%c", most_freqChar);
            digit_count--;
            curr_ptr = most_freq;
            most_freqNum = 0;
            most_freqChar = EMPTY;
            curr_ptr = curr_ptr->state->outputs->head;
        }
        printf("\n");
        past_c = curr_c;
        curr_c = mygetchar(count++);
        curr_ptr = automaton->ini->outputs->head;
        while (1)
        {
            if (past_c == '\n')
            {
                break;
            }
            else
            {
                past_c = curr_c;
                curr_c = mygetchar(count++);
            }
        }
    }
}

void stage0(automaton_t *automaton)
{
    int NewStatementFlag = 1; // when start of new statement
    char past_c = BLANK, curr_c = mygetchar(count++);
    node_t *curr_ptr = automaton->ini->outputs->head;

    while (1)
    {
        // Ends stage 0 when empty line is detected
        if (curr_c == '\n' && past_c == '\n')
        {
            break;
        }
        // First character of each new statement
        if (NewStatementFlag == 1)
        {
            // New statement detected
            automaton->statements = (int)(automaton->statements) + 1;
            curr_ptr = automaton->ini->outputs->head;
            while (1)
            {
                if (*(curr_ptr->str) == EMPTY)
                {
                    break;
                }
                else if (*(curr_ptr->str) == curr_c)
                {
                    break;
                }
                else
                {
                    curr_ptr = curr_ptr->next;
                }
            }
            if (*(curr_ptr->str) == EMPTY)
            {
                make_node(automaton, curr_ptr, curr_c);
                curr_ptr = curr_ptr->state->outputs->head;
                past_c = curr_c;
                curr_c = mygetchar(count++);
                automaton->characters = (int)(automaton->characters) + 1;
                NewStatementFlag = 0;
                continue;
            }
            else
            {
                curr_ptr->state->freq = (int)(curr_ptr->state->freq) + 1;
                curr_ptr = curr_ptr->state->outputs->head;
                past_c = curr_c;
                curr_c = mygetchar(count++);
                automaton->characters = (int)(automaton->characters) + 1;
                NewStatementFlag = 0;
                continue;
            }
        }
        // Subsequent characters of each statement
        while (NewStatementFlag == 0)
        {
            if (curr_c == '\n')
            {
                NewStatementFlag = 1;
                break;
            }
            if (*(curr_ptr->str) == EMPTY)
            {
                make_node(automaton, curr_ptr, curr_c);
                curr_ptr = curr_ptr->state->outputs->head;
                past_c = curr_c;
                curr_c = mygetchar(count++);
                automaton->characters = (int)(automaton->characters) + 1;
                continue;
            }
            else if (*(curr_ptr->str) == curr_c)
            {
                curr_ptr->state->freq = (int)(curr_ptr->state->freq) + 1;
                curr_ptr = curr_ptr->state->outputs->head;
                past_c = curr_c;
                curr_c = mygetchar(count++);
                automaton->characters = (int)(automaton->characters) + 1;
                continue;
            }
            else
            {
                while (1)
                {
                    if (*(curr_ptr->str) == EMPTY)
                    {
                        break;
                    }
                    else if (*(curr_ptr->str) == curr_c)
                    {
                        break;
                    }
                    else
                    {
                        curr_ptr = curr_ptr->next;
                    }
                }
                if (*(curr_ptr->str) == EMPTY)
                {
                    make_node(automaton, curr_ptr, curr_c);
                    curr_ptr = curr_ptr->state->outputs->head;
                    past_c = curr_c;
                    curr_c = mygetchar(count++);
                    automaton->characters = (int)(automaton->characters) + 1;
                    continue;
                }
                else if (*(curr_ptr->str) == curr_c)
                {
                    curr_ptr->state->freq = (int)(curr_ptr->state->freq) + 1;
                    curr_ptr = curr_ptr->state->outputs->head;
                    past_c = curr_c;
                    curr_c = mygetchar(count++);
                    automaton->characters = (int)(automaton->characters) + 1;
                    continue;
                }
            }
        }
        past_c = curr_c;
        curr_c = mygetchar(count++);
    }
    printf(SDELIM, STAGE_ZERO);
    printf(NOSFMT, automaton->statements);
    printf(NOCFMT, automaton->characters);
    printf(NPSFMT, automaton->nid);
}

void make_FirstRun(automaton_t *automaton)
{
    char *curr_c = (char *)malloc(sizeof(char));
    *(curr_c) = mygetchar(count++);
    node_t *curr_ptr = automaton->ini->outputs->head;

    // First statement recorded into automaton
    automaton->statements = (int)(automaton->statements) + 1;

    while (*(curr_c) != '\n')
    {
        // Each character of the first statement registered
        automaton->characters = (int)(automaton->characters) + 1;

        make_node(automaton, curr_ptr, curr_c);
        *(curr_c) = mygetchar(count++);
        curr_ptr = curr_ptr->state->outputs->head;
    }
    return;
}

void make_node(automaton_t *automaton, node_t *node, char *c)
{
    strcpy(node->str, c);

    node->state = (state_t *)malloc(sizeof(state_t));
    assert(node->state);
    make_state(automaton, node->state);

    node->next = (node_t *)malloc(sizeof(node_t));
    assert(node->next);
    node->next->str = (char *)malloc(sizeof(char));
    assert(node->next->str);
    *(node->next->str) = EMPTY;
    return;
}

void make_state(automaton_t *automaton, state_t *state)
{
    automaton->nid = (int)(automaton->nid) + 1;

    state->id = automaton->nid;
    state->freq = 0;
    state->visited = 0;

    state->outputs = (list_t *)malloc(sizeof(list_t));
    assert(state->outputs);
    state->outputs->head = (node_t *)malloc(sizeof(node_t));
    assert(state->outputs->head);
    state->outputs->tail = state->outputs->head;
    state->outputs->head->str = (char *)malloc(sizeof(char));
    *(state->outputs->head->str) = EMPTY;
    return;
}

automaton_t *make_EmptyAutomaton(automaton_t *automaton)
{
    automaton = (automaton_t *)malloc(sizeof(automaton_t));
    assert(automaton);
    automaton->ini = (state_t *)malloc(sizeof(state_t));
    assert(automaton->ini);
    automaton->ini->id = 0;
    automaton->ini->freq = 0;
    automaton->ini->visited = 0;
    automaton->ini->outputs = (list_t *)malloc(sizeof(list_t));
    assert(automaton->ini->outputs);
    automaton->ini->outputs->head = (node_t *)malloc(sizeof(node_t));
    assert(automaton->ini->outputs->head);
    automaton->ini->outputs->tail = automaton->ini->outputs->head;
    automaton->ini->outputs->head->str = (char *)malloc(sizeof(char));
    assert(automaton->ini->outputs->head->str);
    *(automaton->ini->outputs->head->str) = EMPTY;

    automaton->nid = 1;
    automaton->statements = 0;
    automaton->characters = 0;

    return automaton;
}

int mygetchar(int n)
{
    char c;
    char t[] = "Hey#Prof\nHi#Sir\nHi#Sir\nHi#Prof\nHello\nHey\nHi#there\nHey#you\n\n";
    if (count >= 60)
    {
        c = '\n';
        return c;
    }
    c = *(t + n);
    return c;
}

// algorithms are fun