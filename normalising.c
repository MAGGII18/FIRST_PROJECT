#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char **normalize(const char *text, size_t *out_count);
void free_tokens(char **tokens, size_t count);

/* LIST OF COMMON STOPWORDS */
static const char *stopwords[] = 
{
    "a","an","the","and","or","but","if","in","on","at","by","for","with",
    "is","are","was","were","be","been","to","of","that","this","it","as",
    "from","they","their","we","us","he","she","him","her","you","your",
    NULL
};

/* CHECK IF WORD IS STOPWORD OR NOT*/
static int is_stopword(const char *word) 
{
    for (int i = 0;stopwords[i]!=NULL;i++) 
    {
        if (strcmp(stopwords[i], word)== 0)
            return 1;
    }
    return 0;
}

/* CONVERTING TO LOWER CASE AND REMOVING PUNCTUATIONS */
static char *normalize_text(const char *text) {
    size_t len = strlen(text);
    char *clean = malloc(len + 1);

    if (clean == NULL)
        return NULL;

    for (size_t i = 0; i < len; i++) 
    {
        char ch = text[i];
        if (isalnum(ch))
            clean[i] = tolower(ch);  // make lowercase
        else
            clean[i] = ' ';          // replace punctuation with space
    }

    clean[len] ='\0';
    return clean;
}

/* Tokenize normalized text and remove stopwords */
char **normalize(const char *text, size_t *out_count) 
{
    if (text == NULL) 
    {
        if (out_count) 
        {
        *out_count = 0;
        }
        return NULL;
    }

    char *norm = normalize_text(text);
    if (norm == NULL) {
        if (out_count)
        {
            *out_count = 0;
        }
        return NULL;
    }

    size_t capacity = 50;   // initial size
    size_t count = 0;
    char *words = malloc(capacity * sizeof(char));

    char *token = strtok(norm, " \t\n\r");
    while (token != NULL) {
        if (!is_stopword(token)) {
            if (count >= capacity) {
                capacity *= 2;
                words = realloc(words, capacity * sizeof(char*));
            }
            words[count] = strdup(token);
            count++;
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(norm);

    if (out_count)
        *out_count = count;

    return words;
}
void free_tokens(char **tokens, size_t count) {
    for (size_t i = 0; i < count; i++)
        free(tokens[i]);
    free(tokens);
}