#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define V_MAX 100

typedef struct {
  int state;
  struct nodeSet *next;
}nodeSet;

typedef struct {
  char letter;
  struct alphabet *next;
}alphabet;

bool nodeSetComp (nodeSet *ns1, nodeSet *ns2){
 nodeSet *n1,*n2;
 int cont = 0, aux = 0;

 n1 = ns1;
 n2 = ns2;

 if(nodeSetSize(n1) != nodeSetSize(n2)){
   return false;
 }else{
   aux = nodeSetSize(n1);
   while(n1 != NULL){
     while(n2 != NULL){
       if(n1->state == n2->state){
         cont++;
         break;
       }
       n2 = n2->next;
     }
     n1 = n1->next;
     n2 = ns2;
   }
 }

 if(cont == aux){
   return true;
 }
 return false;
}

bool stateInNodeSet(nodeSet *ns, int s){
  nodeSet *n;
  n = ns;
  while(n !=  NULL){
    if(n->state == s){
      return true;
    }
    n = n->next;
  }
  return false;
}

void addNodeSet(nodeSet **ns, int s){
  if(!stateInNodeSet(ns,s)){
    nodeSet *n;
    n = malloc(sizeof(nodeSet));
    n->state = s;
    n->next = *ns;
    *ns = n;
  }
}

int nodeSetSize(nodeSet *ns){
  int cont = 0;
  nodeSet *n;
  n = ns;

  while(n != NULL){
    cont++;
    n = n->next;
  }

  return cont;
}

void printNodeSet(nodeSet *ns){
  nodeSet *n;
  n = ns;
  while(n != NULL){
    printf("%d,", n->state);
    //printf("\n");
    n = n->next;
  }
}

//-----------------------------------------------------------
bool letterInAlphabet(alphabet *al, char c){
  alphabet *p;
  p = al;
  while(p != NULL){
    if(p->letter == c ){
      return true;
    }
    p = p->next;
  }
  return false;
}

void addLetter(alphabet **al, char c){
  if(!letterInAlphabet(*al,c) && c != '_'){
    alphabet *n;
    n = malloc(sizeof(alphabet));
    n->letter = c;
    n->next = *al;
    *al = n;
    /*if(*al != NULL){
      alphabet *p, *n;
      n = malloc(sizeof(alphabet));
      n->letter = c;
      p = *al;
      while(p->next != NULL){
        p = p->next;
      }
      p->next = n;
    }else{
      alphabet *n;
      n = malloc(sizeof(alphabet));
      n->letter = c;
      *al = n;
    }*/
  }
}

void pritnAlphabet(alphabet *al){
  alphabet *p;
  p = al;
  while(p != NULL){
    printf("%c,",p->letter);
    p = p->next;
  }
  printf("\n");
}
//-----------------------------------------------------------
