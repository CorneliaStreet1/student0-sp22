/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utililties */

char *new_string(char *str) {
  return strcpy((char *)malloc(strlen(str)+1), str);
}

void init_words(WordCount **wclist) {
  /* Initialize word count.  */
  *wclist = (WordCount*)malloc(sizeof(WordCount));
  (*wclist)->word = NULL;
  (*wclist)->next = NULL;
  (*wclist)->count = -1;
}

size_t len_words(WordCount *wchead) {
    size_t len = 0;
    WordCount* p = wchead->next;
    size_t i = 0;
    while (p != NULL)
    {
      i++;
      p = p->next;
    }
    len = i;
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
  WordCount *wc = NULL;
  WordCount* p = wchead->next;
  char LowerWord[64] = {};
  int i = 0;
  //convert word to lowercase
  while (word[i] != '\0')
  {
    LowerWord[i] = tolower(word[i]);
    i ++;
  }
  LowerWord[i] = '\0';
  while (p!= NULL)
  {
    int j = 0;
    char PWord[64];
    while (((p->word)[j]) != '\0')
    {
      PWord[j] = tolower((p->word)[j]);
      j ++;
    }
    if (strcmp(LowerWord, PWord) == 0)
    {
      break;
    }
    else {
      p = p->next;
    }
  }
  wc = p;
  return wc;
}

void add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count, otw insert with count 1. */
  WordCount* wc = find_word((*wclist), word);
  if (wc == NULL)
  {
    WordCount* head = (*wclist);
    WordCount* OldNext = head->next;
    WordCount* NewNext = (WordCount*)malloc(sizeof(WordCount));
    NewNext->count = 1;
    NewNext->word = word;
    NewNext->next = OldNext;
    head->next = NewNext;
  }
  else if (wc != NULL)
  {
    wc->count ++;
  }
  
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
